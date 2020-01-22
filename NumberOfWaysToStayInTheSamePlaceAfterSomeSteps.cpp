/*
You have a pointer at index 0 in an array of size arrLen. 
At each step, you can move 1 position to the left, 1 position to the right in the array or stay in the same place.
(The pointer should not be placed outside the array at any time).

Given two integers steps and arrLen, 
return the number of ways such that your pointer still at index 0 after exactly steps steps.

Since the answer may be too large, return it modulo 10^9 + 7.

Example 1:
Input: steps = 3, arrLen = 2
Output: 4
Explanation: There are 4 differents ways to stay at index 0 after 3 steps.
Right, Left, Stay
Stay, Right, Left
Right, Stay, Left
Stay, Stay, Stay

Example 2:
Input: steps = 2, arrLen = 4
Output: 2
Explanation: There are 2 differents ways to stay at index 0 after 2 steps
Right, Left
Stay, Stay

Example 3:
Input: steps = 4, arrLen = 2
Output: 8

Constraints:
1 <= steps <= 500
1 <= arrLen <= 10^6
*/

class Solution {
private:
    static const int MOD_VAL = 1e9 + 7;
    int N;

    int** cache1;
    void init_cache1(const int steps) {
        cache1 = new int*[steps+1];
        const int M = std::min(steps/2, N-1);
        for (int s = 0; s <= steps; ++s) {
            cache1[s] = new int[M+1];
            for (int i = 0; i <= M; ++i) {
                cache1[s][i] = -1;
            }
        }
    }
    void destroy_cache1(const int steps) {
        for (int s = 0; s <= steps; ++s) {
            delete[] cache1[s];
        }
        delete[] cache1;
    }
    int recurse1(const int steps, const int index) {
        // Assumes index <= steps 
        if (cache1[steps][index] >= 0) {
            return cache1[steps][index];
        }

        int num_ways = 0;
        if (steps == 0) {
            num_ways = 1;
        } else {
            // Right
            if (index+1 <= std::min(steps-1, N-1)) {
                num_ways = (num_ways + recurse1(steps-1, index+1)) % MOD_VAL;
            }
            // Stay
            if (index <= steps-1) {
                num_ways = (num_ways + recurse1(steps-1, index)) % MOD_VAL;
            }
            // Left
            if (index) {
                num_ways = (num_ways + recurse1(steps-1, index-1)) % MOD_VAL;
            }
        }

        return cache1[steps][index] = num_ways;
    }
	int solution1(const int steps, const int arr_len) {
        /* Time-Complexity:     O(steps * min{steps, N})
         * Space-Complexity:    O(steps * min{steps, N})
         */
        N = arr_len;
        init_cache1(steps);
        const int num_ways = recurse1(steps, 0);
        destroy_cache1(steps);

        return num_ways;
	}
public:
    int numWays(int steps, int arrLen) {
  		return solution1(steps, arrLen);      
    }
};
