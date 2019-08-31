/*
You are climbing a stair case. 
It takes n steps to reach to the top.
Each time you can either climb 1 or 2 steps. 
In how many distinct ways can you climb to the top?
Note: Given n will be a positive integer.

Example 1:
Input: 2
Output: 2
Explanation: There are two ways to climb to the top.
1. 1 step + 1 step
2. 2 steps

Example 2:
Input: 3
Output: 3
Explanation: There are three ways to climb to the top.
1. 1 step + 1 step + 1 step
2. 1 step + 2 steps
3. 2 steps + 1 step
*/

class Solution {
private:
    int solution3(const int N) {
        /* Time-Complexity:     O( N )
         * Space-Complexity:    O( 1 )
         * */
        // Notice in solution2 we only need to keep of two previous values so we can simply keep track of this and use O(1) Space-Complexity.
        if (N < 2) {
            return (N == 1) ? 1 : 0;
        }
        // First initial value
        int f0 = 1;
        // Second initial value
        int f1 = 1;
        int F = 0;
        for (int i = 2; i <= N; ++i) {
            F = (f0 + f1);
            f0 = f1;
            f1 = F;
        }
        return F;
    }
    
    int solution2(const int N) {
	    /* Time-Complexity:     O( N )
         * Space-Complexity:    O( N )
         * */
        // Dynamic-Programming Implementation of solution1.    
        if (N <= 0) {
            return 0;
        } else if (N == 1) {
            return 1;
        }
        int dp[N+1];
        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i <= N; ++i) {
            dp[i] = dp[i-2] + dp[i-1];
        }
        return dp[N];
    }
    
    int solution1(const int N) {
        // Time Limit Exceeded
        /*
        Time-Complexity:    Exponential (See Fibbonaci)
        Space-Complexity:   Exponential (Stack Calls)
        */
        if (N < 0) {
            return 0;
        } else if (N == 0) {
			// Zero steps. Only one way to reach "top": Take no steps.
            return 1;
        }
		// Either take one step or two steps and sum their results:
        return solution1( N-1 ) + solution1( N-2 );
    }
    
public:
    int climbStairs(int n) {
        return solution3(n);
    }
};
