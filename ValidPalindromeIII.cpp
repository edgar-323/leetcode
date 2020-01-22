/*
Given a string s and an integer k, find out if the given string is a K-Palindrome or not.
A string is K-Palindrome if it can be transformed into a palindrome by removing at most k characters from it.

Example 1:
Input: s = "abcdeca", k = 2
Output: true
Explanation: Remove 'b' and 'e' characters.

Constraints:
1 <= s.length <= 1000
s has only lowercase English letters.
1 <= k <= s.length
*/

class Solution {
private:
    int N, K;

    bool recurse1(
            const int i, 
            const int j, 
            const int k, 
            std::vector<std::vector<std::vector<int>>>& cache, 
            const std::string& S) {
        if (cache[i][j][k] >= 0) {
            return cache[i][j][k];
        }
        bool is_palindromic = false;
        if (i >= j) {
            is_palindromic = true;
        } else if (S[i] == S[j]) {
            is_palindromic = recurse1(i+1, j-1, k, cache, S);
        } else if (k) {
            is_palindromic = recurse1(i+1, j, k-1, cache, S) or recurse1(i, j-1, k-1, cache, S);
        }
        return cache[i][j][k] = is_palindromic; 
    }

    bool solution1(const std::string& S, const int K) {
        /* Time-Complexity:     O(K * N^2)
         * Space-Complexity:    O(K * N^2)
         */
        // MEMORY LIMIT EXCEEDED
        // Passed All Test Cases But Uses Too Much Memory
        N = S.size();
        auto cache = std::vector<std::vector<std::vector<int>>>(N, std::vector<std::vector<int>>(N, std::vector<int>(K+1, -1))); 
        return recurse1(0, N-1, K, cache, S);
    }

    bool solution2(const std::string& S, const int K) {
        /* Time-Complexity:     O(N^2)
         * Space-Complexity:    O(N^2)
         */
        // EXPLANATION:
        // If the longest palindromic subsequence in S[0:N] is at least length N-K, then the operation is possible.
        N = S.size();
        
        auto DP = std::vector<std::vector<int>>(N, std::vector<int>(N, 0));
        // Length 1
        for (int i = 0; i < N; ++i) {
            DP[i][i] = 1;
        }
        // Length 2
        for (int i = 0; i < N-1; ++i) {
            DP[i][i+1] = S[i] == S[i+1] ? 2 : 1;
        }
        // Length >= 3
        for (int len = 3; len <= N; ++len) {
            for (int i = 0, j = len-1; j < N; ++i, ++j) {
                DP[i][j] =  std::max<int>(
                                {
                                    DP[i][j-1],
                                    DP[i+1][j],
                                    DP[i+1][j-1] + 2*(S[i] == S[j])
                                });
            }
        }

        return DP[0][N-1] >= N-K;
    }
public:
    bool isValidPalindrome(string s, int k) {
        return solution2(s, k);
    }
};
