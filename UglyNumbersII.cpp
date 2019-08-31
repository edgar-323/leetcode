/*
Write a program to find the n-th ugly number.
Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. 

Example:
Input: n = 10
Output: 12
Explanation: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.

Note:  
1 is typically treated as an ugly number.
n does not exceed 1690.
*/

class Solution {
private:
    int solution1(const int N) {
        /* Time-Complexity:     O( N )
         * Space-Complexity:    O( N )
         * */
        if (N <= 0) {
            return -1;
        }
        
        int twos = 0;
        int threes = 0;
        int fives = 0;
        
        int DP[N];
        DP[0] = 1;
        
        for (int i = 1; i < N; ++i) {
            DP[i] = std::min( std::min( 2 * DP[twos], 3 * DP[threes]) , 5 * DP[fives] );
            
            if (DP[i] == 2 * DP[twos]) {
                ++twos;
            }
            if (DP[i] == 3 * DP[threes]) {
                ++threes;
            }
            if (DP[i] == 5 * DP[fives]) {
                ++fives;
            }
        }

        return DP[N-1];  
    }
public:
    int nthUglyNumber(int n) {
       return solution1( n ); 
    }
};
