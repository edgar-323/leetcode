/*
Say you have an array for which the ith element is the price of a given stock on day i.
Design an algorithm to find the maximum profit. 
You may complete as many transactions as you like (i.e., buy one and sell one share of the stock multiple times).
Note: You may not engage in multiple transactions at the same time (i.e., you must sell the stock before you buy again).

Example 1:
Input: [7,1,5,3,6,4]
Output: 7
Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 5-1 = 4.

             Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 6-3 = 3.
Example 2:
Input: [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
             Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are
             engaging multiple transactions at the same time. You must sell before buying again.

Example 3:
Input: [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
*/

class Solution {
private:
	int solution1(const std::vector<int>& prices) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(1)
         */
        /* Explanation:
         * Notice that the nature of prices[] produces a discrete graph
         * of peaks and drops.
         * The key thing to notice, is to always locate the next local minima,
         * and it corresponding local maxima and add that to the profit.
         * This is because we want to buy on the day of the local minima 
         * and sell it on the day of the local maxima.
         * Since we don't have limit on number of transactions, we look for
         * all (local_minima, local_maxima) pairs and add to result.
         * */
        const int N = prices.size(); 
        int max_profit = 0;
        int i, j;
        
        i = 0;
        while (i < N-1) {
            // find minima
            if (prices[i] >= prices[i+1]) {
                ++i;
                continue;
            }
            // found a minima
            // now find next maxima
            j = i+1;
            while (j < N-1 and prices[j] < prices[j+1]) {
                ++j;
            }
            if (prices[i] < prices[j]) {
                // found maxima
                max_profit += (prices[j] - prices[i]);
            }
            i = j+1;
        }

        return max_profit;
	}
public:
    int maxProfit(vector<int>& prices) {
  		return solution1(prices);      
    }
};
