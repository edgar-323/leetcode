/*
You are installing a billboard and want it to have the largest height.  
The billboard will have two steel supports, one on each side.  
Each steel support must be an equal height.

You have a collection of rods which can be welded together.  
For example, if you have rods of lengths 1, 2, and 3, you can weld them together to make a support of length 6.

Return the largest possible height of your billboard installation.  
If you cannot support the billboard, return 0.

Example 1:
Input: [1,2,3,6]
Output: 6
Explanation: We have two disjoint subsets {1,2,3} and {6}, which have the same sum = 6.

Example 2:
Input: [1,2,3,4,5,6]
Output: 10
Explanation: We have two disjoint subsets {2,3,5} and {4,6}, which have the same sum = 10.

Example 3:
Input: [1,2]
Output: 0
Explanation: The billboard cannot be supported, so we return 0.

Note:
0 <= rods.length <= 20
1 <= rods[i] <= 1000
The sum of rods is at most 5000.
*/

class Solution {
private:
    static const int MAX_SUM = 5000;
	int solution1(const std::vector<int>& rods) {
        /* Time-Complexity:     O(N * MAX_SUM)
         * Space-Complexity:    O(N * MAX_SUM)
         */
        /*  EXPLANATION (Credit Goes To LeetCoder @wangzi6147):
            Consider this problem as:
            Given a list of numbers, multiply each number with 1 or 0 or -1, make the sum of all numbers to 0 (this is very important).
            Find a combination which has the largest sum of all positive numbers 
            (remember the entire sum must still be zero, but given that the entire sum is zero, we aim to maximize the sum of ONLY the positive number).
            e.g. Given [1,2,3,4,5,6], we have 1*0 + 2 + 3 - 4 + 5 - 6 = 0, the sum of all positive numbers is 2 + 3 + 5 = 10.
            The answer is 10.

            This is a knapsack problem.
            Let's define:
            DP[i][j] = True iff {-1,0,1} mapped onto {rods[0],...,rods[i]} sums to (j-MAX_SUM).
            If so, then DP[i+1][j] = DP[i][j
            dp[i][j] represents whether the sum of first i numbers can be j - MAX_SUM. dp[0][MAX_SUM] = true.
            Then dp[i + 1][j] = dp[i][j - rods[i]] | dp[i][j + rods[i]] | dp[i][j].
            max[i][j] represents the largest sum of all positive numbers when the sum of first i numbers is j - MAX_SUM.
		*/

        const int N = rods.size();

        auto DP = std::vector<std::vector<bool>>(N+1, std::vector<bool>(2 * MAX_SUM + 1, false));
        auto max = std::vector<std::vector<int>>(N+1, std::vector<int>(2 * MAX_SUM + 1, 0));

        DP[0][MAX_SUM] = true;
        for (int i = 0; i < N; ++i) {
            for (int s = 0; s <= 2 * MAX_SUM; ++s) {

                if (DP[i][s]) {
                    DP[i+1][s] = true;
                    max[i+1][s] = std::max(max[i+1][s], max[i][s]);
                }
                if (s - rods[i] >= 0 and DP[i][s - rods[i]]) {
                    DP[i+1][s] = true;
                    max[i+1][s] = std::max(max[i+1][s], max[i][s - rods[i]] + rods[i]);
                }
                if (s + rods[i] <= 2 * MAX_SUM and DP[i][s + rods[i]]) {
                    DP[i+1][s] = true;
                    max[i+1][s] = std::max(max[i+1][s], max[i][s + rods[i]]);
                }

            }
        }
        
        // maximum # of positive numbers: MAX_SUM - MAX_SUM == 0 can be made from first N numbers.
        return max[N][MAX_SUM];
	}
public:
    int tallestBillboard(vector<int>& rods) {
  		return solution1(rods);      
    }
};
