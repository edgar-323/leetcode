/*
There are a row of n houses, each house can be painted with one of the k colors. 
The cost of painting each house with a certain color is different. 
You have to paint all the houses such that no two adjacent houses have the same color.
The cost of painting each house with a certain color is represented by a n x k cost matrix. For example, costs[0][0] is the cost of painting house 0 with color 0; costs[1][2] is the cost of painting house 1 with color 2, and so on... Find the minimum cost to paint all houses.
Note:
All costs are positive integers.

Example:
Input: [[1,5,3],[2,9,4]]
Output: 5
Explanation: Paint house 0 into color 0, paint house 1 into color 2. Minimum cost: 1 + 4 = 5; 
             Or paint house 0 into color 2, paint house 1 into color 0. Minimum cost: 3 + 2 = 5. 

Follow up:
Could you solve it in O(nk) runtime?

*/
class Solution {
private:
    int N,K;

    int recurse1(
            const int i, 
            const int prev_color,
            std::vector<std::vector<int>>& cache,
            const std::vector<std::vector<int>>& costs) {
        if (i == N) {
            // No more houses 
            return 0;
        } else if (cache[i][prev_color] >= 0) {
            return cache[i][prev_color];
        }
        // What to do?
        // Pick the color for the current house given that it cannot be prev_color
        
        int min_cost = INT_MAX;
        for (int color = 0; color < K; ++color) {
            if (color == prev_color) {
                continue;
            }
            min_cost = std::min( min_cost, costs[i][color] + recurse1(i+1, color, cache, costs) );
        }

        return cache[i][prev_color] = min_cost;
    }

    int solution1(const std::vector<std::vector<int>>& costs) {
        /* Time-Complexity:     O(N*K)
         * Space-Complexity:    O(N*K)
         */
        if (costs.empty()) {
            return 0;
        }
        N = costs.size();
        K = costs[0].size();
        
        auto cache = std::vector<std::vector<int>>(N, std::vector<int>(K+1, -1));

        return recurse1(0, K, cache, costs);
    }
public:
    int minCostII(vector<vector<int>>& costs) {
        return solution1(costs); 
    }
};
