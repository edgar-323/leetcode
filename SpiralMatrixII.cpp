/*
Given a positive integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.

Example: 

Input: 1
Output:
[
 [ 1 ]
]

Example: 

Input: 2
Output:
[
 [ 1, 2 ], 
 [ 4, 3 ]
]

Example:

Input: 3
Output:
[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]

Example: 

Input: 4
Output:
[
 [ 1, 2, 3, 4 ],
 [ 
]
*/

class Solution {
    private:
        std::vector<std::vector<int> > solution1(const int N) {
            /* 
             * Time-Complexity:     O(N^2) 
             * Space-Complexity:    O(1)
             * 
             * */

            if (N <= 0) {
                return std::vector<std::vector<int> >();
            }
            
            std::vector<std::vector<int> > matrix(N, std::vector<int>(N));
            
            for (int i = 0, j = 1, 
                    left = 0, right = N-1, top = 0, bottom = N-1;
                    left <= right and top <= bottom; 
                    ++left, --right, ++top, --bottom) {
                // top row
                for (i = left; i <= right; ++i) {
                    matrix[top][i] = j++;
                }
                // right column
                for (i = top+1; i <= bottom; ++i) {
                    matrix[i][right] = j++;
                }
                if (left < right and top < bottom) {
                    // bottom row
                    for (i = right-1; i >= left; --i) {
                        matrix[bottom][i] = j++;
                    }
                    // left column 
                    for (i = bottom-1; i > top; --i) {
                        matrix[i][left] = j++;
                    }
                }
            }
            
            return matrix;
        }
public:
    vector<vector<int>> generateMatrix(int n) {
        return solution1(n);
    }
};
