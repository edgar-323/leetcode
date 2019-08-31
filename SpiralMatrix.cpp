#include <vector>
#include <iostream>

/*

Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

Example 1:

Input:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
Output: [1,2,3,6,9,8,7,4,5]
Example 2:

Input:
[
  [1, 2, 3, 4],
  [5, 6, 7, 8],
  [9,10,11,12]
]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]

*/

class Solution {
    private:
        std::vector<int> solution1(const std::vector<std::vector<int>>& matrix) {
            /* Time-Complexity:     O(M*N)
             * Space-Complexity:    O(1)
             * */
            const int M = matrix.size();
            if (M == 0) {
                return {}; 
            }
            const int N = matrix[0].size();            
            
            std::vector<int> results( M*N, 0 );
            int index = 0;

            for (int i = 0,
                    left = 0, right = N-1, top = 0, bottom = M-1;
                    left <= right and top <= bottom; 
                    ++left, --right, ++top, --bottom) {
                // collect top row
                for (i = left; i <= right; ++i) {
                    results[index++] = matrix[top][i];
                }
                // collect right column 
                for (i = top+1; i <= bottom; ++i) {
                    results[index++] = matrix[i][right];
                } 
                if (left < right and top < bottom) {
                    // collect bottom row
                    for (i = right-1; i >= left; --i) {
                        results[index++] = matrix[bottom][i];
                    }
                    // collect left column
                    for (i = bottom-1; i > top; --i) {
                        results[index++] =  matrix[i][left];
                    }
                }
            }

            return results;
        }

    public:
        std::vector<int> spiralOrder(std::vector<std::vector<int> >& matrix) {
            return solution1( matrix );
        }
};
