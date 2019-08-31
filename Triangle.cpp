/*
Given a triangle, find the minimum path sum from top to bottom. 
Each step you may move to adjacent numbers on the row below.

For example, given the following triangle
[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]
The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

Note:
Bonus point if you are able to do this using only O(n) extra space, where n is the total number of rows in the triangle.
*/

class Solution {
private:
	int solution1(const std::vector<std::vector<int>>& triangle) {
        /* Time-Complexity:     O( T )
         * Space-Complexity:    O( T )
         *  where:
         *      T = ∑ { size(triangle[i]) | i € {0,...,M-1} }
         * */
        const int M = triangle.size();
       
        std::vector<std::vector<int>> DP;
        DP.reserve(M);
        
        DP.push_back( triangle[0] );
        for (int i = 1; i < M; ++i) {
            const int N = triangle[i].size();
            DP.push_back( triangle[i] );
            DP[i][0] += DP[i-1][0];
            for (int j = 1; j < N-1; ++j) {
                DP[i][j] += std::min( DP[i-1][j-1], DP[i-1][j] );
            }
            DP[i][N-1] += DP[i-1][N-2];
        }

        return *std::min_element( DP[M-1].begin(), DP[M-1].end() );
    }
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        return solution1(triangle);
    }
};
