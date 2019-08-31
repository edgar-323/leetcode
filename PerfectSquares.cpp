/*
Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.

Example 1:
Input: n = 12
Output: 3 
Explanation: 12 = 4 + 4 + 4.

Example 2:
Input: n = 13
Output: 2
Explanation: 13 = 4 + 9.
*/

class Solution {
private:
    /**************************************************************/
    int solution1(const int N) {
        /* Time-Complexity:     O( ∑ sqrt(i) for i € {1,...,N}  )
         * Space-Complexity:    O(  N  )
         * */
        
        int DP[N+1];
        DP[0] = 0;
        for (int i = 1; i <= N; ++i) {
            DP[i] = i;
            for (int j = 1; (j*j) <= i; ++j) {
                DP[i] = std::min(DP[i], 1 + DP[i - (j*j)]);
            }
        }
        return DP[N];
    }
    /**************************************************************/
    int solution2(const int N) {
        /*
        
        */
        std::vector<int> DP( 1, 0 );
    
        while (DP.size() <= N) {
            int i = DP.size();
            int next = i;
            for (int j = 1; j*j <= i; ++j) {
                next = std::min(next, 1 + DP[i - j*j]);
            }
            DP.push_back(next);
        }
        return DP[N];
    }
    /**************************************************************/ 
public:
    int numSquares(int n) {
         return solution2(n);
    }
};
