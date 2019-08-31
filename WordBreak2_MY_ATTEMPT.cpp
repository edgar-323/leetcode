/*

Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, add spaces in s to construct a sentence where each word is a valid dictionary word. Return all such possible sentences.

Note:
The same word in the dictionary may be reused multiple times in the segmentation.
You may assume the dictionary does not contain duplicate words.

Example 1:
Input:
s = "catsanddog"
wordDict = ["cat", "cats", "and", "sand", "dog"]
Output:
[
  "cats and dog",
  "cat sand dog"
]

Example 2:
Input:
s = "pineapplepenapple"
wordDict = ["apple", "pen", "applepen", "pine", "pineapple"]
Output:
[
  "pine apple pen apple",
  "pineapple pen apple",
  "pine applepen apple"
]
Explanation: Note that you are allowed to reuse a dictionary word.

Example 3:
Input:
s = "catsandog"
wordDict = ["cats", "dog", "sand", "and", "cat"]
Output:
[]

*/

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <unordered_set>

void print(std::vector<std::string>& vec) {
    std::cout << "[";
    for (auto& s : vec) {
        std::cout << s << ", ";
    }
    std::cout << "]" << std::endl;
}

class Solution {
private:
	/***********************************************************************/
    int prefixCompare1(std::string& s, std::string& t, int suffix) {
        /* Lexicographically compares `s[suffix:S]` and `t`.
         * Returns:
         *   -1 if s[suffix:S) < t
         *    1 if s[suffix:S) > t
         *    0 if t is prefix of s[suffix:S)
         * */
        const int S = s.size();
        const int T = t.size();
        for (int i = 0; i < T; ++i, ++suffix) {
            if (suffix >= S or s[suffix] > t[i]) {
                return 1;
            } else if (s[suffix] < t[i]) {
                return -1;
            }
        }
        return 0;
    }
    void search1(std::string& s, std::string& t, std::vector<int>& indices) {
        /* Populates `indices` with positions `i` 
         * where `t` is a prefix of `s[i:S)`. 
         * */
        const int S = s.size();
        const int T = t.size();
        if (T == 0 or T > S) {
            return;
        }
        for (int i = 0; i < S; ++i) {
            if (prefixCompare1(s, t, i) == 0) {
                indices.push_back(i);
            }
        }
    }
    void recurse1(std::string curr, 
                    std::vector<std::vector<std::pair<int,int> > >& DP, int pos,
                    std::vector<std::string>& wordDict, 
                    std::unordered_set<std::string>& results) {
        for (std::pair<int, int>& p : DP[pos]) {
            int& nextPos = p.first;
            int& index = p.second;
            if (nextPos >= 0) {
                recurse1(curr + ((curr.size() > 0) ? " " : "")  + wordDict[index], DP, nextPos, wordDict, results);
            } else if (results.count(curr) == 0) {
                results.insert(curr);
            }
        }
        
    }
    void solution1(std::string& s, std::vector<std::string>& wordDict, std::vector<std::string>& results) {
        const int S = s.size();
        const int D = wordDict.size();
        
        std::vector<std::vector<int> > indexMatrix(S, std::vector<int>());
        for (int w = 0; w < D; ++w) {
            std::vector<int> indices = std::vector<int>();
            search1(s, wordDict[w], indices);
            for (int index : indices) {
                indexMatrix[index].push_back(w);
            }
        }

        std::vector<std::vector<std::pair<int, int> > > DP(S+1, std::vector<std::pair<int, int > >());
        DP[S].push_back(std::make_pair(-1, -1));
        for (int i = S-1; i >= 0; --i) {
            for (int index : indexMatrix[i]) {
                const int T = wordDict[index].size();
                for (std::pair<int, int>& p : DP[i+T]) {
                    DP[i].push_back(std::make_pair(i+T, index));
                }
            }
        }
        
        std::unordered_set<std::string> result_set;
        recurse1("", DP, 0, wordDict, result_set);
        results = std::vector<std::string>(result_set.begin(), result_set.end());
	}
    /***********************************************************************/
public:
    std::vector<std::string> wordBreak(std::string s, std::vector<std::string>& wordDict) {
        std::vector<std::string> results;
        solution1(s, wordDict, results);
        return results; 
    }
};

int main(int argc, char** argv) {
    std::string s = "pineapplepenapple";
    const int D = 5;
    const char* dict[] = { "apple", "pen", "applepen", "pine", "pineapple" };
    std::vector<std::string> wordDict(dict, dict+D);
    
    Solution solution;
    auto results = solution.wordBreak(s, wordDict);

    std::cout << "INPUT:\n";
    std::cout << "s = " << s << std::endl;
    std::cout << "wordDict = ";
    print(wordDict);
    std::cout << "\nOUTPUT:\n";
    std::cout << "results = ";
    print(results);
    std::cout << std::endl;
    return 0;
}
