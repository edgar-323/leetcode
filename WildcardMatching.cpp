/*
Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*'.

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).
The matching should cover the entire input string (not partial).

Note:
s could be empty and contains only lowercase letters a-z.
p could be empty and contains only lowercase letters a-z, and characters like ? or *.

Example 1:
Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".

Example 2:
Input:
s = "aa"
p = "*"
Output: true
Explanation: '*' matches any sequence.

Example 3:
Input:
s = "cb"
p = "?a"
Output: false
Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.

Example 4:
Input:
s = "adceb"
p = "*a*b"
Output: true
Explanation: The first '*' matches the empty sequence, while the second '*' matches the substring "dce".

Example 5:
Input:
s = "acdcb"
p = "a*c?b"
Output: false
*/
#include <iostream>
#include <string>
class Solution {
private:
    /****************************************************************/
    int N, M;
    bool recurse1(std::string& str, int m, std::string& pat, int n) {
       if (m >= M) {
          return n >= N or 
                (pat[n] == '*' and recurse1(str, m, pat, n+1));
       } else if (n >= N) {
          return m >= M;
       } else if (pat[n] != '*') {
            return (pat[n] == '?' or pat[n] == str[m]) 
                    and recurse1(str, m+1, pat, n+1);
       } else {
            return recurse1(str, m+1, pat, n) 
                    or recurse1(str, m, pat, n+1)
                    or recurse1(str, m+1, pat, n+1);
       }
    }
    bool solution1(std::string& s, std::string& p) {    
        /* 
         * Time-Complexity:     O(3^(M+N))
         * Space-Complexity:    O(M*N)
         * 
         * */
        M = s.size();
        N = p.size();
        return recurse1(s, 0, p, 0);
    }
    /***************************************************************/
    int** memo;
    bool recurse2(std::string& str, int m, std::string& pat, int n) {
        if (memo[m][n] >= 0) {
            return memo[m][n];
        } else if (m >= M) {
            memo[m][n] = n >= N or 
                        (pat[n] == '*' and 
                         recurse2(str, m, pat, n+1));
        } else if (n >= N) {
            memo[m][n] = m >= M;
        } else if (pat[n] != '*') {
            memo[m][n] = (pat[n] == '?' or 
                            pat[n] == str[m]) and 
                        recurse2(str, m+1, pat, n+1);
        } else {
            memo[m][n] = recurse2(str, m+1, pat, n) or 
                        recurse2(str, m, pat, n+1) or 
                        recurse2(str, m+1, pat, n+1);
        }
        
        return memo[m][n];
    }
    bool solution2(std::string& s, std::string& p) {
        /*
         * Time-Complexity:     O(M*N)
         * Space-Complexity:    O(M*N)
         *
         * */
        M = s.size();
        N = p.size();
        memo = new int*[M+1];
        for (int i = 0; i <= M; ++i) {
            memo[i] = new int[N+1];
            for (int j = 0; j <= N; ++j) {
                memo[i][j] = -1;
            }
        }
        bool is_match = recurse2(s, 0, p, 0);
        for (int i = 0; i <= M; ++i) {
            delete [] memo[i];
        }
        delete [] memo;
        memo = NULL;
        return is_match;
    }
    /****************************************************************/
    bool solution3(std::string& str, std::string& pat) {
        /*
         * Time-Complexity:     O(M*N)
         * Space-Complexity:    O(M*N) 
         *
         * */
        M = str.size();
        N = pat.size();
        bool DP[M+1][N+1];
        for (int m = M; m >= 0; --m) {
            for (int n = N; n >= 0; --n) {
                if (m >= M) {
                    DP[m][n] = n >= N or (pat[n] == '*' and DP[m][n+1]);
                } else if (n >= N) {
                    DP[m][n] = false;
                } else if (pat[n] != '*') {
                    DP[m][n] = (pat[n] == '?' or pat[n] == str[m]) and DP[m+1][n+1];
                } else {
                    DP[m][n] = DP[m+1][n] or DP[m][n+1] or DP[m+1][n+1];
                }
            }
        }
        return DP[0][0];
    }
    /****************************************************************/
public:
    bool isMatch(std::string s, std::string p) {
        return solution3(s, p);       
    }
};

int main(int argc, char** argv) {
    Solution solution;
    std::string s = "aaabababaaabaababbbaaaabbbbbbabbbbabbbabbaabbababab";
    std::string p = "*ab***ba**b*b*aaab*b";
    std::string ans = solution.isMatch(s, p) ? "True" : "False";
    std::cout << "ANSWER: " << ans << std::endl;
    return 0;
}
