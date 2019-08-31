/*
 
A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given a non-empty string containing only digits, determine the total number of ways to decode it.

Example 1:

Input: "12"
Output: 2
Explanation: It could be decoded as "AB" (1 2) or "L" (12).
Example 2:

Input: "226"
Output: 3
Explanation: It could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).

*/

class Solution {
private:
    size_t N = 0;
    
    bool isLetter(char a, char b) {
        return b >= '0' and 
                ((a == '1' and b <= '9') or 
                 (a == '2' and b <= '6'));
    }
    
    int recurse1(std::string& s, size_t i) {
        if (i >= N) {
            return 1;
        } else if (s[i] == '0') {
            return 0;
        }
        
        int val = recurse1(s, i+1);
        if (i < N-1 and isLetter(s[i], s[i+1])) {
            val += recurse1(s, i+2);
        }

        return val;
    }
    
 	int solution1(std::string& s) {
       /*
        * Time-Complexity:  O(FIBBONACCI)
        * Space-Complexity: O(N)
        * */

       N = s.size();
       return !N ? 0 : recurse1(s, 0);
	}
    
    int solution2(std::string& s) {
        /*
         * Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         * */
        
        N = s.size();
        if ( !N ) {
            return 0;
        }
        
       int dp[N+1];

       dp[N] = 1;
       dp[N-1] = (s[N-1] == '0') ? 0 : 1;
       for (int i = N-2; i >= 0; --i) {
            if (s[i] == '0') {
                dp[i] = 0;
            } else {
                dp[i] = dp[i+1];
                if (isLetter(s[i], s[i+1])) {
                    dp[i] += dp[i+2];
                }
            }     
       }

       return dp[0];
    }

    int solution3(std::string& s) {
        /*
         * Time-Complexity:     O(N)
         * Space-Complexity:    O(1)
         * */

        N = s.size();
        if (N == 0) {
            return 0;
        }

        int dp_2 = 1;
        int dp_1 = (s[N-1] == '0') ? 0 : 1;
        int dp_0 = dp_1;
        for (int i = N-2; i >= 0; --i) {
            if (s[i] == '0') {
                dp_0 = 0;
            } else {
                dp_0 = dp_1;
                if (isLetter(s[i], s[i+1])) {
                    dp_0 += dp_2;
                }
            }
            dp_2 = dp_1;
            dp_1 = dp_0;
        }

        return dp_0;
    }
    
public:
    int numDecodings(string s) {
        return solution3(s);
    }
};


