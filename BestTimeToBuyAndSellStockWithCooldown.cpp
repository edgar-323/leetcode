/*
Say you have an array for which the ith element is the price of a given stock on day i.
Design an algorithm to find the maximum profit. 

You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times) with the following restrictions:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
After you sell your stock, you cannot buy stock on next day. (ie, cooldown 1 day)

Example:
Input: [1,2,3,0,2]
Output: 3 
Explanation: transactions = [buy, sell, cooldown, buy, sell]
*/


class Solution {
private:
    int N;
    /***************************************************************************************/ 
    int recurse1(
            const std::vector<int>& prices,
            const int i,
            const int profitSoFar,
            const bool holdingStock) {
        if (i >= N) {
            return profitSoFar;
        } else if (holdingStock) {
            return std::max(
                        recurse1( i+1, profitSoFar, true ),
                        recurse1( i+1, profitSoFar+prices[i], false ) );
        } else {
            return std::max(
                        recurse1( i+1, profitSoFar, false ),
                        recurse1( i+1, profitSoFar-prices[i], true ) );
        }
    }
    int solution1(const std::vector<int>& prices) {
        /*
        Time-Complexity:    O( 2^N )
        Space-Complexity:   O(  N  )
        */
        N = prices.size();
        return recurse1( prices, 0, 0, false );
    }
    /***************************************************************************************/
    int solution2(const std::vector<int>& prices) {
        /* Time-Complexity:     O( N )
         * Space-Complexity:    O( N )
         * */
        /*
       	
        DP[i] = maximum profit at end of day i.
           
        Strategy
		Consider for M[i] , what kind of day i is?
		3 options: buy day, cooldown day, sell day, right? Let's analyse one by one below.

		It cannot be a buy day, since we cannot make any profit buying at the last day because you have no chance to sell it. 
        So 2 possibilities left: cooldown day, sell day.
		If It is a cooldown day, then the max profit is the same as day i - 1 =>M[i] = M[i - 1](1)
		If It is a sell day, then which day is the buy day? The buy day could be any days before day i(exclusive, i.e. 0 to i - 1). 
		Let's denote it as j, then the profit we get = nums[i] - nums[j] + previous day's profit. 
        The problem becomes what is the previous days' profit? To figure it out, ask youself what about the day j - 1?
		3.1. j - 1 cannot be a buy day. Since you cannot have 2 continuous days(j - 1 and j) as the buy day, you must sell the stock before you buy again as required.
		3.2. j - 1 cannot be a sell day as well, because if it is, day j must be a cooldown day.
		3.3. Thus, day j - 1 must be a cooldown day. If it is a cooldown day, then the max profit we can get at day j - 1 is M[j - 2]
		Above all, M[i] = Math.max(M[j - 2] + nums[i] - nums[j]) for j = 0 to i - 1 (2)
		With (1) and (2), we know that:
		M[i] = max(M[i - 1], Math.max(M[j - 2] + nums[i] - nums[j]) for j = 0 to i - 1)

		M[j - 2] + nums[i] - nums[j] can be transformed (M[j - 2] - nums[j]) + nums[i], and M[j - 2] - nums[j] is the only variable changing. 
        Then if we keep a varible(maxDiff) to keep track of the max of it, (3) can be changed to M[i] = max(M[i - 1], maxDiff + nums[i]) for j = 0 to i - 1)(4)
		*/
        
        N = prices.size();
        if (N <= 1) {
            return 0;
        }

        std::vector<int> DP( N, 0 );
        int max_diff = std::max( -prices[0], -prices[1] );
        DP[0] = 0;
        DP[1] = std::max( 0, prices[1] - prices[0] );
        for (int i = 2; i < N; ++i) {
            DP[i] = std::max( DP[i-1], max_diff + prices[i] );
            max_diff = std::max( max_diff, DP[i-2] - prices[i] );
        }
        
        return DP[N-1];
    }
    /***************************************************************************************/
    int solution3(std::vector<int>& prices) {
        /*
        Time-Complexity:    O(N)
        Space-Complexity:   O(N)
        */
        if (prices.empty()) {
            return 0;
        }
        N = prices.size();
        // recall states. 
        int s0[N];
        int s1[N];
        int s2[N];
        // intial conditions
        s0[0] = 0;
        s1[0] = -prices[0];
        s2[0] = INT_MIN;
        for (int i = 1; i < N; ++i) {
            // time-step i
            s0[i] = max(s0[i-1], s2[i-1]);
            s1[i] = max(s0[i-1] - prices[i], s1[i-1]);
            s2[i] = s1[i-1] + prices[i];
        }
        return max(s0[N-1], s2[N-1]);
    }
    /***************************************************************************************/ 
    int solution4(std::vector<int>& prices) {
        /*
        Time-Complexity:    O(N)
        Space-Complexity:   O(1)
        */
        N = prices.size();
        if (N == 0) {
            return 0;
        }
        int s0 = 0;
        int s1 = -prices[0];
        int s2 = INT_MIN;
        int prev0 = s0;
        int prev1 = s1;
        int prev2 = s2;
        for (int i = 1; i < N; ++i, 
             prev0 = s0, prev1 = s1, prev2 = s2) {
            s0 = max(prev0, prev2);
            s1 = max(prev0 - prices[i], prev1);
            s2 = prev1 + prices[i];
        }
        return max(s0, s2);
    }
    /***************************************************************************************/
public:
    int maxProfit(vector<int>& prices) {
        return solution3(prices);
    }
};
