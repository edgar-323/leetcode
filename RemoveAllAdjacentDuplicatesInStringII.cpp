/*
Given a string s, a k duplicate removal consists of choosing k adjacent and equal letters from s and removing them causing the left and the right side of the deleted substring to concatenate together.
We repeatedly make k duplicate removals on s until we no longer can.
Return the final string after all such duplicate removals have been made.
It is guaranteed that the answer is unique.

Example 1:
Input: s = "abcd", k = 2
Output: "abcd"
Explanation: There's nothing to delete.

Example 2:
Input: s = "deeedbbcccbdaa", k = 3
Output: "aa"
Explanation: 
First delete "eee" and "ccc", get "ddbbbdaa"
Then delete "bbb", get "dddaa"
Finally delete "ddd", get "aa"

Example 3:
Input: s = "pbbcggttciiippooaais", k = 2
Output: "ps"

Constraints:
1 <= s.length <= 10^5
2 <= k <= 10^4
s only contains lower case English letters.
*/
class Solution {
private:
    std::string solution1(const std::string& S, const int K) {
        auto stack = std::stack<std::pair<char, int>>();
        int i = S.size() - 1;

        while (i >= 0) {
            const auto c = S[i--]; 
            int count = 1;
            while (i >= 0 and S[i] == c) {
                ++count;
                --i;
            }
            int leftover = count % K;
            if (not leftover) {
                continue;
            }
            if (not stack.empty() and stack.top().first == c) {
                leftover = (leftover + stack.top().second) % K;
                if (leftover) {
                    stack.top().second = leftover;
                } else {
                    stack.pop();
                }
            } else {
                stack.push({c, leftover});
            } 
        }

        auto result = std::string("");
        while (not stack.empty()) {
            const auto node = stack.top(); stack.pop();
            result += std::string(node.second, node.first);
        }

        return result;
    }
public:
    string removeDuplicates(string s, int k) {
        return solution1(s, k);       
    }
};
