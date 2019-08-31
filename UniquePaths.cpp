/*
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).
How many possible unique paths are there?
Note: m and n will be at most 100.

Example 1:
Input: m = 3, n = 2
Output: 3
Explanation:
From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
1. Right -> Right -> Down
2. Right -> Down -> Right
3. Down -> Right -> Right

Example 2:
Input: m = 7, n = 3
Output: 28
*/

class Solution {
private:
    int solution1(const int M, const int N) {
        if (M <= 0 or N <= 0) {
            return 0;
        }

        std::vector<std::vector<long long>> DP( M, std::vector<long long>( N, 0 ) );
        
        // row 0
        for (int i = 0; i < M; ++i) {
            DP[i][0] = 1;
        }

        // column 0
        for (int j = 0; j < N; ++j) {
            DP[0][j] = 1;
        }

        for (int i = 1; i < M; ++i) {
            for (int j = 1; j < N; ++j) {
                DP[i][j] = DP[i-1][j] + DP[i][j-1];
            }
        }

        return DP[M-1][N-1];
    }    
    int myUnderstanding(int M, int N) {
        /*
        Time-Complexity:    O(min{M,N})
        Space-Complexity:   O(1)
        */
        M--;
        N--;
        size_t paths = (M < 0 || N < 0) ? 0 : 1;
        const size_t S = M+N;
        const size_t minDimension = min(M, N);
        for (size_t k = 0; k < minDimension; ++k) {
            paths = paths*(S-k) / (1+k);
        }
        return ((int) paths);
    }
    
    int postedSolution(int m, int n) {
        int N = n + m - 2;// how much steps we need to do
        int k = m - 1; // number of steps that need to go down
        double res = 1;
        // here we calculate the total possible path number 
        // Combination(N, k) = n! / (k!(n - k)!)
        // reduce the numerator and denominator and get
        // C = ( (n - k + 1) * (n - k + 2) * ... * n ) / k!
        for (int i = 1; i <= k; i++)
            res = res * (N - k + i) / i;
        return (int)res;
    }
public:
    int uniquePaths(int m, int n) {
        return solution1(m, n);
    }
};
