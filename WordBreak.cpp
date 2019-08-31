/*

Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, determine if s can be segmented into a space-separated sequence of one or more dictionary words.

Note:
The same word in the dictionary may be reused multiple times in the segmentation.
You may assume the dictionary does not contain duplicate words.

Example 1:
Input: s = "leetcode", wordDict = ["leet", "code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".

Example 2:
Input: s = "applepenapple", wordDict = ["apple", "pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
             Note that you are allowed to reuse a dictionary word.

Example 3:
Input: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
Output: false

*/

class Solution {
private:
    /***********************************************************************/
    bool isPrefix1(const std::string& s, const std::string& t, int suffix) {
        // Returns true if `t` is prefix of `s[suffix:S)` otherwise returns false.
        const int S = s.size();
        const int T = t.size();
        for (int i = 0; i < T; ++i, ++suffix) {
            if (suffix >= S or s[suffix] != t[i]) {
                return false;
            } 
        }
        return true;
    }
    std::vector<int> search1(const std::string& s, const std::string& t) {
        /* Returns `indices` with positions `i € {0,1,..., S-1}` 
         * where `t` is a non-empty prefix of `s[i:S)`. 
         * */
        /* Time-Complexity:     O( S*T )
         * Space-Complexity:    O(  1  )
         * */
        // If we implememt Z-Algorithm, we can reduce runtime complexity
        // to O( S+T ) but will increase space complexity O( S+T )
        std::vector<int> indices;
        const int S = s.size();
        const int T = t.size();
        if (T == 0 or T > S) {
            return indices;
        }
        for (int i = 0; i < S; ++i) {
            if (isPrefix1(s, t, i)) {
                indices.push_back(i);
            }
        }
        return indices;
    }
    bool solution1(std::string& s, std::vector<std::string>& wordDict) {
        /*
         * Time-Complexity:     O(S * W)
         * Space-Complexity:    O(S * D)
         *
         * where: 
         *  S = size(s), 
         *  D = size(wordDict),  
         *  W = ∑ {size(t) | t € wordDict}
         *
         * */
        
        const int S = s.size();
        const int D = wordDict.size();
        
        std::vector<std::vector<int>> indexMatrix(S, std::vector<int>());
        for (int w = 0; w < D; ++w) {
            for (const int& index : search1(s, t)) {
                indexMatrix[index].push_back(w);
            }
        }

        std::vector<bool> DP(S+1, false);
        DP[S] = true;
        for (int i = S-1; i >= 0; --i) {
            for (const int& index : indexMatrix[i]) {
                const int T = wordDict[index].size();
                DP[i] = DP[i+T] ? true : DP[i]; 
            }
        }

        return DP[0];
    }
    /***********************************************************************/
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        return solution1(s, wordDict);        
    }
};
