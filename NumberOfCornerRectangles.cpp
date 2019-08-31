/*
Given a grid where each entry is only 0 or 1, find the number of corner rectangles.
A corner rectangle is 4 distinct 1's on the grid that form an axis-aligned rectangle. 
Note that only the corners need to have the value 1. Also, all four 1s used must be distinct.

Example 1:
Input: grid = 
[[1, 0, 0, 1, 0],
 [0, 0, 1, 0, 1],
 [0, 0, 0, 1, 0],
 [1, 0, 1, 0, 1]]
Output: 1
Explanation: There is only one corner rectangle, with corners grid[1][2], grid[1][4], grid[3][2], grid[3][4].

Example 2:
Input: grid = 
[[1, 1, 1],
 [1, 1, 1],
 [1, 1, 1]]
Output: 9
Explanation: There are four 2x2 rectangles, four 2x3 and 3x2 rectangles, and one 3x3 rectangle.

Example 3:
Input: grid = 
[[1, 1, 1, 1]]
Output: 0
Explanation: Rectangles must have four distinct corners.

Note:
The number of rows and columns of grid will each be in the range [1, 200].
Each grid[i][j] will be either 0 or 1.
The number of 1s in the grid will be at most 6000.
*/

class Solution {
private:
    int solution1(const std::vector<std::vector<int>>& grid) {
        /* Time-Complexity:     O( (M*N)^2 )
         * Space-Complexity:    O(    1    )
         * */
        /* EXPLANATION: 
         * Consider all possible rectangles.
         * For each given rectangle, check if its corners are non-zero.
         * If so, increment `rectangles`.
         * */
        const int M = grid.size();
        const int N = M ? grid[0].size() : 0;
        if (!M or !N) {
           return 0;
        } 
       
        int rectangles = 0;

        for (int top = 0; top < M-1; ++top) {
            for (int left = 0; left < N-1; ++left) {
                for (int bot = top+1; bot < M; ++bot) {
                    for (int right = left+1; right < N; ++right) {
                        if (grid[top][left]     and
                            grid[top][right]    and
                            grid[bot][left]     and
                            grid[bot][right]) {
                            ++rectangles;
                        }
                    }
                }
            }
        }

        return rectangles;
    }

    int solution2(const std::vector<std::vector<int>>& grid) {
        /* Time-Complexity:     O( M * N^2 )
         * Space-Complexity:    O(   N^2   )
         * */ 
        /* EXPLANATION:
         * For each row in grid, we search for all pairs 
         *      (row[left], row[right])
         * such that row[left] and row[right] are nonzero.
         * This pair forms a base of a rectangle.
         * Let's call this pair `base`.
         * ...
         * */
        const int M = grid.size();
        const int N = M ? grid[0].size() : 0;
        if (!M or !N) {
            return 0;
        }

        int rectangles = 0;
        std::unordered_map<int,int> count;
        
        for (const auto& row : grid) {
            for (int left = 0; left < N; ++left) {
                if (row[left]) {
                    for (int right = left+1; right < N; ++right) {
                        if (row[right]) {
                            int pos = left*200 + right;
                            rectangles += count[pos];
                            ++count[pos];
                        }
                    }
                }
            }
        }

        return rectangles;
    }

    int solution3(const std::vector<std::vector<int>>& grid) {
        /* Time-Complexity:     O( )
         * Space-Complexity:    O( )
         *
         * */

        const int M = grid.size();
        const int N = M ? grid[0].size() : 0;
        if (!M or !N) {
            return 0;
        }

        int rectangles = 0;
        
        

        return rectangles;
    }
public:
    int countCornerRectangles(vector<vector<int>>& grid) {
        return solution2( grid );     
    }
};
