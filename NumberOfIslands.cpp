/*
Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Example 1:
Input:
11110
11010
11000
00000
Output: 1

Example 2:
Input:
11000
11000
00100
00011
Output: 3
*/

class Solution {
private:
    bool valid(int i, int j, int M, int N) {
        return i >= 0 && i < M && j >= 0 && j < N;
    }
    
    void eliminateIsland(std::vector<std::vector<char>>&  grid, 
                         int i, int j, int M, int N) {
        if (!valid(i, j, M, N) || grid[i][j] == '0') {
            return;
        }
        grid[i][j] = '0';
        eliminateIsland(grid, i-1, j, M, N);
        eliminateIsland(grid, i+1, j, M, N);
        eliminateIsland(grid, i, j-1, M, N);
        eliminateIsland(grid, i, j+1, M, N);
    }
    
    int solution1(std::vector<std::vector<char>>& grid) {
        /*
        Time-Complexity:    O(M*N)
        Space-Complexity:   O(M*N)
        */
        int islands = 0;
        const int M = grid.size();
        if (M == 0) {
            return islands;
        }
        const int N = grid[0].size();
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (grid[i][j] == '1') {
                    eliminateIsland(grid, i, j, M, N);
                    ++islands;
                }
            }
        }
        return islands;
    }
    
public:
    int numIslands(vector<vector<char>>& grid) {
        return solution1(grid);
    }
};
