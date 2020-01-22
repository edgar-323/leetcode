/*
Given a string s that consists of only uppercase English letters, you can perform at most k operations on that string.
In one operation, you can choose any character of the string and change it to any other uppercase English character.
Find the length of the longest sub-string containing all repeating letters you can get after performing the above operations.
Note:
Both the string's length and k will not exceed 10^4.

Example 1:
Input:
s = "ABAB", k = 2
Output:
4
Explanation:
Replace the two 'A's with two 'B's or vice versa.

Example 2:
Input:
s = "AABABBA", k = 1
Output:
4
Explanation:
Replace the one 'A' in the middle with 'B' and form "AABBBBA".
The substring "BBBB" has the longest repeating letters, which is 4.
*/
class Solution {
private:
    static const int ALPH_SZ = 26;

    int index(const char c) {
        return c - 'A';
    }

    int solution1(const std::string& S, const int K) {
        const int N = S.size();

        auto count = std::vector<int>(ALPH_SZ, 0);

        int left = 0;
        // max_count will keep track of biggest frequency in S[left:right]
        // I.e., if some character c appears the most in S[left:right], then
        // max_count will keep track of the number of appearances it made.
        // Let, L = window_length(left, right).
        // c1 has max frequency, and it can make at most k changes.
        // If there are more than k characters in S[left:right] s.t. c2 != c1
        // then, the current window is not valid, so we need to update the window
        // until L - max_count <= K (at most K modifications).
        // We do this by updating left endpoint.
        int max_count = 0;
        int max_len = 0;

        for (int right = 0; right < N; ++right) {
            max_count = std::max( max_count, ++count[index(S[right])] );
            
            while ((1 + right - left) - max_count > K) {
                --count[index(S[left++])];
            }

            max_len = std::max( max_len, 1 + right - left );
        }

        return max_len;
    }

public:
    int characterReplacement(string s, int k) {
        return solution1(s, k);
    }
};
