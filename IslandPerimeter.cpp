/*
You are given a map in form of a two-dimensional integer grid where 1 represents land and 0 represents water.

Grid cells are connected horizontally/vertically (not diagonally). The grid is completely surrounded by water, and there is exactly one island (i.e., one or more connected land cells).

The island doesn't have "lakes" (water inside that isn't connected to the water around the island). One cell is a square with side length 1. The grid is rectangular, width and height don't exceed 100. Determine the perimeter of the island.

Input:
[[0,1,0,0],
 [1,1,1,0],
 [0,1,0,0],
 [1,1,0,0]]

Output: 16

Explanation: The perimeter is the 16 yellow stripes in the image below:
*/

class Solution {
private:
    int M, N;
    int value(const std::vector<std::vector<int>>& grid, const int i, const int j) {
        const bool in_range = i >= 0 and i < M and j >= 0 and j < N;
        return (!in_range or !grid[i][j]) ? 1 : 0;
    }
    int values(const std::vector<std::vector<int>>& grid, const int i, const int j) {
        return value( grid, i-1, j ) + 
                value( grid, i+1, j ) + 
                value( grid, i, j-1 ) + 
                value( grid, i, j+1 );
    }
    int solution1(std::vector<std::vector<int>>& grid) {
        /* 
         * Time-Complexity:     O( M*N )
         * Space-Complexity:    O(  1  )
         * */
        int perimeter = 0;
        M = grid.size();
        if ( !M ) {
            return perimeter;
        }
        N = grid[0].size();
           
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if ( grid[i][j] ) {
                    perimeter += values( grid, i, j );           
                }
            }
        }

        return perimeter; 
    }
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        return solution1( grid );    
    }
};
