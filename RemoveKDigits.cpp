/*
Given a non-negative integer num represented as a string, remove k digits from the number so that the new number is the smallest possible.
Note:
The length of num is less than 10002 and will be ≥ k.
The given num does not contain any leading zero.

Example 1:
Input: num = "1432219", k = 3
Output: "1219"
Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.

Example 2:
Input: num = "10200", k = 1
Output: "200"
Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.

Example 3:
Input: num = "10", k = 2
Output: "0"
Explanation: Remove all the digits from the number and it is left with nothing which is 0.
*/
class Solution {
private:
    std::string solution1(const std::string& num, int K) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         */
        auto deque = std::deque<char>();
        for (const auto& digit : num) {
            while (not deque.empty() and K and deque.back() > digit) {
                deque.pop_back();
                --K;
            }
            deque.push_back(digit);
        }
        while (K) {
            deque.pop_back();
            --K;
        }
        auto result = std::string("");
        bool has_leading_zero = true;
        while (not deque.empty()) {
            const auto digit = deque.front();
            deque.pop_front();
            if (has_leading_zero and digit == '0') {
                continue;
            }
            has_leading_zero = false;
            result += std::string(1, digit);
        }
        
        return result.empty() ? "0" : result; 
    }
public:
    string removeKdigits(string num, int k) {
        return solution1(num, k);        
    }
};
