/*
Evaluate the value of an arithmetic expression in Reverse Polish Notation.

Valid operators are +, -, *, /. Each operand may be an integer or another expression.

Note:

Division between two integers should truncate toward zero.
The given RPN expression is always valid. That means the expression would always evaluate to a result and there won't be any divide by zero operation.
Example 1:

Input: ["2", "1", "+", "3", "*"]
Output: 9
Explanation: ((2 + 1) * 3) = 9
Example 2:

Input: ["4", "13", "5", "/", "+"]
Output: 6
Explanation: (4 + (13 / 5)) = 6
Example 3:

Input: ["10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"]
Output: 22
Explanation: 
  ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22
*/
class Solution {
private:
    bool is_operator(const std::string& token) {
        return token.size() == 1 and not ('0' <= token[0] and token[0] <= '9');
    }

    int solution1(const std::vector<std::string>& tokens) {
        auto stack = std::stack<int>();
        for (const auto& token : tokens) {
            if (not is_operator(token)) {
                stack.push(std::stoi(token)); 
                continue;
            }
            const auto y = stack.top(); stack.pop();
            const auto x = stack.top(); stack.pop();
            stack.push(
                    token == "+" ?
                    x + y :
                    token == "-" ?
                    x - y :
                    token == "*" ?
                    x * y :
                    x / y);
        }

        return stack.top();
    }
public:
    int evalRPN(vector<string>& tokens) {
        return solution1(tokens);        
    }
};
