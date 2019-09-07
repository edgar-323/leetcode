/*
In the "100 game," two players take turns adding, to a running total, any integer from 1..10. 
The player who first causes the running total to reach or exceed 100 wins.
What if we change the game so that players cannot re-use integers?
For example, two players might take turns drawing from a common pool of numbers of 1..15 without replacement until they reach a total >= 100.

Given an integer maxChoosableInteger and another integer desiredTotal, determine if the first player to move can force a win, assuming both players play optimally.
Note:
You can always assume that maxChoosableInteger will not be larger than 20 and desiredTotal will not be larger than 300.

Example
Input:
maxChoosableInteger = 10
desiredTotal = 11

Output:
false

Explanation:
No matter which integer the first player choose, the first player will lose.
The first player can choose an integer from 1 up to 10.
If the first player choose 1, the second player can only choose integers from 2 up to 10.
The second player will win by choosing 10 and get a total = 11, which is >= desiredTotal.
Same with other integers chosen by the first player, the second player will always win.
*/

class Solution {
    static const int MAX_CHOOSABLE_INT = 20;
    static const int SUCCESS =  1;
    static const int FAILURE = -1;
    int cache[1 << (MAX_CHOOSABLE_INT + 1)];
    int maxChoosableInteger;
    int desiredTotal;

    bool chosen(const int choices, const int choice) {
        // Given current set of `choices`.
        // Checks whether `choice` is available.
        return choices & (1 << choice);
    }

    int choose(const int choices, const int choice) {
        // Modifies current set of `choices` so that 
        // `choice` is chosen.
        return choices | (1 << choice);
    }

    void init_cache(const int maxChoosableInteger, const int desiredTotal) {
        this->maxChoosableInteger   = maxChoosableInteger;
        this->desiredTotal          = desiredTotal;
        // Set all cache value to zero (nothing is in cache)
        memset( cache, 0, sizeof( cache ) );
    }

    bool in_cache(const int choices) {
        return cache[choices];
    }

    bool get_cache_value(const int choices) {
        return cache[choices] == SUCCESS;
    }
    
    bool set_cache_value(const int choices, const int val) {
        cache[choices] = val;
        return val == SUCCESS ? true : false;
    }

    bool choice_yields_success(const int choices, const int currentTotal, const int choice) {
        // Returns True if:
        //  1) `choice` is avaible in `choices` AND
        //  2) if available, choosing `choice` results in other player losing.
        // Otherwise returns False.
        return  not chosen( choices, choice) and 
                not recurse1( choose( choices, choice ), currentTotal + choice );
    }

    bool recurse1(const int choices, const int currentTotal) {
        // Returns True if CURRENT player wins the game
        // Otherwise returns False.
        if (currentTotal >= desiredTotal) {
            // Previous player has reached desiredTotal.
            // So current player loses.
            return false;
        } else if (in_cache( choices )) {
            // Cache Hit.
            // Return cache value.
            return get_cache_value( choices );
        }

        // Go through all possible choices.
        // For a given choice:
        //  Check if choice is available (i.e., not chosen yet)
        //      If so, check whether choosing it yields SUCCESS.
        for (int choice = 1; choice <= maxChoosableInteger; ++choice) {
            if (choice_yields_success( choices, currentTotal, choice )) {    
                return set_cache_value( choices, SUCCESS );
            }
        }
        
        // Either no choice was available (so we couldn't try anything)
        // or available choices all yielded FAILURE.
        return set_cache_value( choices, FAILURE );
    }
    
    bool solution1(const int maxChoosableInteger, const int desiredTotal) {
        /* Time-Complexity:     O( 2^(maxChoosableInteger) )
         * Space-Complexity:    O( 2^(MAX_CHOOSABLE_INT)   )
         * */
        // ASSUMES:
        // 1 <= maxChoosableInteger <= MAX_CHOOSABLE_INT
        // CREDITS:
        // Credit for this solutoion goes to leetcoder: zzg_zzm
        
        // If desiredTotal <= 1, then player1 can choose any value 
        // in {1,...,maxChoosableInteger} and win.
        if (desiredTotal <= 1) {
            return true;
        }
        // maxSum = ∑ { i | i € [1,..,maxChoosableInteger] }
        const int maxSum = maxChoosableInteger * (maxChoosableInteger + 1) / 2;
        if (desiredTotal > maxSum) {
            // No way either player can ever reach `desiredTotal`
            return false;
        } else if (desiredTotal == maxSum) {
            // Last player will reach `desiredTotal`.
            // We have to figure out who is last player:
            //  If `maxChoosableInteger` is EVEN, the player2 will be last player
            //  otherwise (if `maxChoosableInteger` is ODD), player1 will be last player.
            // Thus, player1 wins if `maxChoosableInteger` is ODD. 
            return maxChoosableInteger & 1;
        }
        
        init_cache( maxChoosableInteger, desiredTotal );

        // Return whether player1 can win the game given that:
        //  1) All choices are currently available
        //  2) Current total is zero 
        return recurse1( 0, 0 );
    }
public:
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        return solution1( maxChoosableInteger, desiredTotal );
    }
};
