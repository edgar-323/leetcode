/*
Say you have an array for which the i-th element is the price of a given stock on day i.
Design an algorithm to find the maximum profit. 
You may complete at most k transactions.
Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

Example 1:
Input: [2,4,1], k = 2
Output: 2
Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.

Example 2:
Input: [3,2,6,5,0,3], k = 2
Output: 7
Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4.
             Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
*/
class Solution {
private:
    int helper1(const std::vector<int>& prices) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(1)
         */
        // This Solution Solves The Problem For The Case Where We Can Do Unlimited Transactions.
        const int N = prices.size();
        int max_profit = 0;
        int i, j;
        i = 0;
        while (i < N-1) {
            if (prices[i] >= prices[i+1]) { ++i; continue; }
            j = i+1;
            while (j < N-1 and prices[j] < prices[j+1]) { ++j; }
            if (prices[i] < prices[j]) { max_profit += (prices[j] - prices[i]); }
            i = j+1;
        }

        return max_profit;
    }
	int solution1(int K, const std::vector<int>& prices) {
        /* Time-Complexity:     O(N*K)
         * Space-Complexity:    O(N*K)
         */
        const int N = prices.size();
        if (N <= 1 or K <= 0) {
            return 0;
        } else if (K >= N/2) {
            // We can have unlimited # of transactions.
            return helper1(prices);
        }

        auto state = std::vector<std::vector<int>>( 2*K, std::vector<int>(N, INT_MIN) );
        state[0][0] = -prices[0];
        for (int i = 1; i < N; ++i) {
            state[0][i] = std::max(state[0][i-1], -prices[i]);
            const int M = std::min(2*K, i+1);
            for (int k = 1; k < M; ++k) {
                state[k][i] = std::max(state[k][i-1], state[k-1][i-1] + prices[i] * (k&1 ? 1 : -1));
            }
        }

        int max_profit = 0;
        for (int k = 0; k < K; ++k) {
            max_profit = std::max(max_profit, state[2*k+1][N-1]);
        }

        return max_profit;
	}
public:
    int maxProfit(int k, std::vector<int>& prices) {
  		return solution1(k, prices);      
    }
};
