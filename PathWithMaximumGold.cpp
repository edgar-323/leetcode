/*
In a gold mine grid of size m * n, each cell in this mine has an integer representing the amount of gold in that cell, 0 if it is empty.
Return the maximum amount of gold you can collect under the conditions:
Every time you are located in a cell you will collect all the gold in that cell.
From your position you can walk one step to the left, right, up or down.
You can't visit the same cell more than once.
Never visit a cell with 0 gold.
You can start and stop collecting gold from any position in the grid that has some gold.

Example 1:
Input: grid = [[0,6,0],[5,8,7],[0,9,0]]
Output: 24
Explanation:
[[0,6,0],
 [5,8,7],
 [0,9,0]]
Path to get the maximum gold, 9 -> 8 -> 7.

Example 2:
Input: grid = [[1,0,7],[2,0,6],[3,4,5],[0,3,0],[9,0,20]]
Output: 28
Explanation:
[[1,0,7],
 [2,0,6],
 [3,4,5],
 [0,3,0],
 [9,0,20]]
Path to get the maximum gold, 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7.

Constraints:
1 <= grid.length, grid[i].length <= 15
0 <= grid[i][j] <= 100
There are at most 25 cells containing gold.
*/
class Solution {
private:
    int M,N;

    bool valid(const int i, const int j) {
        return 0 <= i and i < M and 0 <= j and j < N;
    }

    int DFS(const int i, const int j, std::vector<std::vector<int>>& grid) {
        if (not valid(i, j) or not grid[i][j]) {
            return 0;
        }
        const int cell_gold = grid[i][j];
        grid[i][j] = 0;
        const int max_gold = cell_gold + std::max<int>(
                                            {
                                                DFS(i-1, j, grid),
                                                DFS(i+1, j, grid),
                                                DFS(i, j-1, grid),
                                                DFS(i, j+1, grid)
                                             });
        grid[i][j] = cell_gold;

        return max_gold;
    }

    int solution1(std::vector<std::vector<int>>& grid) {
        M = grid.size();
        N = grid[0].size();
        int max_gold = 0;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                max_gold = std::max(max_gold, DFS(i, j, grid));
            }
        }

        return max_gold;
    }

public:
    int getMaximumGold(vector<vector<int>>& grid) {
        return solution1(grid);        
    }
};
