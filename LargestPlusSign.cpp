/*
In a 2D grid from (0, 0) to (N-1, N-1), every cell contains a 1, except those cells in the given list mines which are 0. What is the largest axis-aligned plus sign of 1s contained in the grid? Return the order of the plus sign. If there is none, return 0.

An "axis-aligned plus sign of 1s of order k" has some center grid[x][y] = 1 along with 4 arms of length k-1 going up, down, left, and right, and made of 1s. This is demonstrated in the diagrams below. Note that there could be 0s or 1s beyond the arms of the plus sign, only the relevant area of the plus sign is checked for 1s.

Examples of Axis-Aligned Plus Signs of Order k:

Order 1:
000
010
000

Order 2:
00000
00100
01110
00100
00000

Order 3:
0000000
0001000
0001000
0111110
0001000
0001000
0000000
Example 1:

Input: N = 5, mines = [[4, 2]]
Output: 2
Explanation:
11111
11111
11111
11111
11011
In the above grid, the largest plus sign can only be order 2.  One of them is marked in bold.
Example 2:

Input: N = 2, mines = []
Output: 1
Explanation:
There is no plus sign of order 2, but there is of order 1.
Example 3:

Input: N = 1, mines = [[0, 0]]
Output: 0
Explanation:
There is no plus sign, so return 0.
Note:

N will be an integer in the range [1, 500].
mines will have length at most 5000.
mines[i] will be length 2 and consist of integers in the range [0, N-1].
(Additionally, programs submitted in C, C++, or C# will be judged with a slightly smaller time limit.)
*/

class Solution {
private:
	int solution1(const int N, const std::vector<std::vector<int>>& mines) {
        /* Time-Complexity:     O(N^2)
         * Space-Complexity:    O(N^2)
         */
        int max_order = 0;

        auto grid = std::vector<std::vector<int>>(N, std::vector<int>(N, 1));
        for (const auto& mine : mines) {
            grid[mine[0]][mine[1]] = 0;
        }
        auto top    = std::vector<std::vector<int>>(N, std::vector<int>(N, 0));
        auto down   = std::vector<std::vector<int>>(N, std::vector<int>(N, 0));
        auto left   = std::vector<std::vector<int>>(N, std::vector<int>(N, 0));
        auto right  = std::vector<std::vector<int>>(N, std::vector<int>(N, 0));
        // Calculate left[] and right[]
        for (int i = 0; i < N; ++i) {
            left[i][0]      = grid[i][0];
            right[i][N-1]   = grid[i][N-1];
            for (int j = 1; j < N; ++j) {
                if (grid[i][j]) {
                    left[i][j]      = 1 + left[i][j-1];
                }
                if (grid[i][N-1-j]) {
                    right[i][N-1-j] = 1 + right[i][N-j];
                }
            }
        }
        // Calculate top[] and down[]
        for (int j = 0; j < N; ++j) {
            top[0][j]       = grid[0][j];
            down[N-1][j]    = grid[N-1][j];
            for (int i = 1; i < N; ++i) {
                if (grid[i][j]) {
                    top[i][j]       = 1 + top[i-1][j];
                }
                if (grid[N-1-i][j]) {
                    down[N-1-i][j]  = 1 + down[N-i][j];
                }
            }
        }
        // Calculate maximum order
        for (int i = 0; i < N; ++i) {
           for (int j = 0; j < N; ++j) {
                if (not grid[i][j]) {
                    continue;
                }
                const int order = 1 + std::min<int>(
                                        {
                                            j > 0   ?   left[i][j-1]    : 0, 
                                            j < N-1 ?   right[i][j+1]   : 0, 
                                            i > 0   ?   top[i-1][j]     : 0, 
                                            i < N-1 ?   down[i+1][j]    : 0
                                        });
                max_order = std::max<int>({max_order, order});
           }
        }
        return max_order;
	}
public:
    int orderOfLargestPlusSign(int N, vector<vector<int>>& mines) {
  		return solution1(N, mines);      
    }
};
