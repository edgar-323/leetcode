/*
You are a professional robber planning to rob houses along a street. 
Each house has a certain amount of money stashed. 
All houses at this place are arranged in a circle. 
That means the first house is the neighbor of the last one. 
Meanwhile, adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.

Example 1:
Input: [2,3,2]
Output: 3
Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money = 2),
             because they are adjacent houses.

Example 2:
Input: [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
             Total amount you can rob = 1 + 3 = 4.
*/
class Solution {
private:
	int solution1(const std::vector<int>& nums) {
		/* Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         */
        // Consider Base Cases 
        const int N = nums.size();
        if (not N) {
            // No houses to rob
            return 0;
        } else if (N == 1) {
            // Only one house to rob. Rob it.
            return nums[0];
        } else if (N == 2) {
            // Only two houses to rob. Rob best of the two.
            return std::max(nums[0], nums[1]);
        }
        // Assume last house does not exist.
        auto DP = std::vector<int>(N, 0);
        DP[0] = nums[0];
        DP[1] = std::max(nums[0], nums[0]);
        for (int i = 2; i < N-1; ++i) {
            DP[i] = std::max(nums[i] + DP[i-2], DP[i-1]);
        }
        const int max_rob = DP[N-2];
        // Assume first house does not exist.
        DP[1] = nums[1];
        DP[2] = std::max(nums[1], nums[2]);
        for (int i = 3; i < N; ++i) {
            DP[i] = std::max(nums[i] + DP[i-2], DP[i-1]);
        }
        // Return best choice of both assumprions.  
        return std::max(max_rob, DP[N-1]);
	}
public:
    int rob(vector<int>& nums) {
  		return solution1(nums);      
    }
};
