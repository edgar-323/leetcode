/*
Say you have an array for which the ith element is the price of a given stock on day i.
If you were only permitted to complete at most one transaction (i.e., buy one and sell one share of the stock), design an algorithm to find the maximum profit.
Note that you cannot sell a stock before you buy one.

Example 1:
Input: [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
             Not 7-1 = 6, as selling price needs to be larger than buying price.

Example 2:
Input: [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
*/

class Solution {
private:
    int solution1(const std::vector<int>& prices) {
        /*
         * Time-Complexity:    O( N )
         * Space-Complexity:   O( 1 )
         * */
        /* Explanation:
         * For every price prices[i], maintain maximum value in prices[i+1:N), 
         * so that the max profit we can make if we decide to buy on day i is:
         *  max_value(prices[i+1:N]) - prices[i]
         * We check what is the best day to buy and return maximum profit this way.
         */
        const int N = prices.size();
        // Our return value (which we will iteritavely maximize):
        int maxProfit = 0;
        // If we are at `prices[i]`, `maxRight` will be the largest value in `prices[i+1:N)`.
        // We will iteratively update/maximize this value.
        int maxRight = 0;
        // Iterate `prices` in reverse order so that we can efficiently keep track of `maxRight`.
        for (int i = N-1; i >= 0; --i) {
            // Can we get a better profit if we buy at day `i` and sell at later day with value `maxRight`?
            maxProfit = std::max( maxProfit, maxRight - prices[i] );
            // Can we update `maxRight` for today's price?
            maxRight = std::max( maxRight, prices[i] );
        }

        return maxProfit;
    }
public:
    int maxProfit(vector<int>& prices) {
        return solution1(prices);
    }
};
