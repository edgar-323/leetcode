/*
Given an array of scores that are non-negative integers. Player 1 picks one of the numbers from either end of the array followed by the player 2 and then player 1 and so on. Each time a player picks a number, that number will not be available for the next player. This continues until all the scores have been chosen. The player with the maximum score wins.

Given an array of scores, predict whether player 1 is the winner. You can assume each player plays to maximize his score.

Example 1:

Input: [1, 5, 2]
Output: False
Explanation: Initially, player 1 can choose between 1 and 2. 
If he chooses 2 (or 1), then player 2 can choose from 1 (or 2) and 5. If player 2 chooses 5, then player 1 will be left with 1 (or 2). 
So, final score of player 1 is 1 + 2 = 3, and player 2 is 5. 
Hence, player 1 will never be the winner and you need to return False.
Example 2:

Input: [1, 5, 233, 7]
Output: True
Explanation: Player 1 first chooses 1. Then player 2 have to choose between 5 and 7. No matter which number player 2 choose, player 1 can choose 233.
Finally, player 1 has more score (234) than player 2 (12), so you need to return True representing player1 can win.
Note:

1 <= length of the array <= 20.
Any scores in the given array are non-negative integers and will not exceed 10,000,000.
If the scores of both players are equal, then player 1 is still the winner.
*/

class Solution {
private:
    int N;

    int** cache1;
    void init_cache1() {
        cache1 = new int*[N+1];
        for (int i = 0; i <= N; ++i) {
            cache1[i] = new int[N+1];
            for (int j = 0; j <= N; ++j) {
                cache1[i][j] = -1;
            }
        }
    }
    void destroy_cache1() {
        for (int i = 0; i <= N; ++i) {
            delete[] cache1[i];
        }
        delete[] cache1;
    }
    int recurse1(const int i, const int j, const std::vector<int>& nums) {
        // Return the maximum score current player can attain in nums[i:j] (inclusive),
        // given the rules of the game.

        if (cache1[i][j] >= 0) {
            // Cache Hit
            return cache1[i][j];
        }

        int max_player_score;
        if (i > j) {
            // No more choices for current player choose from.
            max_player_score = 0;
        } else if (i == j) {
            // Only one choice for current player
            max_player_score = nums[i];
        } else if (i+1 == j) {
            // current player has two choices, so grab the best choice
            max_player_score = std::max(nums[i], nums[j]);
        } else {
            // This is the main part of the algorithm.
            //
            // If current player chooses nums[i], then opponent will choose maximum score in nums[i+1:j].
            // If opponent chooses nums[i+1] (it must be optimal), then we get choices in nums[i+2:j] (becuase its minimal to us).
            // Else opponent chooces nums[j] (it must be optimal), then we get choices in nums[i+1:j-1] (because its minimal to current player and opponent wants that).
            // In either case we get minimum in nums[i+2:j] and nums[i+1:j-1].
            //
            // Similarly if we choose nums[j], then opponent chooses optimally in nums[i:j-1].
            // If opponent chooces nums[i] (because its optimal), then we get choices in nums[i+1:j-1].
            // Else opponent chooses nums[j-1] (because its opponent), then we get choices in nums[i:j-2]. 
            // In either case we get minimum in nums[i+1:j-1] and nums[i:j-2].
            //
            // We choose maximum between choosing nums[i] or nums[j].
            max_player_score = std::max(
                                nums[i] + std::min(recurse1(i+2, j, nums), recurse1(i+1, j-1, nums)),
                                nums[j] + std::min(recurse1(i+1, j-1, nums), recurse1(i, j-2, nums)));
        }

        return cache1[i][j] = max_player_score;
    }
	bool solution1(const std::vector<int>& nums) {
        /* Time-Complexity:     O(N^2)
         * Space-Complexity:    O(N^2)
         */
        /* EXPLANATION:
         * We calculate what is the maximum score that player1 can attain using the above recursive algorithm.
         * If this score is at least half as big as the total possible score, then he can win because that means
         * that the opponent can optimally score at most total_score - player1_score.
         */

        N = nums.size();
        init_cache1();
        const int max_player_score = recurse1(0, N-1, nums);
        destroy_cache1();
        
        const int total_sum = std::accumulate(nums.begin(), nums.end(), 0);
        
        return max_player_score >= total_sum / 2 + (total_sum & 1);
	}
public:
    bool PredictTheWinner(vector<int>& nums) {
  		return solution1(nums);      
    }
};
