/*
You are given a map of a server center, represented as a m * n integer matrix grid, where 1 means that on that cell there is a server and 0 means that it is no server. Two servers are said to communicate if they are on the same row or on the same column.

Return the number of servers that communicate with any other server.

Example 1:
Input: grid = [[1,0],[0,1]]
Output: 0
Explanation: No servers can communicate with others.

Example 2:
Input: grid = [[1,0],[1,1]]
Output: 3
Explanation: All three servers can communicate with at least one other server.

Example 3:
Input: grid = [[1,1,0,0],[0,0,1,0],[0,0,1,0],[0,0,0,1]]
Output: 4
Explanation: The two servers in the first row can communicate with each other. The two servers in the third column can communicate with each other. The server at right bottom corner can't communicate with any other server.

Constraints:
m == grid.length
n == grid[i].length
1 <= m <= 250
1 <= n <= 250
grid[i][j] == 0 or 1
*/
class Solution {
private:
	int solution1(std::vector<std::vector<int>>& grid) {
        /* Time-Complexity:     O(M*N)
         * Space-Complexity:    O(M + N) (if allowed to modify input else O(M*N))
         */
        // EXPLANATION:
        // Compute:
        //  row[i] = # of servers @ ith row
        //  col[i] = # of columns @ jth column
        // 
        // The above arrays will allow us to discard isolated servers (servers which
        // cannot communicate with any other servers) from the grid and thus we will
        // be left with machines which can communicate with other machines, so once
        // the grid is in this state, we return the total number of machines left.
        //
        // In order to eliminate isolated machines, we go through the grid.
        // Suppose there is a machine @ grid[i][j].
        // If this is the only machine on the ith row and the only machine on the jth column
        // (row[i] == 1 and col[j] == 1), then it is, by definition, an isolated machine, and
        // we eliminate it by setting: 
        //                  grid[i][j] = 0;
        const int M = grid.size();
        const int N = grid[0].size();
        
        auto row = std::vector<int>(M, 0);
        auto col = std::vector<int>(N, 0);
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                row[i] += grid[i][j];
            }
        }
        for (int j = 0; j < N; ++j) {
            for (int i = 0; i < M; ++i) {
                col[j] += grid[i][j];
            }
        }
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (row[i] <= 1 and col[j] <= 1) {
                    grid[i][j] = 0;
                }
            }
        } 
        int total_comms = 0;
        for (int i = 0; i < M; ++i) {
            total_comms += std::accumulate(grid[i].begin(), grid[i].end(), 0);
        }

        return total_comms;
    }
public:
    int countServers(vector<vector<int>>& grid) {
  		return solution1(grid);
    }
};
