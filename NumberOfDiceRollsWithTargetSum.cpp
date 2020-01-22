/*
You have d dice, and each die has f faces numbered 1, 2, ..., f.
Return the number of possible ways (out of f^d total ways) modulo 10^9 + 7 to roll the dice so the sum of the face up numbers equals target.

Example 1:
Input: d = 1, f = 6, target = 3
Output: 1
Explanation: 
You throw one die with 6 faces.  There is only one way to get a sum of 3.

Example 2:
Input: d = 2, f = 6, target = 7
Output: 6
Explanation: 
You throw two dice, each with 6 faces.  There are 6 ways to get a sum of 7:
1+6, 2+5, 3+4, 4+3, 5+2, 6+1.

Example 3:
Input: d = 2, f = 5, target = 10
Output: 1
Explanation: 
You throw two dice, each with 5 faces.  There is only one way to get a sum of 10: 5+5.

Example 4:
Input: d = 1, f = 2, target = 3
Output: 0
Explanation: 
You throw one die with 2 faces.  There is no way to get a sum of 3.

Example 5:
Input: d = 30, f = 30, target = 500
Output: 222616187
Explanation: 
The answer must be returned modulo 10^9 + 7.

Constraints:
1 <= d, f <= 30
1 <= target <= 1000
*/

class Solution {
private:
    static const int MOD_VALUE = 1e9 + 7;
    int faces;
    /*************************************************************************************************************/
    int** cache1;
    void init_cache1(const int dice, const int target) {
        cache1 = new int*[dice+1];
        for (int die = 0; die <= dice; ++die) {
            cache1[die] = new int[target+1];
            for (int t = 0; t <= target; ++t) {
                cache1[die][t] = -1;
            }
        }
    }
    void destroy_cache1(const int dice) {
        for (int i = 0; i <= dice; ++i) {
            delete [] cache1[i];
        }
        delete [] cache1;
    }
    bool in_cache1(const int dice, const int target) {
        return cache1[dice][target] >= 0;
    }
    int get_cache1_value(const int dice, const int target) {
        return cache1[dice][target];
    }
    int set_cache1_value(const int dice, const int target, const int num_rolls) {
        return (cache1[dice][target] = num_rolls);
    }
    int recurse1(const int dice, const int target) {
        if (in_cache1(dice, target)) {
            return get_cache1_value(dice, target);
        }
        int num_rolls;
        if (not target) {
            num_rolls = not dice;
        } else if (not dice) {
            num_rolls = 0;
        } else {
            num_rolls = 0;
            for (int face = std::min(faces, target); face; --face) {
                num_rolls += recurse1(dice - 1, target - face);
                num_rolls %= MOD_VALUE;
            }
        }
        return set_cache1_value(dice, target, num_rolls);
    }
	int solution1(const int dice, const int f, const int target) {
        /* Time-Complexity:     O(dice * f * target)
         * Space-Complexity:    O(dice * target)
         *
         * Recursively-Cached Solution.
         *
         */

        faces = f;
        
        init_cache1(dice, target);
        int num_rolls = recurse1(dice, target);
        destroy_cache1(dice);

        return num_rolls;
	}
    /*************************************************************************************************************/
    int solution2(const int dice, const int faces, const int target) {
        /* Time-Complexity:     O(dice * faces * target)
         * Space-Complexity:    O(dice * target)
         * 
         * DP Version of Solution1().
         *
         */

        auto DP = std::vector<std::vector<int>>(dice+1, std::vector<int>(target+1, 0));
        
        DP[0][0] = 1;
        for (int die = 1; die <= dice; ++die) {
            for (int t = 1; t <= target; ++t) {
                for (int face = 1; face <= std::min(faces, t); ++face) {
                    DP[die][t] = (DP[die][t] + DP[die-1][t-face]) % MOD_VALUE;
                }
            }
        }
        
        return DP[dice][target];
    }
    /*************************************************************************************************************/
public:
    int numRollsToTarget(int d, int f, int target) {
		return solution2(d, f, target);
    }
};
