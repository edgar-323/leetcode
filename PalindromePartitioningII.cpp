/*
Given a string s, partition s such that every substring of the partition is a palindrome.
Return the minimum cuts needed for a palindrome partitioning of s.

Example:
Input: "aab"
Output: 1
Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.
*/

class Solution {
private:
    int solution1(const std::string& s) {
        /* Time-Complexity:     O(N^2)
         * Space-Complexity:    O(N^2)
         */

        const int N = s.size();
        if (not N) {
            return 0;
        }
        
        // is_palindrome[i][j] = true if s[i:j] is a palindrome, false otherwise. 
        // is_palindrome[i][j] = s[i] == s[j] and is_palindrome[i+1][j-1]
        auto is_palindrome = std::vector<std::vector<bool>>(N, std::vector<bool>(N, false));
        // DP[j] = mininum cuts required to partition s[0:j]
        // DP[j] = min{DP[i-1] + 1 | i <= j and is_palindrome[i][j]}
        auto DP = std::vector<int>(N);

        for (int j = 0; j < N; ++j) {
            // considering min cuts to partition s[0:j]
            DP[j] = j; // initial value: DP[j] = length(s[0:j]) - 1
            for (int i = 0; i <= j; ++i) {
                if (s[i] == s[j] and (j - i < 2 or is_palindrome[i+1][j-1])) {
                    // if s[i] matches s[j] and if s[i+1:j-1] is a palindrome
                    // then s[i:j] must also be a palindrome.
                    is_palindrome[i][j] = true;
                    // Can we minimize DP[j] if we decide to make a cut before index i?
                    // Note that if i is beginning of `s` (i.e., if i is zero), then s[i:j] == s[0:]
                    // is a palindrome and there is no need to make a cut and so DP[j] must be zero.
                    DP[j] = i ? std::min(DP[j], DP[i-1] + 1) : 0;
                }
            }
        }
        // We are interested in minimum cuts required to partition s[0:N-1] 
        // i.e., we are interested in DP[N-1]
        return DP[N-1];
    }
public:
    int minCut(string s) {
        return solution1(s);
    }
};
