/*
Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.

Example:
Input: [-2,1,-3,4,-1,2,1,-5,4],
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.

Follow up:
If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.
*/

class Solution {
private:
    int solution1(const std::vector<int>& nums) {
        /* Time-Complexity:     O( N )
         * Space-Complexity:    O( 1 )
         * */
        const int N = nums.size();
        if ( !N ) {
            return 0;
        }
        int globalMax = nums[0];
        int localMax = nums[0];
        for (int i = 1; i < N; ++i) {
            // `localMax` is updated greedily (i.e., it is updated based on what is maximal at the moment not in the long run).
            // Notice that `localMax` will only be set to `nums[i]` if `localMax` is currently negative.
            // This is because, if `localMax < 0` then `nums[i]` will always be greater than `nums[i] + localMax` regardless of the value of `nums[i]`. 
            localMax = std::max( nums[i], nums[i] + localMax );
            // `globalMax` keeps track of the maximum value that `localMax` was ever acquired. 
            globalMax = std::max(globalMax, localMax);
        }
        return globalMax;
    }
public:
	int maxSubArray(vector<int>& nums) {
		return solution1( nums );
	}
};
