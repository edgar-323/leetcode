/*
Find the length of the longest substring T of a given string (consists of lowercase letters only) such that every character in T appears no less than k times.

Example 1:

Input:
s = "aaabb", k = 3

Output:
3

The longest substring is "aaa", as 'a' is repeated 3 times.
Example 2:

Input:
s = "ababbc", k = 2

Output:
5

The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.
*/
class Solution {
private:
    static const int ALPH_SZ = 26;

    int index(const char c) {
        return c - 'a';
    }

    int solution1(const std::string& S, const int K) {
        /* Time-Complexity:     O(ALPH_SZ * N)
         * Space-Complexity:    O(ALPH_SZ)
         */
        /* Explanation:
         * This problem seems nearly impossible to do by considering simple (left, right) window.
         * This is because even if current window is valid, the intro of a new character may break
         * our window and it is not known how we should adust (left, right).
         * There is a clever "brute-force" way to solve this:
         * Suppose we are interested in windows (left, right) where the # of unique characters
         * is EXACTLY D and every character in that window has frequency AT LEAST K.
         * Then we know that (left, right) is a valid window.
         * Now, we know that D follows the constraint: 1 <= D <= ALPH_SZ.
         * Therefore, we can look for valid windows over all values of D and update our max_window
         * in this manner.
         * This way we know that we considered every possible valid window.
         *
         */
        const int N = S.size();
        int max_window = 0;
        auto count = std::array<int,ALPH_SZ>();
        
        for (int D = 1; D <= ALPH_SZ; ++D) {
            std::fill(count.begin(), count.end(), 0);
            int unique = 0;
            int left = 0;
            int right = 0;
            int num_unique_with_freq_at_least_K = 0;
            while (right < N) {
                if (unique <= D) {
                    const auto c = index(S[right++]);
                    if (not count[c]++) {
                        ++unique;
                    }
                    if (count[c] == K) {
                        ++num_unique_with_freq_at_least_K;
                    }
                } else {
                    // Greater than D unique chars -> let's increment left until we reduce them
                    const auto c = index(S[left++]);
                    if (count[c] == K) {
                        --num_unique_with_freq_at_least_K;
                    }
                    if (not --count[c]) {
                        --unique;
                    }
                }
                if (unique == D and num_unique_with_freq_at_least_K == D) {
                    max_window = std::max(max_window, right - left);
                }
            }
        }

        return max_window;
    }
public:
    int longestSubstring(string s, int k) {
        return solution1(s, k);        
    }
};
