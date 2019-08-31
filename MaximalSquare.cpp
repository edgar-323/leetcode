/*
Given a 2D binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.

Example:
Input: 
1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0
Output: 4
*/

class Solution {
private:
    int max(int x, int y) {
        return x < y ? y : x;
    }
    
    int max(int x, int y, int z) {
        return max(max(x, y), z);
    }
    
    int max(int x, int y, int z, int a) {
        return max(max(x, y, z), a);
    }
    
    int min(int x, int y) {
        return x < y ? x : y;
    }
    
    int min(int x, int y, int z) {
        return min(min(x, y), z);
    }
    /********************************************************************************/
    int maxDP(int topLeft, int left, int top, char curr) {
        if (curr == '0') {
            return 0;
        } else if (topLeft == 0 || left == 0 || top == 0) {
            return 1;
        }
        
        return max(2, 
                (left >= (top+1)) ? (top+1) : 0, 
                (top >= (left+1)) ? (left+1) : 0, 
                (left >= topLeft && top >= topLeft) ? topLeft+1 : 0);
    }
    int solution1(std::vector<std::vector<char>>& matrix) {
        /*
        Time-Complexity:    O(M*N)
        Space-Complexity:   O(M*N)
        
        I came up with this solution independently, however, by looking
        at the DP equation within `maxDP` we can see that we can reduce
        this to solution2 which is much simpler to understand.
        */
        int M = matrix.size();
        if (M == 0) {
            return 0;
        }
        int N = matrix[0].size();
        if (N == 0) {
            return 0;
        }
        int maxSide = 0;
        auto DP = std::vector<std::vector<int>>(M, std::vector<int>(N, 0));
        for (int i = 0; i < M; ++i) {
            DP[i][0] = (matrix[i][0] == '1') ? 1 : 0;
            maxSide = max(maxSide, DP[i][0]);
        }
        for (int j = 1; j < N; ++j) {
            DP[0][j] = (matrix[0][j] == '1') ? 1 : 0;
            maxSide = max(maxSide, DP[0][j]);
        }
        for (int i = 1; i < M; ++i) {
            for (int j = 1; j < N; ++j) {
                DP[i][j] = maxDP(DP[i-1][j-1], DP[i][j-1], DP[i-1][j], matrix[i][j]);
                maxSide = max(maxSide, DP[i][j]);
            }
        }
        return maxSide * maxSide;
    }
	/********************************************************************************/    
    int solution2(std::vector<std::vector<char>>& matrix) {
        /*
        Time-Complexity:    O(M*N)
        Space-Complexity:   O(M*N)
        */
        int M = matrix.size();
        if (M == 0) {
            return 0;
        }
        int N = matrix[0].size();
        if (N == 0) {
            return 0;
        }
        int maxSide = 0;
        auto DP = std::vector<std::vector<int>>(M, std::vector<int>(N, 0));
        for (int i = 0; i < M; ++i) {
            DP[i][0] = (matrix[i][0] == '1') ? 1 : 0;
            maxSide = max(maxSide, DP[i][0]);
        }
        for (int j = 1; j < N; ++j) {
            DP[0][j] = (matrix[0][j] == '1') ? 1 : 0;
            maxSide = max(maxSide, DP[0][j]);
        }
        for (int i = 1; i < M; ++i) {
            for (int j = 1; j < N; ++j) {
                DP[i][j] = ((matrix[i][j] == '1') ? 1 : 0) * 
                            (min(DP[i-1][j-1], DP[i][j-1], DP[i-1][j]) + 1);
                maxSide = max(maxSide, DP[i][j]);
            }
        }
        return maxSide * maxSide;
    }
    /********************************************************************************/
    int solution3(std::vector<std::vector<char>>& matrix) {
        /*
        Time-Complexity:    O(M*N)
        Space-Complexity:   O(N)
        
        By inspecting the recursive DP equation, it becomes apparent that 
        during the calculation of the DP[][] equation, we only look at values
        in the previous row and in the same row and so we require only two
        rows to calculate all possible DP[][] values.
        */
        int M = matrix.size();
        if (M == 0) {
            return 0;
        }
        int N = matrix[0].size();
        if (N == 0) {
            return 0;
        }
        int maxSide = 0;
        int* row0 = new int[N];
        int* row1 = new int[N];
        for (int j = 0; j < N; ++j) {
            row0[j] = (matrix[0][j] == '1') ? 1 : 0;
            maxSide = max(maxSide, row0[j]);
        }
        if (M == 1) {
            delete[] row0;
            delete[] row1;
            return maxSide;
        }
        row1[0] = (matrix[1][0] == '1') ? 1 : 0;
        maxSide = max(maxSide, row1[0]);
        for (int j = 1; j < N; ++j) {
            row1[j] = ((matrix[1][j] == '1') ? 1 : 0) * 
                        (min(row0[j-1], row0[j], row1[j-1]) + 1);
            maxSide = max(maxSide, row1[j]);
        }
        int* temp = NULL;
        for (int i = 2; i < M; ++i) {
            temp = row0;
            row0 = row1;
            row1 = temp;
            row1[0] = (matrix[i][0] == '1') ? 1 : 0;
            maxSide = max(maxSide, row1[0]);
            for (int j = 1; j < N; ++j) {
                row1[j] = ((matrix[i][j] == '1') ? 1 : 0) * 
                        (min(row0[j-1], row0[j], row1[j-1]) + 1);
                maxSide = max(maxSide, row1[j]);
            }
        }
        
        delete[] row0;
        delete[] row1;
        
        return (maxSide * maxSide);    
    }
    /********************************************************************************/
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        return solution3(matrix);
    }
};
