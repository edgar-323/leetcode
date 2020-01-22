/*
Given two integer arrays A and B, return the maximum length of an subarray that appears in both arrays.

Example 1:
Input:
A: [1,2,3,2,1]
B: [3,2,1,4,7]
Output: 3
Explanation: 
The repeated subarray with maximum length is [3, 2, 1].

Note:
1 <= len(A), len(B) <= 1000
0 <= A[i], B[i] < 100
*/

class Solution {
private:
    int solution1(const std::vector<int>& A, const std::vector<int>& B) {
        /* Time-Complexity:     O(M*N)
         * Space-Complexity:    O(M*N)
         */
        int max_len = 0;

        const int M = A.size();
        const int N = B.size();
        
        auto DP = std::vector<std::vector<int>>(M+1, std::vector<int>(N+1, 0));
        for (int i = M-1; i >= 0; --i) {
            for (int j = N-1; j >= 0; --j) {
                if (A[i] == B[j]) {
                    DP[i][j] = 1 + DP[i+1][j+1];
                    max_len = std::max(max_len, DP[i][j]);
                }
            }
        }

        return max_len;
    }
public:
    int findLength(vector<int>& A, vector<int>& B) {
  		return solution1(A, B);      
    }
};
