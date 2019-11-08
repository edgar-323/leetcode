/*
Given a matrix, and a target, return the number of non-empty submatrices that sum to target.
A submatrix x1, y1, x2, y2 is the set of all cells matrix[x][y] with x1 <= x <= x2 and y1 <= y <= y2.
Two submatrices (x1, y1, x2, y2) and (x1', y1', x2', y2') are different if they have some coordinate that is different: for example, if x1 != x1'.

Example 1:
Input: matrix = [[0,1,0],[1,1,1],[0,1,0]], target = 0
Output: 4
Explanation: The four 1x1 submatrices that only contain 0.

Example 2:
Input: matrix = [[1,-1],[-1,1]], target = 0
Output: 5
Explanation: The two 1x2 submatrices, plus the two 2x1 submatrices, plus the 2x2 submatrix.

Note:
1 <= matrix.length <= 300
1 <= matrix[0].length <= 300
-1000 <= matrix[i] <= 1000
-10^8 <= target <= 10^8
*/

class Solution {
private:
	int solution1(const std::vector<std::vector<int>>& matrix, const int target) {
        /* Time-Complexity:     O(M*N^2)
         * Space-Complexity:    O(M*N)
         */

	    int num_submatrices = 0;

        auto A = matrix;
        const int M = A.size();
        const int N = A[0].size();
        
        for (int i = 0; i < M; ++i) {
            for (int j = 1; j < N; ++j) {
                A[i][j] += A[i][j-1];
            }
        }
        for (int i = 0; i < N; ++i) {
            for (int j = i; j < N; ++j) {
                auto map = std::unordered_map<int,int>();
                map.insert({0, 1});
                int running_sum = 0;
                for (int r = 0; r < M; ++r) {
                    running_sum += A[r][j] - (i ? A[r][i-1] : 0);
                    num_submatrices += map[running_sum - target];
                    map[running_sum]++;
                }
            }
        }
        
        return num_submatrices;
	}
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
  		return solution1(matrix, target);      
    }
};
