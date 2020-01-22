/*
Given strings S and T, find the minimum (contiguous) substring W of S, so that T is a subsequence of W.
If there is no such window in S that covers all characters in T, return the empty string "". 
If there are multiple such minimum-length windows, return the one with the left-most starting index.

Example 1:
Input: 
S = "abcdebdde", T = "bde"
Output: "bcde"
Explanation: 
"bcde" is the answer because it occurs before "bdde" which has the same length.
"deb" is not a smaller window because the elements of T in the window must occur in order.

Note:
    1)  All the strings in the input will only contain lowercase letters.
    2)  The length of S will be in the range [1, 20000].
    3)  The length of T will be in the range [1, 100].
*/
class Solution {
private:
    static const int INF = INT_MAX;
    int M,N;

    int recurse1(
            const int i,
            const int j,
            std::vector<std::vector<int>>& cache,
            const std::string& S,
            const std::string& T) {
        if (j == N) {
            return i;
        } else if (i == M) {
            return INF;
        } else if (cache[i][j] >= 0) {
            return cache[i][j];
        }
        return cache[i][j] = recurse1(i + 1, j + (S[i] == T[j]), cache, S, T);
    }

    std::string solution1(const std::string& S, const std::string& T) {
        /* Time-Complexity:     O(M*N)
         * Space-Complexity:    O(M*N)
         */

        M = S.size();
        N = T.size();

        auto cache = std::vector<std::vector<int>>(M, std::vector<int>(N, -1));
        int left = INF;
        int right;
        int start = 0;
        int end;
        while (start < M and (end = recurse1(start, 0, cache, S, T)) != INF) {
            if (left == INF or end - start < right - left) { 
                left = start; 
                right = end; 
            }
            ++start;
        }

        return left == INF ? "" : S.substr(left, right - left);
    }
public:
    string minWindow(string S, string T) {
        return solution1(S, T); 
    }
};
