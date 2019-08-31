/*
Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
Note that an empty string is also considered valid.

Example 1:

Input: "()"
Output: true
Example 2:

Input: "()[]{}"
Output: true
Example 3:

Input: "(]"
Output: false
Example 4:

Input: "([)]"
Output: false
Example 5:

Input: "{[]}"
Output: true
*/

class Solution {
private:
    bool match1(std::stack<char>& stack, const char c) {
        if (stack.empty()) {
            return false;
        }
        const char t = stack.top(); stack.pop();
        return t == c;
    }
    bool solution1(const std::string& s) {
        /*
         * Time-Complexity:     O( N )
         * Space-Complexity:    O( N )
         *  where N = length( s )
         *
         *  */
        std::stack<char> stack;
        for (auto c : s) {
            switch (c) {
                case ')':
                    {
                        if (!match1( stack, '(' )) {
                            return false;
                        }
                        break;
                    }
                case ']':
                    {
                        if (!match1( stack, '[' )) {
                            return false;
                        }
                        break;
                    }
                case '}':
                    {
                        if (!match1( stack, '{' )) {
                            return false;
                        }
                        break;
                    }
                default:
                    {
                        stack.push( c );
                    }
            }
        }

        return stack.empty();
    }
public:
    bool isValid(string s) {
        return solution1( s ); 
    }
};
