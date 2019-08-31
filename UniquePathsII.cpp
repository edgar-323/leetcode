/*
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
The robot can only move either down or right at any point in time. 
The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).
Now consider if some obstacles are added to the grids. 
How many unique paths would there be?
An obstacle and empty space is marked as 1 and 0 respectively in the grid.
Note: m and n will be at most 100.

Example 1:
Input:
[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
Output: 2
Explanation:
There is one obstacle in the middle of the 3x3 grid above.
There are two ways to reach the bottom-right corner:
1. Right -> Right -> Down -> Down
2. Down -> Down -> Right -> Right
*/

class Solution {
private:
    int solution1(const std::vector<std::vector<int>>& obstacleGrid) {
        /* Time-Complexity:     O( M*N )
         * Space-Complexity:    O( M*N )
         * */
        const int M = grid.size();
        const int N = M ? grid[0].size() : 0;
        if (!M or !N or grid[0][0]) {
            return 0;
        }

        std::vector<std::vector<unsigned long long>> DP( M, std::vector<unsigned long long>( N, 0 ) );
        
        DP[0][0] = 1;
        for (int i = 1; i < M; ++i) {
            DP[i][0] = grid[i][0] ? 0 : DP[i-1][0];
        }
        for (int j = 1; j < N; ++j) {
            DP[0][j] = grid[0][j] ? 0 : DP[0][j-1];
        }
        for (int i = 1; i < M; ++i) {
            for (int j = 1; j < N; ++j) {
                DP[i][j] = grid[i][j] ? 0 : DP[i-1][j] + DP[i][j-1]; 
            }
        }
        
        return DP[M-1][N-1];
    }
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        return solution1( obstacleGrid );    
    }
};
