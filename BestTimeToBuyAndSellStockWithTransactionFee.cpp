/*
Your are given an array of integers prices, for which the i-th element is the price of a given stock on day i; and a non-negative integer fee representing a transaction fee.
You may complete as many transactions as you like, but you need to pay the transaction fee for each transaction. 
You may not buy more than 1 share of a stock at a time (ie. you must sell the stock share before you buy again.)

Return the maximum profit you can make.

Example 1:
Input: prices = [1, 3, 2, 8, 4, 9], fee = 2
Output: 8
Explanation: The maximum profit can be achieved by:
Buying at prices[0] = 1
Selling at prices[3] = 8
Buying at prices[4] = 4
Selling at prices[5] = 9
The total profit is ((8 - 1) - 2) + ((9 - 4) - 2) = 8.

Note:
0 < prices.length <= 50000.
0 < prices[i] < 50000.
0 <= fee < 50000.
*/

class Solution {
private:
	int solution1(std::vector<int>& prices, const int fee) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(1)
         */
        const int N = prices.size();
        int cash = 0;
        int hold = -prices[0];
        for (int k = 1; k < N; ++k) {
            cash = std::max(cash, hold + prices[k] - fee);
            hold = std::max(hold, cash - prices[k]);
        }

        return cash;
	}
public:
    int maxProfit(vector<int>& prices, int fee) {
  		return solution1(prices, fee);      
    }
};
