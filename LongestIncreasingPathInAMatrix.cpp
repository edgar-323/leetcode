/*
Given an integer matrix, find the length of the longest increasing path.
From each cell, you can either move to four directions: left, right, up or down. You may NOT move diagonally or move outside of the boundary (i.e. wrap-around is not allowed).

Example 1:
Input: nums = 
[
  [9,9,4],
  [6,6,8],
  [2,1,1]
] 
Output: 4 
Explanation: The longest increasing path is [1, 2, 6, 9].

Example 2:
Input: nums = 
[
  [3,4,5],
  [3,2,6],
  [2,2,1]
] 
Output: 4 
Explanation: The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.
*/

class Solution {
private:
    int M,N;
    std::vector<std::vector<int>> offsets;

    int valid(const int i, const int j) {
        return 0 <= i and i < M and 0 <= j and j < N;
    }

    int visit(
            const int i, 
            const int j, 
            std::vector<std::vector<int>>& LIP,
            const std::vector<std::vector<int>>& grid) {
        if (LIP[i][j]) {
            return LIP[i][j];
        }
        int longest_path = 1;
        for (const auto& offset : offsets) {
            const auto i2 = i + offset[0];
            const auto j2 = j + offset[1];
            if (valid(i2, j2) and grid[i][j] < grid[i2][j2]) {
                longest_path = std::max(longest_path, 1 + visit(i2, j2, LIP, grid));
            }
        }

        return LIP[i][j] = longest_path;
    }

    int solution1(const std::vector<std::vector<int>>& grid) {
        if (grid.empty()) {
            return 0;
        }
        offsets = std::vector<std::vector<int>>{{-1,0},{1,0},{0,-1},{0,1}};
        M = grid.size();
        N = grid[0].size();    
        auto LIP = std::vector<std::vector<int>>(M, std::vector<int>(N, 0));
        
        int longest_path = 0;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                longest_path = std::max(longest_path, visit(i, j, LIP, grid));
            }
        }
        
        return longest_path;  
    }
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        return solution1(matrix); 
    }
};
