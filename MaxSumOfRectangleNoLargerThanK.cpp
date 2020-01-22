/*
Given a non-empty 2D matrix matrix and an integer k, find the max sum of a rectangle in the matrix such that its sum is no larger than k.

Example:
Input: matrix = [[1,0,1],[0,-2,3]], k = 2
Output: 2 
Explanation: Because the sum of rectangle [[0, 1], [-2, 3]] is 2,
             and 2 is the max number no larger than k (k = 2).

Note:
The rectangle inside the matrix must have an area > 0.
What if the number of rows is much larger than the number of columns?
*/

class Solution {
private:
    int M,N;
    int solution1_column_version(const std::vector<std::vector<int>>& matrix, const int K) {
        int max_sum = INT_MIN;
        for (int col1 = 0; col1 < N; ++col1) {
            auto sums = std::vector<int>(M, 0);
            for (int col2 = col1; col2 < N; ++col2) {
                for (int i = 0; i < M; ++i) {
                    sums[i] += matrix[i][col2];
                }
                auto set = std::set<int>();
                set.insert(0);
                int curr_sum = 0;
                for (const auto& sum : sums) {
                    curr_sum += sum;
                    auto it = set.lower_bound(curr_sum - K); // prev_sum ==> (curr_sum - K <= prev_sum) ==> curr_sum - prev_sum <= K
                    if (it != set.end()) {
                        max_sum = std::max(max_sum, curr_sum - *it);
                    }
                    set.insert(curr_sum);
                }
            }
        }
             
        return max_sum;          
    }
    int solution1_row_version(const std::vector<std::vector<int>>& matrix, const int K) {
        int max_sum = INT_MIN;
        for (int row1 = 0; row1 < M; ++row1) {
            auto sums = std::vector<int>(N, 0);
            for (int row2 = row1; row2 < M; ++row2) {
                for (int j = 0; j < N; ++j) {
                    sums[j] += matrix[row2][j];
                }
                auto set = std::set<int>();
                set.insert(0);
                int curr_sum = 0;
                for (const auto& sum : sums) {
                    curr_sum += sum;
                    auto it = set.lower_bound(curr_sum - K);
                    if (it != set.end()) {
                        max_sum = std::max(max_sum, curr_sum - *it);
                    }
                    set.insert(curr_sum);
                }
            }
        }
        
        return max_sum;
    }
    int solution1(const std::vector<std::vector<int>>& matrix, const int K) {
        /* Time-Complexity:     O(M*N*min{M,N}*log(max{M,N}))
         * Space-Complexity:    O(M*N)
         */
        // Explanation:
        // First read https://www.quora.com/Given-an-array-of-integers-A-and-an-integer-k-find-a-subarray-that-contains-the-largest-sum-subject-to-a-constraint-that-the-sum-is-less-than-k
        // Which explains how you would tackle this problem in the 1D setting.
        // We will apply this solution to this 2D case setting as follows:
        // Choose two columns (col1, col2).
        M = matrix.size();
        if (not M) {
            return 0;
        }
        N = matrix[0].size();
        return  M < N ? solution1_row_version(matrix, K) : solution1_column_version(matrix, K);
    }
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
     	return solution1(matrix, k);   
    }
};
