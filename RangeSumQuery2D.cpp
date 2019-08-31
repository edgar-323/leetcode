/*
Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).

Example:
Given matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
]

sumRegion(2, 1, 4, 3) -> 8
sumRegion(1, 1, 2, 2) -> 11
sumRegion(1, 2, 2, 4) -> 12

Note:
You may assume that the matrix does not change.
There are many calls to sumRegion function.
You may assume that row1 ≤ row2 and col1 ≤ col2.
*/

class NumMatrix {
/* EXPLANATION:
 * Let:
 *      DP[i][j] = ∑∑( */
private:
    int M;
    int N;
    int** DP;
public:
    NumMatrix(vector<vector<int>>& matrix) {
        M = matrix.size();
        N = M ? matrix[0].size() : 0;
        
        if (!M or !N) {
            return;
        }

        DP = new int*[M];

        DP[0] = new int[N];
        int row_sum = 0;
        for (int j = 0; j < N; ++j) {
            DP[0][j] = (row_sum += matrix[0][j]);
        }
        for (int i = 1; i < M; ++i) {
            DP[i] = new int[N];
            row_sum = 0;
            for (int j = 0; j < N; ++j) {
                DP[i][j] = DP[i-1][j] + (row_sum += matrix[i][j]);  
            }
        }
    }

    ~NumMatrix() {
        if (!M or !N) {
            return;
        }
        for (int i = 0; i < M; ++i) {
            delete [] DP[i];
        }
        delete [] DP;
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        /* ASSUMES:
         * 0 <= row1 <= row2 < M
         * 0 <= col1 <= col2 < N
         * */
        return  DP[row2][col2] 
                - (row1             ? DP[row1-1][col2]      : 0) 
                - (col1             ? DP[row2][col1-1]      : 0) 
                + (row1 and col1    ? DP[row1-1][col1-1]    : 0);
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */
