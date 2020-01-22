/*
Implement a basic calculator to evaluate a simple expression string.

The expression string may contain open ( and closing parentheses ), the plus + or minus sign -, non-negative integers and empty spaces .

Example 1:
Input: "1 + 1"
Output: 2

Example 2:
Input: " 2-1 + 2 "
Output: 3

Example 3:
Input: "(1+(4+5+2)-3)+(6+8)"
Output: 23

Note:
You may assume that the given expression is always valid.
Do not use the eval built-in library function.
*/
class Solution {
private:
    void consume_spaces(const std::string& S, int& index) {
        while (index >= 0 and S[index] == ' ') {
            --index;
        }
    }

    bool is_digit(const char c) {
        return '0' <= c and c <= '9';
    }

    int get_digit(const char c) {
        return c - '0';
    }

    long long parse_integer(const std::string& S, int& index) {
        long long pow_ten = 1;
        long long num = 0;
        while (index >= 0 and is_digit(S[index])) {
            num = pow_ten * get_digit(S[index--]) + num;
            pow_ten *= 10;
        }
        return num;
    }

    bool is_operator(const char c) {
        return c == '+' or c == '-' or c == '*';
    }

    int solution1(const std::string& S) {
        if (S.empty()) {
            return 0;
        }
        const int N = S.size();
        
        auto stack = std::stack<std::string>();
       
        int i = N-1;

        while (i >= 0) {
            consume_spaces(S, i);
            if (is_digit(S[i])) {
                auto num = parse_integer(S, i);
                while (not stack.empty() and stack.top() == "*") {
                    stack.pop();
                    num *= std::stoll(stack.top());
                    stack.pop();
                }
                stack.push(std::to_string(num));
            } else if (is_operator(S[i]) or S[i] == ')') {
                stack.push(std::string(1, S[i--]));
            } else if (stack.top() == ")") {
                // Dont know if this is legal
                --i;
                stack.pop();
                stack.push("0");
            } else {
                --i;
                auto num = std::stoll(stack.top()); stack.pop();
                while (stack.top() != ")") {
                    const auto op = stack.top(); stack.pop();
                    num += (op == "-" ? -1 : 1) * std::stoll(stack.top()); stack.pop();
                }
                stack.pop();
                stack.push(std::to_string(num));
            }
        }
        auto result = std::stoll(stack.top()); stack.pop();
        while (not stack.empty()) {
            const auto op = stack.top(); stack.pop();
            result += (op == "-" ? -1 : 1) * std::stoll(stack.top()); stack.pop();
        }

        return result; 
    }
public:
    int calculate(string s) {
        return solution1(s);
    }
};
