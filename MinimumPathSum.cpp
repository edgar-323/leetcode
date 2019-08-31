/*
Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.
Note: You can only move either down or right at any point in time.

Example:
Input:
[
  [1,3,1],
  [1,5,1],
  [4,2,1]
]
Output: 7
Explanation: Because the path 1→3→1→1→1 minimizes the sum.
*/

class Solution {
private:
    int solution1(vector<vector<int>>& grid) {
        /*
        Time-Complexity:    O(M * N) 
        Space-Complexity:   O(1)
        */
        const int M = grid.size();
        if (M == 0) {
            return 0;
        }
        const int N = grid[0].size();
        if (N == 0) {
            return 0;
        }
        for (int i = 1; i < M; ++i) {
            grid[i][0] += grid[i-1][0];
        }
        for (int j = 1; j < N; ++j) {
            grid[0][j] += grid[0][j-1];
        }
        for (int i = 1; i < M; ++i) {
            for (int j = 1; j < N; ++j) {
                grid[i][j] += min(grid[i-1][j], grid[i][j-1]);
            }
        }
        return grid[M-1][N-1];
    }
    
public:
    int minPathSum(vector<vector<int>>& grid) {
        return solution1(grid);
    }
};
