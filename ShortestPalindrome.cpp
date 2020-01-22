/*
Given a string s, you are allowed to convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation.

Example 1:
Input: "aacecaaa"
Output: "aaacecaaa"

Example 2:
Input: "abcd"
Output: "dcbabcd"
*/
class Solution {
private:
    /***********************************************************************************************/
    std::string tranform(const std::string& S) {
        const int M = S.size();
        const int N = 2*M + 3;
        auto T = std::string(N, '#');
        T[0] = '^';
        for (int i = 0; i < M; ++i) {
            T[2*i + 2] = S[i];
        }
        T[N-1] = '$';
        return T;
    }

    std::vector<int> manacher(const std::string& S) {
        const auto T = tranform(S);
        const int N = T.size();
        
        auto P = std::vector<int>(N);
        
        int center = 0;
        int right = 0;
        int i_mirror;
        
        P[0] = 0;
        for (int i = 1; i < N-1; ++i) {
            i_mirror = 2*center - i;
            P[i] = right > i ? std::min(right - i, P[i_mirror]) : 0;
            while (T[i+1+P[i]] == T[i-1-P[i]]) {
                ++P[i];
            }
            if (i+P[i] > right) {
                center = i;
                right = i + P[i];
            }
        }
        P[N-1] = 0;

        return P;
    }

    int length_of_longest_palindrome_starting_at_index0(const std::string& S) {
		const auto P = manacher(S);
        const int N = P.size();
        
        int max_len = 0;
        int len = 0;
        int start = 0;
        
        for (int i = 1; i < N-1; ++i) {
            if (len < P[i]) {
                len = P[i];
                start = (i - P[i] - 1) / 2;
                if (start == 0) {
                    max_len = len;
                }
            }
        }
		
		return max_len;
    }

    std::string solution1(std::string& S) {
        /* Time-Complexity:     O(M)
         * Space-Complexity:    O(M)
         *      Where:
         *          M = len(S)
         */
        /* Explanation:
         * We want to find the longest palindrome, whose left endpoint is @ S[0].
         * Why is this?
         * Let 
         *      T = longest palindrome starting at index 0.
         * Then let
         *      Q = S.substr(T.size())
         *  I.e., Q is the part of S that wasn't able to be part of the longest palinrome
         *  that starts at index 0.
         *  Then all we have to do is prepend the reverse of Q to the begginning of S.
         *  This is because we can only prepend to S.
         *
         *  Thus, we leverage Manacher algorithm to find longest palindromes in S (in linear time).
         *  Then, we find the length of the longest palindrome starting at position 0.
         */
        const int max_len = length_of_longest_palindrome_starting_at_index0(S);

        const auto right_half = S.substr((max_len&1) + max_len/2);
        const auto left_half = std::string(right_half.rbegin(), right_half.rend());
        const auto center = max_len&1 ? std::string(1, S[max_len/2]) : "";

        return left_half + center + right_half;
    }
    /***********************************************************************************************/
public:
    string shortestPalindrome(string s) {
        return solution1(s);        
    }
};
