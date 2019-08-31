/*
You are given coins of different denominations and a total amount of money amount. 
Write a function to compute the fewest number of coins that you need to make up that amount. 
If that amount of money cannot be made up by any combination of the coins, return -1.

Example 1:
Input: coins = [1, 2, 5], amount = 11
Output: 3 
Explanation: 11 = 5 + 5 + 1

Example 2:
Input: coins = [2], amount = 3
Output: -1

Note: You may assume that you have an infinite number of each kind of coin.
*/

class Solution {
private:
    /***********************************************************************/
    int* memo;
    void cache_init(const int size) {
        memo = new int[size]();
    }
    void cache_destroy() {
        delete[] memo;
    }
    bool in_cache(const int amount) {
        return memo[amount] != 0;
    }
    int get_cache_value(const int amount) {
        return memo[amount];
    }
    void set_cache_value(const int amount, const int minCoins) {
        memo[amount] = (minCoins == INT_MAX) ? -1 : minCoins; 
    }
    int recurse1(const std::vector<int>& coins, const int amount) {
        if (amount < 0) {
            return -1;
        } else if (amount == 0) {
            return 0;
        } else if (in_cache( amount )) {
            return get_cache_value( amount ); 
        }

        int minCoins = INT_MAX;
        for (const int& coin : coins) {
            int res = recurse1(coins, amount - coin);
            if (res >= 0) {
                minCoins = std::min( minCoins, 1 + res );        
            }
        }
        set_cache_value( amount, minCoins );
        
        return get_cache_value( amount );
    }
    int solution1(const std::vector<int>& coins, const int amount) {
        if (amount < 0) {
            return -1;
        }

        cache_init( amount+1 );
        int res = recurse1(coins, amount);
        cache_destroy();

        return res;
    }
   	/***********************************************************************/ 
    int solution2(const std::vector<int>& coins, const int amount) {
        /* Time-Complexity:     O( C * AMOUNT )
         * Space-Complexity:    O(   AMOUNT   )
         *  where
         *      C = size( coins )
         * */
        if (amount < 0) {
            return -1;
        }

        std::vector<int> DP( amount+1, INT_MAX-1 );	
        DP[0] = 0;
        for (int rem = 1; rem <= amount; ++rem) {
            for (const int& coin : coins) {
                if (rem >= coin) {
                    DP[rem] = std::min( DP[rem], DP[rem-coin]+1 );
                }
            }
        }

        return DP[amount] > amount ? -1 : DP[amount];
    }
  	/***********************************************************************/ 
public:
    int coinChange(vector<int>& coins, int amount) {
        return solution2(coins, amount);
    }
};

