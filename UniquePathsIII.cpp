/*
On a 2-dimensional grid, there are 4 types of squares:
    1 represents the starting square.  There is exactly one starting square.
    2 represents the ending square.  There is exactly one ending square.
    0 represents empty squares we can walk over.
    -1 represents obstacles that we cannot walk over.
Return the number of 4-directional walks from the starting square to the ending square, that walk over every non-obstacle square exactly once.

Example 1:
Input: [[1,0,0,0],[0,0,0,0],[0,0,2,-1]]
Output: 2
Explanation: We have the following two paths: 
1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)

Example 2:
Input: [[1,0,0,0],[0,0,0,0],[0,0,0,2]]
Output: 4
Explanation: We have the following four paths: 
1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2),(2,3)
2. (0,0),(0,1),(1,1),(1,0),(2,0),(2,1),(2,2),(1,2),(0,2),(0,3),(1,3),(2,3)
3. (0,0),(1,0),(2,0),(2,1),(2,2),(1,2),(1,1),(0,1),(0,2),(0,3),(1,3),(2,3)
4. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2),(2,3)

Example 3:
Input: [[0,1],[2,0]]
Output: 0
Explanation: 
There is no path that walks over every empty square exactly once.
Note that the starting and ending square can be anywhere in the grid.

Note:
1 <= grid.length * grid[0].length <= 20
*/

class Solution {
private:
    const std::vector<std::vector<int>> offsets = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int M,N;
    int walkable_cells;
    
    bool valid(const int row, const int col) {
        return 0 <= row and row < M and 0 <= col and col < N;
    }

    int recurse1(const int row, const int col, const int cells_visisted, std::vector<std::vector<int>>& grid) {
        if (not valid(row, col) or grid[row][col] == -1) {
            return 0;
        } else if (grid[row][col] == 2) {
            return cells_visisted == walkable_cells;
        }
        grid[row][col] = -1;
        int paths = 0;
        for (const auto& offset : offsets) {
            paths += recurse1(row + offset[0], col + offset[1], cells_visisted + 1, grid);
        }
        grid[row][col] = 0;
        
        return paths; 
    }

    int solution1(std::vector<std::vector<int>>& grid) {
        M = grid.size();
        N = grid[0].size();
        walkable_cells = 0;
        int start_row = -1;
        int start_col = -1;
        for (int row = 0; row < M; ++row) {
            for (int col = 0; col < N; ++col) {
                if (grid[row][col] == 1) {
                    start_row = row;
                    start_col = col;
                }
                if (grid[row][col] != -1) {
                    ++walkable_cells;
                }
            }
        }
        return recurse1(start_row, start_col, 1, grid);
    }
public:
    int uniquePathsIII(vector<vector<int>>& grid) {
        return solution1(grid);        
    }
};
