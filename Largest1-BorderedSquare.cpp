/*
Given a 2D grid of 0s and 1s, return the number of elements in the largest square subgrid that has all 1s on its border, or 0 if such a subgrid doesn't exist in the grid.
 
Example 1:
Input: grid = [[1,1,1],[1,0,1],[1,1,1]]
Output: 9

Example 2:
Input: grid = [[1,1,0,0]]
Output: 1

Constraints:
1 <= grid.length <= 100
1 <= grid[0].length <= 100
grid[i][j] is 0 or 1
*/

class Solution {
private:
	int solution1(const std::vector<std::vector<int>>& grid) {
        /* Time-Complexity:     O(M * N * min{M, N})
         * Space-Complexity:    O(M * N) 
         */
        const int M = grid.size();
        const int N = grid[0].size();
        
        // horizontal[i][j] = # of 1's horizontally ending @ grid[i][j]
        auto horizontal     = std::vector<std::vector<int>>(M, std::vector<int>(N, 0));
        // vertical[i][j]   = # of 1's vertically ending @ grid[i][j]
        auto vertical       = std::vector<std::vector<int>>(M, std::vector<int>(N, 0));
        // largest_side     = largest square side in grid
        int largest_side    = 0;
        
        // Populate horizontal[]
        for (int i = 0; i < M; ++i) {
            horizontal[i][0] = grid[i][0];
            for (int j = 1; j < N; ++j) {
                if (not grid[i][j]) {
                    continue;
                }
                horizontal[i][j] = 1 + horizontal[i][j-1];
            }
        }
        // Populate vertical[]
        for (int j = 0; j < N; ++j) {
            vertical[0][j] = grid[0][j];
            for (int i = 1; i < M; ++i) {
                if (not grid[i][j]) {
                   continue;
                }
                vertical[i][j] = 1 + vertical[i-1][j];
            }
        }
        // Update largest_side
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (not grid[i][j]) {
                    continue;
                }
                // Best square we can possibly wish for has side length of `dist`
                const int dist = std::min(horizontal[i][j], vertical[i][j]);
                for (int k = dist; k >= 1; --k) {
                    if (vertical[i][j+1-k] >= k and horizontal[i+1-k][j] >= k) {
                        largest_side = std::max(largest_side, k);
                        break;
                    }
                }
            }
        }

        return largest_side * largest_side; 
	}
public:
    int largest1BorderedSquare(vector<vector<int>>& grid) {
  		return solution1(grid);      
    }
};
