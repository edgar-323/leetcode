/*
Given an array nums of integers, we need to find the maximum possible sum of elements of the array such that it is divisible by three.

Example 1:
Input: nums = [3,6,5,1,8]
Output: 18
Explanation: Pick numbers 3, 6, 1 and 8 their sum is 18 (maximum sum divisible by 3).

Example 2:
Input: nums = [4]
Output: 0
Explanation: Since 4 is not divisible by 3, do not pick any number.

Example 3:
Input: nums = [1,2,3,4,4]
Output: 12
Explanation: Pick numbers 1, 3, 4 and 4 their sum is 12 (maximum sum divisible by 3).
 
Constraints:
1 <= nums.length <= 4 * 10^4
1 <= nums[i] <= 10^4
*/

class Solution {
private:
    int N;

	int solution1(const std::vector<int>& nums) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(1)
         */
        /* Explanation:
         * We know that (num1 + num2) % 3 € {0, 1, 2}
         * So, we create DP[] = { ,  ,  }
         * Where 
         *      DP[0] = maximum subset sum of nums (call it t) such that t % 3 == 0.
         *      DP[1] = maximum subset sum of nums (call it t) such that t % 3 == 1.
         *      DP[2] = maximum subset sum of nums (call it t) such that t % 3 == 2.
         *
         * Initially, DP[t] = 0.
         * We inspect nums in order, so when inspecting nums[i] we use it to update DP[t]
         * For example, we update it as follows
         *      DP[(nums[i] + DP[0]) % 3] = std::max(DP[(nums[i] + DP[0]) % 3], nums[i] + DP[0]) (i.e., we try to update the group (0-2) that nums[i] + DP[0] maps to)
         *      DP[(nums[i] + DP[1]) % 3] = std::max(DP[(nums[i] + DP[1]) % 3], nums[i] + DP[1]) (i.e., we try to update the group (0-2) that nums[i] + DP[1] maps to)
         *      DP[(nums[i] + DP[2]) % 3] = std::max(DP[(nums[i] + DP[2]) % 3], nums[i] + DP[2]) (i.e., we try to update the group (0-2) that nums[i] + DP[2] maps to) 
         *
         *  At the end we will be interested in DP[0] since it will give us the maximum subset sum of nums[] that maps to group 0 (i.e., sum % 3 == 0).
         *
         *  Notice how we can generalize this technique.
         *  I.e., if we want maximum subset sum that is divisible by positive integers k, then we create DP[k] and update it similarly:
         *      For num in nums:
         *          For sum in DP[]:
         *              DP[(sum + num) % 3] = max{ DP[(sum + num) % 3], sum + num }
         */
        auto DP = std::vector<int>(3, 0);
        for (const int num : nums) {
            for (const int i : std::vector(DP)) {
                DP[(i + num) % 3] = std::max(DP[(i + num) % 3], i + num);
            }
        }
        return DP[0];
	}
public:
    int maxSumDivThree(vector<int>& nums) {
  		return solution1(nums);      
    }
};
