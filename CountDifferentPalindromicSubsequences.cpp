/*
Given a string S, find the number of different non-empty palindromic subsequences in S, and return that number modulo 10^9 + 7.
A subsequence of a string S is obtained by deleting 0 or more characters from S.
A sequence is palindromic if it is equal to the sequence reversed.
Two sequences A_1, A_2, ... and B_1, B_2, ... are different if there is some i for which A_i != B_i.

Example 1:
Input: S = 'bccb'
Output: 6
Explanation: 
The 6 different non-empty palindromic subsequences are 'b', 'c', 'bb', 'cc', 'bcb', 'bccb'.
Note that 'bcb' is counted only once, even though it occurs twice.

Example 2:
Input: S = 'abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba'
Output: 104860361
Explanation: 
There are 3104860382 different non-empty palindromic subsequences, which is 104860361 modulo 10^9 + 7.

Note:
The length of S will be in the range [1, 1000].
Each character S[i] will be in the set {'a', 'b', 'c', 'd'}.
*/

class Solution {
private:
    static const int MOD_VAL = 1e9 + 7; // 10^9 + 7

    static const int ALPH_SZ = 4; // {a, b, c, d}

    char to_char(const int x) {
        return x + 'a';
    }

	int solution1(const std::string& S) {
        /* Time-Complexity:     O(ALPH_SZ * N^2)
         * Space-Complexity:    O(ALPH_SZ * N^2)
         */
        /* EXLPANATION:
         * Let dp[x][i][j] be the answer for the substring S[i...j] where S[i] == S[j] == 'a'+x. 
         * Note that since we only have 4 characters a, b, c, d, thus 0 <= x < 4. 
         *
         * The DP formula goes as follows:
         *  1)  If S[i] != 'a'+x, then dp[x][i][j] = dp[x][i+1][j], note that here we leave the first character S[i] in the window out due to our definition of dp[x][i][j].
         *  2)  If S[j] != 'a'+x, then dp[x][i][j] = dp[x][i][j-1], leaving the last character S[j] out.
         *  3)  If S[i] == S[j] == 'a'+x, then dp[x][i][j] = 2 + dp[0][i+1][j-1] + dp[1][i+1][j-1] + dp[2][i+1][j-1] + dp[3][i+1][j-1]. 
         *      When the first and last characters are the same, we need to count all the distinct palindromes 
         *      (for each of a,b,c,d) within the sub-window S[i+1][j-1] plus the 2 palindromes contributed by the first and last characters.
         *
         * Let n be the length of the input string S,
         * The final answer would be (dp[0][0][n-1] + dp[1][0][n-1] + dp[2][0][n-1] + dp[3][0][n-1]) mod (10^9 + 7).
         */
        const int N = S.size(); 
         
        auto DP = std::vector<std::vector<std::vector<int>>>( ALPH_SZ,
                    std::vector<std::vector<int>>(N,
                        std::vector<int>(N)));
        // len 1
        for (int i = 0; i < N; ++i) {
            for (int x = 0; x < ALPH_SZ; ++x) {
                DP[x][i][i] = S[i] == to_char(x); 
            }
        }
        // len 2
        for (int i = 0; i < N-1; ++i) {
            for (int x = 0; x < ALPH_SZ; ++x) {
                if (S[i] != to_char(x)) {
                    DP[x][i][i+1] = DP[x][i+1][i+1];
                } else if (S[i+1] != to_char(x)) {
                    DP[x][i][i+1] = DP[x][i][i];
                } else {
                    DP[x][i][i+1] = 2;
                }
            }
        }
        // len >= 3
        for (int len = 3; len <= N; ++len) {
            for (int i = 0, j = len-1; j < N; ++i, ++j) {
                for (int x = 0; x < ALPH_SZ; ++x) {
                    if (S[i] != to_char(x)) {
                        DP[x][i][j] = DP[x][i+1][j];
                    } else if (S[j] != to_char(x)) {
                        DP[x][i][j] = DP[x][i][j-1];
                    } else {
                        DP[x][i][j] = 2;
                        for (int y = 0; y < ALPH_SZ; ++y) {
                            DP[x][i][j] = (DP[x][i][j] + DP[y][i+1][j-1]) % MOD_VAL;
                        }
                    }
                }
            }
        }
        // RESULT 
        int result = 0;
        for (int x = 0; x < ALPH_SZ; ++x) {
            result = (result + DP[x][0][N-1]) % MOD_VAL;
        }
        return result;
	}
public:
    int countPalindromicSubsequences(string S) {
  		return solution1(S);
    }
};
