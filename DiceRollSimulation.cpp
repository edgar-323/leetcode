/*
A die simulator generates a random number from 1 to 6 for each roll. 
You introduced a constraint to the generator such that it cannot roll the number i more than rollMax[i] (1-indexed) consecutive times. 

Given an array of integers rollMax and an integer n, return the number of distinct sequences that can be obtained with exact n rolls.

Two sequences are considered different if at least one element differs from each other. Since the answer may be too large, return it modulo 10^9 + 7.

Example 1:
Input: n = 2, rollMax = [1,1,2,2,2,3]
Output: 34
Explanation: There will be 2 rolls of die, if there are no constraints on the die, there are 6 * 6 = 36 possible combinations. In this case, looking at rollMax array, the numbers 1 and 2 appear at most once consecutively, therefore sequences (1,1) and (2,2) cannot occur, so the final answer is 36-2 = 34.

Example 2:
Input: n = 2, rollMax = [1,1,1,1,1,1]
Output: 30

Example 3:
Input: n = 3, rollMax = [1,1,1,2,2,3]
Output: 181

Constraints:
1 <= n <= 5000
rollMax.length == 6
1 <= rollMax[i] <= 15
*/

class Solution {
private:
    static const int MOD_VAL = 1e9 + 7;
    static const int NUM_OUTCOMES = 6;
    /***********************************************************************************************/
    int*** cache1;
    void init_cache1(const int N, const std::vector<int>& roll_max) {
        cache1 = new int**[NUM_OUTCOMES];
        for (int die = 0; die < NUM_OUTCOMES; ++die) {
            cache1[die] = new int*[roll_max[die] + 1];
            for (int num_rolls = 0; num_rolls <= roll_max[die]; ++num_rolls) {
                cache1[die][num_rolls] = new int[N+1];
                for (int n = 0; n <= N; ++n) {
                    cache1[die][num_rolls][n] = -1;
                }
            }
        }
    }
    void destroy_cache1(const int N, const std::vector<int>& roll_max) {
        for (int die = 0; die < NUM_OUTCOMES; ++die) {
            for (int num_rolls = 0; num_rolls <= roll_max[die]; ++num_rolls) {
                delete[] cache1[die][num_rolls];
            }
            delete[] cache1[die];
        }
        delete[] cache1;
    }
    int recurse1(const int die, const int num_rolls, const int N, const std::vector<int>& roll_max) {
        if (cache1[die][num_rolls][N] >= 0) {
            return cache1[die][num_rolls][N];
        }
        int distinct_sqns = 0;
        if (N == 1) {
            distinct_sqns = 5 + (num_rolls < roll_max[die]); 
        } else {
            for (int other_die = 0; other_die < NUM_OUTCOMES; ++other_die) {
                if (other_die == die) {
                    if (num_rolls < roll_max[die]) {
                        distinct_sqns = (distinct_sqns + recurse1(die, num_rolls + 1, N-1, roll_max)) % MOD_VAL;
                    }
                } else {
                    distinct_sqns = (distinct_sqns + recurse1(other_die, 1, N-1, roll_max)) % MOD_VAL; 
                }
            }
        }

        return cache1[die][num_rolls][N] = distinct_sqns;
    } 
    int solution1(const int N, const std::vector<int>& roll_max) {
        /* Time-Complexity:     O(NUM_OUTCOMES * max{roll_max} * N}
         * Space-Complexity:    O(NUM_OUTCOMES * max{roll_max} * N)
         */
        init_cache1(N, roll_max);
        const int distinct_sqns = recurse1(0, 0, N, roll_max);
        destroy_cache1(N, roll_max);

        return distinct_sqns;
    }
    /***********************************************************************************************/
    int solution2(const int N, const std::vector<int>& roll_max) {
         
    }
    /***********************************************************************************************/
public:
    int dieSimulator(int n, vector<int>& rollMax) {
        return solution1(n, rollMax); 
    }
};
