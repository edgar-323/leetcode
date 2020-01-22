/*
Given a balanced parentheses string S, compute the score of the string based on the following rule:
() has score 1
AB has score A + B, where A and B are balanced parentheses strings.
(A) has score 2 * A, where A is a balanced parentheses string.

Example 1:
Input: "()"
Output: 1

Example 2:
Input: "(())"
Output: 2

Example 3:
Input: "()()"
Output: 2

Example 4:
Input: "(()(()))"
Output: 6

Note:
S is a balanced parentheses string, containing only ( and ).
2 <= S.length <= 50
*/
class Solution {
private:
    int N;
    int i;

    int recurse1(const std::string& S) {
        // assume we ae already submerged into an open paren
        int score = 0;
        ++i;
        while (S[i] != ')') {
            // Since S[i] != ')', we know S[i] == '('
            if (S[i+1] == ')') {
                ++score;
                i += 2;
            } else {
                score += 2 * recurse1(S);
            }
        }
        ++i;

        return score;
    }

    int solution1(const std::string& S) {
        N = S.size();
        i = 0;
        int score = 0;
        while (i < N) {
            if (S[i+1] == ')') {
                ++score;
                i += 2;
            } else {
                score += 2 * recurse1(S);
            }
        }

        return score; 
    }
public:
    int scoreOfParentheses(string S) {
        return solution1(S);    
    }
};
