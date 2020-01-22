/*
You want to build a house on an empty land which reaches all buildings in the shortest amount of distance. You can only move up, down, left and right. You are given a 2D grid of values 0, 1 or 2, where:

Each 0 marks an empty land which you can pass by freely.
Each 1 marks a building which you cannot pass through.
Each 2 marks an obstacle which you cannot pass through.
Example:

Input: [[1,0,2,0,1],[0,0,0,0,0],[0,0,1,0,0]]

1 - 0 - 2 - 0 - 1
|   |   |   |   |
0 - 0 - 0 - 0 - 0
|   |   |   |   |
0 - 0 - 1 - 0 - 0

Output: 7 

Explanation: Given three buildings at (0,0), (0,4), (2,2), and an obstacle at (0,2),
             the point (1,2) is an ideal empty land to build a house, as the total 
             travel distance of 3+3+1=7 is minimal. So return 7.
Note:
There will be at least one building. If it is not possible to build such house according to the above rules, return -1.

*/
class Solution {
private:
    typedef std::pair<int,int> Node;

    const std::vector<std::vector<int>> offsets{{-1,0}, {1,0}, {0,-1}, {0,1}};

    int M,N;

    bool valid(const int i, const int j) {
        return 0 <= i and i < M and 0 <= j and j < N;
    }


    void BFS1(
            const int i,
            const int j,
            std::vector<std::vector<int>>& distance,
            std::vector<std::vector<int>>& reached,
            const std::vector<std::vector<int>>& grid) {
        
        auto seen = std::vector<std::vector<bool>>(M, std::vector<bool>(N, false));
        auto Q = std::queue<Node>();
        Q.push({i, j});
        
        int level = 0;

        while (not Q.empty()) {
            for (int sz = Q.size(); sz; --sz, Q.pop()) {
                const auto i = Q.front().first;
                const auto j = Q.front().second;
                for (const auto& offset : offsets) {
                    const auto m = i + offset[0];
                    const auto n = j + offset[1];
                    if (valid(m, n) and grid[m][n] == 0 and not seen[m][n]) {
                        distance[m][n] += level + 1;
                        ++reached[m][n];
                        seen[m][n] = true;
                        Q.push({m, n});
                    }
                }
            }
            ++level;
        }
    }
            

    int solution1(const std::vector<std::vector<int>>& grid) {
        if (grid.empty()) {
            return -1;
        }
        M = grid.size();
        N = grid[0].size();
        
        auto distance = std::vector<std::vector<int>>(M, std::vector<int>(N, 0));
        auto reached = std::vector<std::vector<int>>(M, std::vector<int>(N, 0));

        int total_buildings = 0;

        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (grid[i][j] == 1) {
                    BFS1(i, j, distance, reached, grid);
                    total_buildings++;
                }
            }
        }

        int shortest = INT_MAX;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (grid[i][j] == 0 and reached[i][j] == total_buildings) {
                    shortest = std::min(shortest, distance[i][j]);
                }
            }
        }

        return shortest == INT_MAX ? -1 : shortest;
    }
public:
    int shortestDistance(vector<vector<int>>& grid) {
        return solution1(grid);
    }
};
