/*
Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*'.
'.' Matches any single character.
'*' Matches zero or more of the preceding element.
The matching should cover the entire input string (not partial).

Note:
s could be empty and contains only lowercase letters a-z.
p could be empty and contains only lowercase letters a-z, and characters like . or *.

Example 1:
Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".

Example 2:
Input:
s = "aa"
p = "a*"
Output: true
Explanation: '*' means zero or more of the preceding element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".

Example 3:
Input:
s = "ab"
p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".

Example 4:
Input:
s = "aab"
p = "c*a*b"
Output: true
Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore, it matches "aab".

Example 5:
Input:
s = "mississippi"
p = "mis*is*p*."
Output: false
*/

class Solution {
private:
   bool solution1(const std::string& str, const std::string& pat) {
        /*
         * Time-Complexity:     O(M*N)
         * Space-Complexity:    O(M*N) 
         *
         * */
        const int M = str.size();
        const int N = pat.size();
        bool DP[M+1][N+1];
        for (int m = M; m >= 0; --m) {
            for (int n = N; n >= 0; --n) {
                if (m >= M) {
                    DP[m][n] = n >= N or (pat[n] == '*' and DP[m][n+1]);
                } else if (n >= N) {
                    DP[m][n] = false;
                } else if (pat[n] != '*') {
                    DP[m][n] = (pat[n] == '.' or pat[n] == str[m]) and DP[m+1][n+1];
                } else {
                    DP[m][n] = DP[m+1][n] or DP[m][n+1] or DP[m+1][n+1];
                }
            }
        }
        return DP[0][0];
    } 
public:
    bool isMatch(string s, string p) {
        return solution1( s, p );        
    }
};
