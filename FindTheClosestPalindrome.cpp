/*
Given an integer n, find the closest integer (not including itself), which is a palindrome.
The 'closest' is defined as absolute difference minimized between two integers.

Example 1:
Input: "123"
Output: "121"

Note:
    1)  The input n is a positive integer represented by string, whose length will not exceed 18.
    2)  If there is a tie, return the smaller one as answer.
*/
class Solution {
private:
    bool is_all_digit_9(const std::string& num) {
        for (const auto& c : num) {
            if (c != '9') {
                return false;
            }
        }
        return true;
    }

    long long to_palindrome(const int root, const bool exclude_last_digit) {
        const auto num = std::to_string(root);
        auto reversed = exclude_last_digit ? num.substr(0, num.size()-1) : num;
        std::reverse(reversed.begin(), reversed.end());
        return std::stoll(num + reversed);
    }

    std::string solution1(const std::string& num) {
        /* Time-Complexity:     O(L)
         * Space-Complexity:    O(L)
         *      Where:
         *          L = len(num)
         */
        const int L = num.size();

        const auto N = std::stoll(num);
        
        if (N <= 10) {
            // cases: {0,1,..,10}
            return std::to_string(N-1);
        }
        if (N % 10 == 0 and std::stoll(num.substr(1)) == 0) {
            // cases: {100, 1000, 10000, ...}
            return std::to_string(N-1);
        }
        if (N == 11 or (N % 10 == 1 and 
                        num[0] == '1' and 
                        std::stoll(num.substr(1, L - 2)) == 0)) {
            // cases: {11, 101, 1001, 10001, ...}
            return std::to_string(N-2);
        }
        if (is_all_digit_9(num)) {
            // cases: {9, 99, 999, 9999, ...}
            return std::to_string(N+2);
        }

        const auto palindrome_root = std::stoll(num.substr(0, L/2 + (L&1)));
        
        const auto equal = to_palindrome(palindrome_root, L&1);
        const auto diff_equal = std::abs(N - equal);

        const auto smaller = to_palindrome(palindrome_root - 1, L&1);
        const auto diff_smaller = std::abs(N - smaller);

        const auto bigger = to_palindrome(palindrome_root + 1, L&1);
        const auto diff_bigger = std::abs(N - bigger);

        auto closest =  diff_bigger < diff_smaller ? bigger : smaller;
        auto min_diff = std::min(diff_smaller, diff_bigger);

        if (diff_equal) {
            if (diff_equal == min_diff) {
                closest = std::min(closest, equal);
            } else if (diff_equal < min_diff) {
                closest = equal;
            }
        }

        return std::to_string(closest);
    }
public:
    string nearestPalindromic(string n) {
        return solution1(n);       
    }
};
