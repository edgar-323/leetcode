/*
Given a string s, partition s such that every substring of the partition is a palindrome.

Return all possible palindrome partitioning of s.

Example:

Input: "aab"
Output:
[
  ["aa","b"],
  ["a","a","b"]
]
*/
#include <iostream>
#include <vector>
#include <string>
#include <list>

class Solution {
private:
    typedef std::vector<std::list<std::string>> Lists;
    typedef std::list<std::string> List;
    /***********************************************************************************/
    bool is_palindrome(const std::string& s, int start,int end) {
        for(; start <= end; ++start, --end) {
            if (s[start] != s[end]) {
                return false;
            }
        }
        return true;
    }
    void recurse1(const std::string& s, Lists& partitions, const size_t start) {
        const size_t N = s.size();
        if (start >= N) {
            partitions.push_back( List() ); 
            return;
        }
        for (size_t i = start; i < N; ++i) {
            if (is_palindrome(s, start, i)) {
                std::string palindrome = s.substr( start, (i+1) - start );
                Lists partials = Lists();
                recurse1(s, partials, i+1);
                for (auto& list : partials) {
                    list.push_front( palindrome );
                    partitions.push_back( list );
                }
            }
        }
    }
    void solution1(const std::string& s, std::vector<std::vector<std::string>>& results) {
        /* Approach: 
         * In this approach we begin from index 0 and begin searching for palindromes 
         * from `s[0:i]` and if we find a palindrome we get the palindromes from `s[i+1:N]`
         * and we add current palindromes to paloindromes lists of `s[i+1:N]`. 
         * We do this recursivesly for all i.
         * This is very slow due to fact that we recompute palindrome partitions for certain
         * values of  `i` and also because the way in which we check whether a given substring
         * of `s` is a palindrome is very inefficient.
         * */
        if (s.empty()) {
            return;
        }
        Lists lists;
        recurse1( s, lists, 0 );
        for (auto& list : lists ) {
            results.push_back( std::vector<std::string>( list.begin(), list.end() ));
        }
    }
    /***********************************************************************************/
    bool** in_cache;
    Lists** cache;
    size_t N;
    void recurse2(std::string& s, const int start, const int end) {
        std::cout << "(START = " << start << ", END = " << end << ")" << std::endl;
        for (int center = start; center <= end; ++center) {
            for (int l = center, r = center; 
                l >= start and r <= end and s[l] == s[r]; 
                --l, ++r) {
                // We have a palindrome: `s[l:r]`
                auto palindrome = s.substr(l, (l+1) - r);
                Lists partitions = Lists();
                if (l > 0) {
                    if (!in_cache[0][l-1]) {
                        recurse2(s, 0, l-1);
                    }
                    partitions = cache[0][l-1];
                } else {
                    // There is no left to check
                    partitions.push_back( List() );
                }
                for (auto& list : partitions) {
                    list.push_back( palindrome );
                }
                if (r < N-1) {
                    if (!in_cache[r+1][N-1]) {
                        recurse2(s, r+1, N-1);
                    }
                    for (auto& left_list : partitions) {
                        for (auto& right_list : cache[r+1][N-1]) {
                            for (auto& right_palindrome : right_list) {
                                left_list.push_back( right_palindrome );
                            }
                        }
                    }
                }
                auto& P = cache[start][end];
                P.reserve( P.size() + partitions.size() );
                P.insert( P.end(), partitions.begin(), partitions.end() ); 
            }
        }
        in_cache[start][end] = true;
    }
    void init() {
        in_cache = new bool*[N];
        cache = new Lists*[N];
        for (size_t i = 0; i < N; ++i) {
            in_cache[i] = new bool[N];
            cache[i] = new Lists[N];
            for (size_t j = 0; j < N; ++j) {
                in_cache[i][j] = false;
            }
        }
    }
    void set_single_palindromes(const std::string& s) {
        for (size_t i = 0; i < N; ++i) {
            cache[i][i].push_back( List(1, s.substr( i, 1 ) ) );
            in_cache[i][i] = true;
        }
    }
    void destroy() {
        for (size_t i = 0; i < N; ++i) {
            delete[] in_cache[i];
            delete[] cache[i];
        }
        delete[] in_cache;
        delete[] cache;
    }
    void collect(std::vector<std::vector<std::string>>& results) {
        for (auto& partition : cache[0][N-1]) {
            results.push_back( std::vector<std::string>( partition.begin(), partition.end() ) );
        }
    }
    void solution2( std::string& s, std::vector<std::vector<std::string>>& results ) {
        N = s.size();
        if ( !N ) {
            return;
        }
        std::cout << "Initializing...";
        init(); 
        std::cout << "Done." << std::endl;
        set_single_palindromes( s ); 
        recurse2(s, 0, N-1);
        collect( results );
        std::cout << std::endl;
        destroy();
    }
    /***********************************************************************************/
public:
    std::vector<std::vector<std::string>> partition(std::string s) {
        std::vector<std::vector<std::string>> results;
        solution2( s, results );
        return results;
    }
};

template <typename T>
void print(std::vector<T>& vec) {
    const size_t N = vec.size();
    std::cout << "[";
    for (size_t i = 0; i < N; ++i) {
        std::cout << vec[i] << ((i < N-1) ? ", " : "");
    }
    std::cout << "]" << std::endl;
}

int main() {
    Solution solution;
    std::string s = "acb";
    auto ans = solution.partition( s );
    std::cout << "partition(\"" << s << "\"):" << std::endl;
    for (auto& list : ans) {
        print( list );
    }

    return 0;
}
