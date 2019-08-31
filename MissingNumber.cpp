/*
Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, find the one that is missing from the array.

Example 1:

Input: [3,0,1]
Output: 2
Example 2:

Input: [9,6,4,2,3,5,7,0,1]
Output: 8
Note:
Your algorithm should run in linear runtime complexity. Could you implement it using only constant extra space complexity?
*/

class Solution {
private:
	int solution1(std::vector<int>& nums) {
        /* 
         * Time-Complexity:     O( N )
         * Space-Complexity:    O( 1 )
         * */
        const size_t N = nums.size();
        size_t total = 0;
        for (size_t i = 0; i <= N; ++i) {
            total ^= i;
        }       
        size_t partial = 0;
        for (auto& num : nums) {
            partial ^= num;
        }
        return total ^ partial;
    }
public:
    int missingNumber(vector<int>& nums) {
        return solution1( nums );    
    }
};
