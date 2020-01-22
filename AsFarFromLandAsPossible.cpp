/*
Given an N x N grid containing only values 0 and 1, where 0 represents water and 1 represents land, find a water cell such that its distance to the nearest land cell is maximized and return the distance.
The distance used in this problem is the Manhattan distance: the distance between two cells (x0, y0) and (x1, y1) is |x0 - x1| + |y0 - y1|.
If no land or water exists in the grid, return -1.

Example 1:
Input: [[1,0,1],[0,0,0],[1,0,1]]
Output: 2
Explanation: 
The cell (1, 1) is as far as possible from all the land with distance 2.

Example 2:
Input: [[1,0,0],[0,0,0],[0,0,0]]
Output: 4
Explanation: 
The cell (2, 2) is as far as possible from all the land with distance 4.

Note:
1 <= grid.length == grid[0].length <= 100
grid[i][j] is 0 or 1
*/
class Solution {
private:
    int N;
    
    bool valid(const int i, const int j) {
        return 0 <= i and i < N and 0 <= j and j < N;
    }

    int solution1(const std::vector<std::vector<int>>& grid) {
        /* Time-Complexity:     O(N^2)
         * Space-Complexity:    O(N^2)
         */
        // Explanation (Breadth-First-Search):
        // Initiate BFS as follows:
        //  1)  Push all land cells into Queue (also maintain seen[][] table).
        //  2)  Visit all adjacent water cells until the Queue is empty (make sure to increment distance appropriately).
        //  3)  Return `dist - 1` because the furthest cell(s) increment the distance one additonial time during the BFS process.

        N = grid.size();
        auto seen = std::vector<std::vector<bool>>(N, std::vector<bool>(N, false));  
        auto Q = std::queue<std::pair<int,int>>();
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (grid[i][j]) {
                    Q.push({i,j});
                    seen[i][j] = true;
                }
            }
        }
        
        if (Q.size() == 0 or Q.size() == N*N) {
            // all water cells or all land cells 
            return -1;
        }

        int dist = 0;
        
        while (not Q.empty()) {
            for (int _ = Q.size(); _; --_, Q.pop()) {
                const auto i = Q.front().first;
                const auto j = Q.front().second;
                // top
                if (valid(i-1, j) and not seen[i-1][j]) {
                    Q.push({i-1, j});
                    seen[i-1][j] = true;
                }
                // bottom
                if (valid(i+1, j) and not seen[i+1][j]) {
                    Q.push({i+1,j});
                    seen[i+1][j] = true;
                }
                // left
                if (valid(i, j-1) and not seen[i][j-1]) {
                    Q.push({i,j-1});
                    seen[i][j-1] = true;
                }
                // right
                if (valid(i, j+1) and not seen[i][j+1]) {
                    Q.push({i,j+1});
                    seen[i][j+1] = true;
                }
            }
            ++dist;
        }

        return dist - 1;
    }
public:
    int maxDistance(vector<vector<int>>& grid) {
        return solution1(grid);       
    }
};
