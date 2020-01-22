/*
You are given a string s that consists of lower case English letters and brackets. 
Reverse the strings in each pair of matching parentheses, starting from the innermost one.
Your result should not contain any brackets.

Example 1:
Input: s = "(abcd)"
Output: "dcba"

Example 2:
Input: s = "(u(love)i)"
Output: "iloveu"
Explanation: The substring "love" is reversed first, then the whole string is reversed.

Example 3:
Input: s = "(ed(et(oc))el)"
Output: "leetcode"
Explanation: First, we reverse the substring "oc", then "etco", and finally, the whole string.

Example 4:
Input: s = "a(bcdefghijkl(mno)p)q"
Output: "apmnolkjihgfedcbq"

Constraints:
0 <= s.length <= 2000
s only contains lower case English characters and parentheses.
It's guaranteed that all parentheses are balanced.
*/
class Solution {
private:
    int N;
    int i;
    
    std::string reverse_str(std::string& result) {
        const int M = result.size();
        for (int j = 0; j < M/2; ++j) {
            std::swap(result[j], result[M-1-j]);
        }
        return result;
    }

    std::string recurse1(const std::string& S) {
        auto result = std::string("");

        ++i; // '('
        while (S[i] != ')') {
            if (S[i] == '(') {
                result += recurse1(S);
            } else {
                result += std::string(1, S[i++]);
            }
        }
        ++i; // ')'

        return reverse_str(result);
    }

    std::string solution1(const std::string& S) {
        N = S.size();
        i = 0;

        auto result = std::string("");

        while (i < N) {
            if (S[i] == '(') {
                result += recurse1(S);
            } else {
                result += std::string(1, S[i++]);
            }
        } 

        return result;
    }
public:
    string reverseParentheses(string s) {
        return solution1(s);        
    }
};
