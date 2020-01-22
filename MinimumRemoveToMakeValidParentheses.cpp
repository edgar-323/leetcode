/*
Given a string s of '(' , ')' and lowercase English characters. 

Your task is to remove the minimum number of parentheses ( '(' or ')', in any positions ) so that the resulting parentheses string is valid and return any valid string.

Formally, a parentheses string is valid if and only if:

It is the empty string, contains only lowercase characters, or
It can be written as AB (A concatenated with B), where A and B are valid strings, or
It can be written as (A), where A is a valid string.
 

Example 1:

Input: s = "lee(t(c)o)de)"
Output: "lee(t(c)o)de"
Explanation: "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.
Example 2:

Input: s = "a)b(c)d"
Output: "ab(c)d"
Example 3:

Input: s = "))(("
Output: ""
Explanation: An empty string is also valid.
Example 4:

Input: s = "(a(b(c)d)"
Output: "a(b(c)d)"
 

Constraints:

1 <= s.length <= 10^5
s[i] is one of  '(' , ')' and lowercase English letters.
*/
class Solution {
private:
    static const char INVALID = '$';

    std::string solution1(std::string& S) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(1)
         */

        const int N = S.size();    
        
        int balanced = 0;
        for (int i = 0; i < N; ++i) {
            if (S[i] == '(') {
                ++balanced;
            } else if (S[i] == ')') {
                if (not balanced) {
                    S[i] = INVALID;
                } else {
                    --balanced;
                }    
            }
        }
        balanced = 0;
        for (int i = N-1; i >= 0; --i) {
            if (S[i] == ')') {
                ++balanced;
            } else if (S[i] == '(') {
                if (not balanced) {
                    S[i] = INVALID;
                } else {
                    --balanced;
                }
            }
        }
        auto valid_str = std::string("");
        valid_str.reserve(N);
        for (int i = 0; i < N; ++i) {
            if (S[i] == INVALID) {
                continue;
            }
            valid_str += std::string(1, S[i]);
        }

        return valid_str;
    }
public:
    string minRemoveToMakeValid(string s) {
        return solution1(s);        
    }
};
