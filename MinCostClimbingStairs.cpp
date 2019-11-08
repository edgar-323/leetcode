/*
On a staircase, the i-th step has some non-negative cost cost[i] assigned (0 indexed).
Once you pay the cost, you can either climb one or two steps. 
You need to find minimum cost to reach the top of the floor, and you can either start from the step with index 0, or the step with index 1.

Example 1:
Input: cost = [10, 15, 20]
Output: 15
Explanation: Cheapest is start on cost[1], pay that cost and go to the top.

Example 2:
Input: cost = [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]
Output: 6
Explanation: Cheapest is start on cost[0], and only step on 1s, skipping cost[3].

Note:
cost will have a length in the range [2, 1000].
Every cost[i] will be an integer in the range [0, 999].
*/

class Solution {
private:
    /*************************************************************************/
	int solution1(const std::vector<int>& cost) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         * */
        const int N = cost.size();
        if (!N) {
            return 0;
        } else if (N == 1) {
            return cost[0];
        }
        
        // DP[i] will be minimum cost to reach step i.
        // We are interested in DP[N]
        auto DP = std::vector<int>(N+1, 0);
        for (int i = 2; i <= N; ++i) {
            DP[i] = std::min(DP[i-2] + cost[i-2], DP[i-1] + cost[i-1]);
        }

        return DP[N];
	}
    /*************************************************************************/
    int solution2(const std::vector<int>& cost) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(1)
         * */
        // SAME AS solution1() BUT WE OPTIMIZE SPACE-COMPLEXITY. 
        const int N = cost.size();
        if (!N) {
            return 0;
        } else if (N == 1) {
            return cost[0];
        }

        int DP_minus_two = 0;
        int DP_minus_one = 0;
        int DP_final;

        for (int i = 2; i <= N; ++i) {
            DP_final = std::min(DP_minus_two + cost[i-2], DP_minus_one + cost[i-1]);
            DP_minus_two = DP_minus_one;
            DP_minus_one = DP_final; 
        }
        
        return DP_final;
    }
    /*************************************************************************/
public:
    int minCostClimbingStairs(vector<int>& cost) {
     	return solution2(cost); 
    }
};
