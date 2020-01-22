/*
A group of two or more people wants to meet and minimize the total travel distance. 
You are given a 2D grid of values 0 or 1, where each 1 marks the home of someone in the group. 
The distance is calculated using Manhattan Distance, 
where distance(p1, p2) = |p2.x - p1.x| + |p2.y - p1.y|.

Example:
Input: 
1 - 0 - 0 - 0 - 1
|   |   |   |   |
0 - 0 - 0 - 0 - 0
|   |   |   |   |
0 - 0 - 1 - 0 - 0
Output: 6 
Explanation: Given three people living at (0,0), (0,4), and (2,2):
             The point (0,2) is an ideal meeting point, as the total travel distance 
             of 2+2+2=6 is minimal. So return 6.
*/
class Solution {
private:
    std::vector<int> collect_rows(const std::vector<std::vector<int>>& grid) {
        const int M = grid.size();
        const int N = grid[0].size();
        auto rows = std::vector<int>();
        for (auto row = 0; row < M; ++row) {
            for (auto col = 0; col < N; ++col) {
                if (grid[row][col]) {
                    rows.push_back(row);
                }
            }
        }
        return rows;
    }

    std::vector<int> collect_cols(const std::vector<std::vector<int>>& grid) {
        const int M = grid.size();
        const int N = grid[0].size();
        auto cols = std::vector<int>();
        for (auto col = 0; col < N; ++col) {
            for (auto row = 0; row < M; ++row) {
                if (grid[row][col]) {
                    cols.push_back(col);
                }
            }
        }
        return cols;
    }

    int min_dist(const std::vector<int>& points) {
        int dist = 0;
        int left = 0;
        int right = points.size() - 1;
        while (left < right) {
            dist += points[right--] - points[left++];
        }
        return dist;
    }

    int solution1(const std::vector<std::vector<int>>& grid) {
        /* Time-Complexity:     O(M*N)
         * Space-Complexity:    O(M+N)
         *      Where:
         *          M = len(grid)
         *          N = len(grid[0])
         */
        /* Explanation:
         * https://leetcode.com/problems/best-meeting-point/solution/
         *
         * (I would've never figured this out)
         */
        return  min_dist(collect_rows(grid)) + 
                min_dist(collect_cols(grid));
    }
public:
    int minTotalDistance(vector<vector<int>>& grid) {
        return solution1(grid);       
    }
};
