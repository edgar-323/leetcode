/*
Given two strings s1, s2, find the lowest ASCII sum of deleted characters to make two strings equal.

Example 1:
Input: s1 = "sea", s2 = "eat"
Output: 231
Explanation: Deleting "s" from "sea" adds the ASCII value of "s" (115) to the sum.
Deleting "t" from "eat" adds 116 to the sum.
At the end, both strings are equal, and 115 + 116 = 231 is the minimum sum possible to achieve this.

Example 2:
Input: s1 = "delete", s2 = "leet"
Output: 403
Explanation: Deleting "dee" from "delete" to turn the string into "let",
adds 100[d]+101[e]+101[e] to the sum.  Deleting "e" from "leet" adds 101[e] to the sum.
At the end, both strings are equal to "let", and the answer is 100+101+101+101 = 403.
If instead we turned both strings into "lee" or "eet", we would get answers of 433 or 417, which are higher.

Note:
0 < s1.length, s2.length <= 1000.
All elements of each string will have an ASCII value in [97, 122].
*/

class Solution {
private:
    int M;
    int N;
    /*************************************************************************************/
    std::unordered_map<std::string, std::unordered_map<std::string, int>> cache1;
    bool in_cache1(const std::string& s1, const std::string& s2) {
        return cache1.count(s1) and cache1[s1].count(s2);
    }
    int set_cache1_value(const std::string& s1, const std::string& s2, const int min_cost) {
        if (!cache1.count(s1)) {
            cache1.insert(std::make_pair(s1, std::unordered_map<std::string, int>()));
        }
        if (!cache1[s1].count(s2)) {
            cache1[s1].insert(std::make_pair(s2, min_cost));
        }
        return min_cost;
    }
    int recurse1(const std::string& s1, const std::string& s2) {
        if (in_cache1(s1, s2)) {
            return cache1[s1][s2];
        }
        int sum;
        if (s1 == s2) {
            // s1 and s2 are Equal, no need to delete anything else
            sum = 0;
        } else if (s1.empty()) {
            // For s1 and s2 to be equal we must delete all of s2
            sum = 0;
            for (const char& c : s2) {
                sum += int(c);
            }
        } else if (s2.empty()) {
            // For s1 and s2 to be equal we must delete all of s1
            sum = 0;
            for (const char& c : s1) {
                sum += int(c);
            }
        } else if (s1[0] == s2[0]) {
            // first character matches. No need to delete it.
            // We just need the cost of s1[1:M] and s2[1:N)
            sum = recurse1(s1.substr(1), s2.substr(1));
        } else {
            // Let's see if it is cheaper to delete first character
            // from s1 or from s2
            sum = std::min(
                        recurse1(s1.substr(1), s2) + int(s1[0]),
                        recurse1(s1, s2.substr(1)) + int(s2[0]));
        }

        return set_cache1_value(s1, s2, sum); 
    }
    int solution1(const std::string& s1, const std::string& s2) {
        // BRUTE-FORCE SOLUTION
        cache1.clear();
        return recurse1(s1, s2);
    }
    /*************************************************************************************/
    int** cache2;
    int* s1_sum;
    int* s2_sum;
    bool* equal;
    void cache2_init(const std::string& s1, const std::string& s2) {
        M = s1.size();
        N = s2.size();

        cache2 = new int*[M+1];
        for (int i = 0; i <= M; ++i) {
            cache2[i] = new int[N+1];
            for (int j = 0; j <= N; ++j) {
                cache2[i][j] = -1;
            }
        }
        sum_init(s1, s2);
        equal_init(s1, s2);
    }
    void cache2_destroy() {
        for (int i = 0; i <= M; ++i) {
            delete[] cache2[i];
        }
        delete[] cache2;
        sum_destroy();
        equal_destroy();
    }
    void sum_init(const std::string& s1, const std::string& s2) {
     	s1_sum = new int[M+1];
        s1_sum[M] = 0;
        for (int i = M-1; i >= 0; --i) {
            s1_sum[i] = int(s1[i]) + s1_sum[i+1];
        }

        s2_sum = new int[N+1];
        s2_sum[N] = 0;
        for (int j = N-1; j >= 0; --j) {
            s2_sum[j] = int(s2[j]) + s2_sum[j+1];
        }
    }
	void sum_destroy() {
		delete[] s1_sum;
		delete[] s2_sum;
	}
	void equal_init(const std::string& s1, const std::string& s2) {
		const int MIN_DIM = std::min(M,N);
        equal = new bool[MIN_DIM + 1];
        equal[MIN_DIM] = true;
        for (int i = M-1, j = N-1; i >= 0 and j >= 0; --i, --j) {
            equal[MIN_DIM == M ? i : j] = equal[MIN_DIM == M ? i+1 : j+1] and s1[i] == s2[j];
        }
	}
    void equal_destroy() {
        delete[] equal;
    }
    bool in_cache2(const int i, const int j) {
        return cache2[i][j] >= 0;
    }
    int set_cache2_value(const int i, const int j, const int min_cost) {
        return (cache2[i][j] = min_cost);
    }
    bool are_equal(const int i, const int j) {
        if ((M-i) != (N-j)) {
            return false;
        }
        return M <= N ? equal[i] : equal[j];
    }
    int recurse2(const std::string& s1, const std::string& s2, const int i, const int j) {
        if (in_cache2(i, j)) {
            return cache2[i][j];
        }
        int sum;
        if (are_equal(i, j)) {
            sum = 0;
        } else if (i >= M) {
            sum = s2_sum[j];
        } else if (j >= N) {
            sum = s1_sum[i];
        } else if (s1[i] == s2[j]) {
            sum = recurse2(s1, s2, i+1, j+1);
        } else {
            sum = std::min(
                    recurse2(s1, s2, i+1, j) + int(s1[i]),
                    recurse2(s1, s2, i, j+1) + int(s2[j]));
        }

        return set_cache2_value(i, j, sum);
    }
    int solution2(const std::string& s1, const std::string& s2) {
        // SAME IDEA AS solution1(), DIFFERENT CACHING STRATEGY
        cache2_init(s1, s2);
        int min_cost = recurse2(s1, s2, 0, 0);
        cache2_destroy();
        return min_cost; 
    }
    /*************************************************************************************/
    int solution3(const std::string& s1, const std::string& s2) {
        /* Time-Complexity:     O(M*N)
         * Space-Complexity:    O(M*N)
         * */

        M = s1.size();
        N = s2.size();

        equal_init(s1, s2);
        
        auto DP = std::vector<std::vector<int>>(M+1, std::vector<int>(N+1, 0));
        
        for (int i = M-1; i >= 0; --i) {
            DP[i][N] = DP[i+1][N] + int(s1[i]);
        }
        for (int j = N-1; j >= 0; --j) {
            DP[M][j] = DP[M][j+1] + int(s2[j]);
        }
        for (int i = M-1; i >= 0; --i) {
            for (int j = N-1; j >= 0; --j) {
                DP[i][j] =  are_equal(i, j) ?
                            0 :
                            s1[i] == s2[j] ?
                            DP[i+1][j+1] :
                            std::min(DP[i+1][j] + int(s1[i]), DP[i][j+1] + int(s2[j]));
            }
        }
        
        equal_destroy();

        return DP[0][0];
    }
    /*************************************************************************************/                                            
public:
    int minimumDeleteSum(string s1, string s2) {
        return solution3(s1, s2);   
    }
};
