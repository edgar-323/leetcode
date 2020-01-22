/*
Given two integer arrays arr1 and arr2, return the minimum number of operations (possibly zero) needed to make arr1 strictly increasing.
In one operation, you can choose two indices 0 <= i < arr1.length and 0 <= j < arr2.length and do the assignment arr1[i] = arr2[j].
If there is no way to make arr1 strictly increasing, return -1.

Example 1:
Input: arr1 = [1,5,3,6,7], arr2 = [1,3,2,4]
Output: 1
Explanation: Replace 5 with 2, then arr1 = [1, 2, 3, 6, 7].

Example 2:
Input: arr1 = [1,5,3,6,7], arr2 = [4,3,1]
Output: 2
Explanation: Replace 5 with 3 and then replace 3 with 4. arr1 = [1, 3, 4, 6, 7].

Example 3:
Input: arr1 = [1,5,3,6,7], arr2 = [1,6,3,3]
Output: -1
Explanation: You can't make arr1 strictly increasing.

Constraints:
1 <= arr1.length, arr2.length <= 2000
0 <= arr1[i], arr2[i] <= 10^9
*/

class Solution {
private:
    int M,N;
    /*****************************************************************************************************************************/
    int solution1(std::vector<int>& A, std::vector<int>& B) {
        /* Time-Complexity:     O(M*N)
         * Space-Complexity:    O(M*N)
         */
        // Credit Goes To @chenbai10

        // EXPLANATION:
        // Here is DP transition formula:
        //      F[i, j] = minimum operations required to keep A[0..i] strictly increasing, if we replace A[i] with B[j]
        //      G[i]    = minimum operations required to keep A[0..i] strictly increasing, if we DON'T replace A[i]
        //
        // Then:
        // F[i, j] = min {
        //                  F[i-1, j-1] + 1,    if j > 0,               // Case where we replaced A[i-1] with B[j-1], and since B[j-1] < B[j], then it is possible
        //                  G[i-1]      + 1,    if A[i - 1] < B[j]      // Case Where we didn't replce A[i-1] but we want to replace A[i] with B[j], but we must ensure A[i-1] < B[j] (to keep A[] S.I.)
        //               }
        //
        // G[i] = min {
        //          G[i-1],     if A[i] > A[i - 1],                     // Case where we dont want to replace A[i], and we also didn't replace A[i-1], but we must ensure A[i-1] < A[i]
        //          F[i-1, j],  for any j where B[j] < A[i]             // Case where we dont want to replace A[i], but we replaced A[i-1] with B[j] (for some j), but we must ensure A[i] > B[j]
        //        }

        // Sort B[] and ensure it contains only unique elements
        std::sort(B.begin(), B.end());
        B.erase(std::unique(B.begin(), B.end()), B.end());
        
        M = A.size();
        N = B.size();

        auto F = std::vector<std::vector<int>>(M, std::vector<int>(N, INT_MAX));
        auto G = std::vector<int>(M, INT_MAX);
        
        // If we replace A[0] with B[j] (for any j) then we did 1 operation
        for (int j = 0; j < N; ++j) {
            F[0][j] = 1;
        }
        // We don't A[0] (no operations needed)
        G[0] = 0;
        // General Cases
        for (int i = 1; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                F[i][j] = std::min<int>(
                                {
                                    j > 0 and F[i-1][j-1] < INT_MAX     ?   F[i-1][j-1] + 1 : INT_MAX,
                                    A[i-1] < B[j] and G[i-1] < INT_MAX  ?   G[i-1]      + 1 : INT_MAX
                                });
                G[i]    = std::min<int>(
                                {
                                    G[i],
                                    A[i-1] < A[i]                       ?   G[i-1]          : INT_MAX,
                                    A[i] > B[j]                         ?   F[i-1][j]       : INT_MAX
                                });
            }
        }

        // G[M-1] enures A[] is SI
        // F[M-1][*] also ensures A[] is SI
        // So we are interested in min{ G[M-1], F[M-1][*] }
        const int min_ops = std::min( G[M-1], *std::min_element(F[M-1].begin(), F[M-1].end()));
        
        return min_ops == INT_MAX ? -1 : min_ops;
    }
    /*****************************************************************************************************************************/
    int*** cache2;
    void init_cache2() {
        cache2 = new int**[M+1];
        for (int i = 0; i <= M; ++i) {
            cache2[i] = new int*[N+1];
            for (int j = 0; j <= N; ++j) {
                cache2[i][j] = new int[3]();
            }
        }
    }
    void destroy_cache2() {
        for (int i = 0; i <= M; ++i) {
            for (int j = 0; j <= N; ++j) {
                delete[] cache2[i][j];
            }
            delete[] cache2[i];
        }
        delete[] cache2;
    }
    bool in_cache2(const int i, const int j, const int k) {
        return cache2[i][j][k]; 
    }
    int set_cache2(const int i, const int j, const int k, const int min_ops) {
        return cache2[i][j][k] = min_ops;
    }
    int recurse2(const int i, const int j, const int k, const std::vector<int>& A, const std::vector<int>& B) {
        if (in_cache2(i, j, k)) {
            return cache2[i][j][k];
        }

        int min_ops;
        if (i == M) {
            min_ops = 1;
        } else {
            const int prev_val = k == 0 ? A[i-1] : k == 1 ? B[j-1] : INT_MIN;
            int n = N;
            int left = j;
            int right = N;
            while (left <= right) {
                const int mid = left + (right - left) / 2;
                if (mid == N) {
                    break;
                } else if (prev_val >= B[mid]) {
                    left    = left == mid   ? mid+1 : mid;
                } else if (mid > j and prev_val < B[mid-1]) {
                    right   = right == mid  ? mid-1 : mid;
                } else {
                    n = mid;
                    break;
                }
            }
            min_ops = std::min<int>(
                            {
                                N+1,
                                prev_val < A[i] ? recurse2(i+1, j, 0, A, B)         : N+1,
                                n < N           ? recurse2(i+1, n+1, 1, A, B) + 1   : N+1
                            });
        }
        
        return set_cache2(i, j, k, min_ops);
    }
    int solution2(std::vector<int>& A, std::vector<int>& B) {
        /* Time-Complexity:     O(M*N*log(N))
         * Space-Complexity:    O(M*N)
         */
        M = A.size();
        N = B.size();
          
        std::sort(B.begin(), B.end());         
        init_cache2();
        const int min_ops = recurse2(0, 0, 2, A, B);
        destroy_cache2();   
        
        return min_ops == N+1 ? -1 : min_ops - 1;
    }
    /*****************************************************************************************************************************/
public:
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
  		return solution2(arr1, arr2);      
    }
};
