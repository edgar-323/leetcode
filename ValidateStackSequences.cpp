/*
Given two sequences pushed and popped with distinct values, 
return true if and only if this could have been the result of a sequence of push and pop operations on an initially empty stack.

Example 1:
Input: pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
Output: true
Explanation: We might do the following sequence:
push(1), push(2), push(3), push(4), pop() -> 4,
push(5), pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1

Example 2:
Input: pushed = [1,2,3,4,5], popped = [4,3,5,1,2]
Output: false
Explanation: 1 cannot be popped before 2.

Note:
0 <= pushed.length == popped.length <= 1000
0 <= pushed[i], popped[i] < 1000
pushed is a permutation of popped.
pushed and popped have distinct values.
*/
class Solution {
private:
    bool solution1(const std::vector<int>& pushed, const std::vector<int>& popped) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         */

        const int N = pushed.size();

        auto stack = std::stack<int>();
        auto already_pushed = std::unordered_set<int>();

        for (int i = 0, j = 0; j < N; ++j) {
            if (already_pushed.count(popped[j])) {
                while (not stack.empty() and stack.top() != popped[j]) {
                    stack.pop();
                }
                if (stack.empty()) {
                    // we popped it before we were supposed to
                    return false;
                }
                stack.pop();
            } else {
                while (pushed[i] != popped[j]) {
                    stack.push(pushed[i]);
                    already_pushed.insert(pushed[i]);
                    ++i;
                }
                // since pushed[] is a permutation of popped[],
                // we are certain that currently pushed[i] == popped[j]
                already_pushed.insert(popped[j]);
            }
        }

        return true;
    }
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        return solution1(pushed, popped);        
    }
};
