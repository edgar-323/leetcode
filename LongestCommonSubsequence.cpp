/*
Given two strings text1 and text2, return the length of their longest common subsequence.
A subsequence of a string is a new string generated from the original string with some characters(can be none) deleted without changing the relative order of the remaining characters. 
(eg, "ace" is a subsequence of "abcde" while "aec" is not). 
A common subsequence of two strings is a subsequence that is common to both strings.
If there is no common subsequence, return 0.
 
Example 1:
Input: text1 = "abcde", text2 = "ace" 
Output: 3  
Explanation: The longest common subsequence is "ace" and its length is 3.

Example 2:
Input: text1 = "abc", text2 = "abc"
Output: 3
Explanation: The longest common subsequence is "abc" and its length is 3.

Example 3:
Input: text1 = "abc", text2 = "def"
Output: 0
Explanation: There is no such common subsequence, so the result is 0.
 
Constraints:
1 <= text1.length <= 1000
1 <= text2.length <= 1000
The input strings consist of lowercase English characters only.
*/

class Solution {
private:
	int solution1(const std::string& s, const std::string& t) {
        /* Time-Complexity:     O( M*N )
         * Space-Complexity:    O( M*N )
         * */
        const int M = s.size();
        const int N = t.size();
        
        if (!M or !N) {
            return 0;
        }
      
        // EXPLANATION: 
        // DP[i,j] is an MxN grid.
        // DP[i,j] = longest common subsqn btwn s[0:i] and t[0:j].
        // We are interested in DP[M-1][N-1].
        // That is, we are interested in longest common subsqn btwn s[0:M) and t[0:N).
        // To solve:
        //  DP[0,0] = 1 if s[0] == t[0] else 0
        //  DP[i,0] = longest cmn subsqn btwn s[0:i] and t[0:0]
        //            These values will be either 0 or 1
        //  DP[0,j] = Similar to DP[i,0]
        //  DP[i,j] = 
		auto DP = std::vector<std::vector<int>>( M, std::vector<int>( N, 0 ) );
        
        // s[0:0] and t[0:0]
        DP[0][0] = s[0] == t[0] ? 1 : 0;
        // s[1:M) and t[0:0]
        for (int i = 1; i < M; ++i) {
            DP[i][0] = s[i] == t[0] ? 1 : DP[i-1][0];
        }
        // s[0:0] and t[1:N)
        for (int j = 1; j < N; ++j) {
            DP[0][j] = s[0] == t[j] ? 1 : DP[0][j-1];
        }
        // s[1:M) and t[1:N)
        for (int i = 1; i < M; ++i) {
            for (int j = 1; j < N; ++j) {
                DP[i][j] =  s[i] == t[j] ?
                            DP[i-1][j-1] + 1 :
                            std::max( DP[i-1][j], DP[i][j-1] );
            }
        }
        
        return DP[M-1][N-1];
	}
public:
    int longestCommonSubsequence(string text1, string text2) {
  		return solution1( text1, text2 );      
    }
};
