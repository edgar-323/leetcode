/*
Say you have an array for which the ith element is the price of a given stock on day i.
Design an algorithm to find the maximum profit. 
You may complete at most two transactions.

Note: You may not engage in multiple transactions at the same time (i.e., you must sell the stock before you buy again).

Example 1:
Input: [3,3,5,0,0,3,1,4]
Output: 6
Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
             Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.

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
         * Space-Complexity:    O(N)
         */
        // MY SOLUTION
        // Inspired by looking at solution for "BestTimeToBuyAndSellStockWithCooldown" and was 
        // able to produce my own state machine solition.
        const int N = prices.size(); 

        if (N <= 1) {
            return 0;
        } else if (N == 2) {
            return std::max(0, prices[1] - prices[0]);
        } else if (N == 3) {
            return std::max<int>({0, prices[1] - prices[0], prices[2] - prices[0], prices[2] - prices[1]});
        }
        
        // s1[i] = max profit at end of day i after buying one bond
        auto s1 = std::vector<int>(N);
        // s2[i] = max profit at end of day i after buying one bond and selling it 
        auto s2 = std::vector<int>(N);
        // s3[i] = max profit at end of day i after buying one bond, selling it, and buying another bond
        auto s3 = std::vector<int>(N);
        // s4[i] = max profit at end of day i after buying one bond, selling it, buying another bond, and selling it again.
        auto s4 = std::vector<int>(N);
        
        // Initial conditions of these states.
        s1[0] = -prices[0];
        s1[1] = std::max(s1[0], -prices[1]);
        s1[2] = std::max(s1[1], -prices[2]);
        s1[3] = std::max(s1[2], -prices[3]); 

        s2[0] = INT_MIN;
        s2[1] = s1[0] + prices[1];
        s2[2] = std::max(s2[1], s1[1] + prices[2]);
        s2[3] = std::max(s2[2], s1[2] + prices[3]);
        
        s3[0] = INT_MIN;
        s3[1] = INT_MIN;
        s3[2] = s2[1] - prices[2];
        s3[3] = std::max(s3[2], s2[2] - prices[3]); 

        s4[0] = INT_MIN;
        s4[1] = INT_MIN;
        s4[2] = INT_MIN;
        s4[3] = s3[2] + prices[3];

        for (int i = 4; i < N; ++i) {
            s1[i] = std::max(s1[i-1], -prices[i]);
            s2[i] = std::max(s2[i-1], s1[i-1] + prices[i]);
            s3[i] = std::max(s3[i-1], s2[i-1] - prices[i]);
            s4[i] = std::max(s4[i-1], s3[i-1] + prices[i]);
        }

        return std::max<int>({0, s2[N-1], s4[N-1]}); 
    }
public:
    int maxProfit(vector<int>& prices) {
        return solution1(prices);
    }
};
