/*
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
For example, given n = 3, a solution set is:

[
  "((()))",
  "(()())",
  "(())()",
  "()(())",
  "()()()"
]
*/

class Solution {
private:
    void recurse1(std::string curr, const int openPars, const int closePars, std::vector<std::string>& results) {
        if (openPars <= 0 && closePars <= 0) {
            // No more options to generate more paranthesis
            if (curr.size() > 0) {
                // Only add if we have non-empty generation
                results.push_back(curr);
            }
            return;
        }
        
        if (openPars >= 1) {
            collectCombinations(curr + "(", openPars - 1, closePars, results);
        }
        if (openPars < closePars) {
            collectCombinations(curr + ")", openPars, closePars - 1, results);
        }
    }

    std::vector<std::string> solution1(const int N) {
        std::vector<std::string> results;
        recurse1( "", N, N, results );
        return results;
    }	
public:
    vector<string> generateParenthesis(int n) {
        return solution1( n );
    }
};
