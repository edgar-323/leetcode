/*
Given a square array of integers A, we want the minimum sum of a falling path through A.
A falling path starts at any element in the first row, and chooses one element from each row. 
The next row's choice must be in a column that is different from the previous row's column by at most one.

Example 1:
Input: 
[[1,2,3],
 [4,5,6],
 [7,8,9]]
Output: 12
Explanation: 
The possible falling paths are:
[1,4,7], [1,4,8], [1,5,7], [1,5,8], [1,5,9]
[2,4,7], [2,4,8], [2,5,7], [2,5,8], [2,5,9], [2,6,8], [2,6,9]
[3,5,7], [3,5,8], [3,5,9], [3,6,8], [3,6,9]
The falling path with the smallest sum is [1,4,7], so the answer is 12.

Note:
1 <= A.length == A[0].length <= 100
-100 <= A[i][j] <= 100
*/

class Solution {
private:
	int solution1(const std::vector<std::vector<int>>& A) {
        /* Time-Complexity:     O( M )
         * Space-Complexity:    O( M )
         *  where M = N^2
         * */
        const int N = A.size();
        if (!N) {
            return 0;
        } else if (N == 1) {
            return A[0][0];
        }
        
        auto DP = std::vector<std::vector<int>>( A );
        
        for (int row = 1; row < N; ++row) {
            DP[row][0] += std::min( DP[row-1][0], DP[row-1][1] );
            for (int col = 1; col < N-1; ++col) {
                DP[row][col] += std::min( std::min( DP[row-1][col-1], DP[row-1][col] ), DP[row-1][col+1] );
            }
            DP[row][N-1] += std::min( DP[row-1][N-2], DP[row-1][N-1] );
        }
        
        return *std::min_element( DP[N-1].begin(), DP[N-1].end() );    
	}
public:
    int minFallingPathSum(vector<vector<int>>& A) {
     	return solution1( A ); 
    }
};
