/*
You are given an n x n 2D matrix representing an image.
Rotate the image by 90 degrees (clockwise).
Note: You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.

Example 1:
Given input matrix = 
[
  [1,2,3],
  [4,5,6],
  [7,8,9]
],
rotate the input matrix in-place such that it becomes:
[
  [7,4,1],
  [8,5,2],
  [9,6,3]
]

Example 2:
Given input matrix =
[
  [ 5, 1, 9,11],
  [ 2, 4, 8,10],
  [13, 3, 6, 7],
  [15,14,12,16]
], 
rotate the input matrix in-place such that it becomes:
[
  [15,13, 2, 5],
  [14, 3, 4, 1],
  [12, 6, 8, 9],
  [16, 7,10,11]
]
*/

class Solution {
public:
    void solution1(vector<vector<int>>& matrix) {
        int t1, t2;
        const int N = matrix.size();
        for (int L = 0, R = N-1; L < R; ++L, --R) {
            for (int i = L; i < R; ++i) {
                t1 = matrix[i][R];
                matrix[i][R] = matrix[L][i];
                
                t2 = matrix[R][(N-1)-i];
                matrix[R][(N-1)-i] = t1;
                
                t1 = matrix[(N-1)-i][L];
                matrix[(N-1)-i][L] = t2;
                
                matrix[L][i] = t1;
            }
        }
    }
public:
	void rotate(std::vector<std::vector<int>>& matrix) {
        solution1( matrix );	
	}
};
