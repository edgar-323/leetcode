/*
Given a string S of '(' and ')' parentheses, we add the minimum number of parentheses ( '(' or ')', and in any positions ) so that the resulting parentheses string is valid.
Formally, a parentheses string is valid if and only if:
It is the empty string, or
It can be written as AB (A concatenated with B), where A and B are valid strings, or
It can be written as (A), where A is a valid string.
Given a parentheses string, return the minimum number of parentheses we must add to make the resulting string valid.

Example 1:
Input: "())"
Output: 1

Example 2:
Input: "((("
Output: 3

Example 3:
Input: "()"
Output: 0

Example 4:
Input: "()))(("
Output: 4

Note:
S.length <= 1000
S only consists of '(' and ')' characters.
*/
class Solution {
private:
    int solution1(const std::string& S) {
        int min_paren = 0;
        int num_open_paren = 0;

        for (const auto& c : S) {
            if (c == '(') {
                ++num_open_paren;
            } else if (not num_open_paren) {
                ++min_paren;
            } else {
                --num_open_paren;
            }
        }
        min_paren += num_open_paren;

        return min_paren;
    }
public:
    int minAddToMakeValid(string S) {
        return solution1(S);        
    }
};
