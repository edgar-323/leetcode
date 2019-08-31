/*
Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0? 
Find all unique triplets in the array which gives the sum of zero.
Note: The solution set must not contain duplicate triplets.

Example:
Given array nums = [-1, 0, 1, 2, -1, -4],
A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]
*/

class Solution {
private:
    std::vector<std::vector<int>> solution1(vector<int>& nums) {
        /* Time-Complexity:     O( N^2 )
         * Space-Complexity:    O(  1  )
         * */ 

        std::vector<std::vector<int>> results;
        const int N = nums.size();
        std::sort(nums.begin(), nums.end());
        int a, b, c, left, right, sum;
        int i = 0;
        while (i < N) {
            a = nums[i];
            left = i+1;
            right = N-1;
            while (left < right) {
                b = nums[left];
                c = nums[right];
                sum = a + b + c;
                if (sum == 0) {
                    results.push_back( std::vector<int>{ a, b, c } );
                    while (left < right and nums[left] == b) {
                        ++left;
                    }
                } else if (sum < 0) {
                    while (left < right and nums[left] == b) {
                        ++left;
                    }
                } else {
                    while (left < right and nums[right] == c) {
                        --right;
                    }
                }
            }
            while (i < N and nums[i] == a) {
                ++i;
            }
        }
        return results;
    }
public:
	std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
		return solution1( nums );
	}
};
