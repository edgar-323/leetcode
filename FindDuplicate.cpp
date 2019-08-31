/*
Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive), prove that at least one duplicate number must exist. 
Assume that there is only one duplicate number, find the duplicate one.

Example 1:
Input: [1,3,4,2,2]
Output: 2

Example 2:
Input: [3,1,3,4,2]
Output: 3

Note:
You must not modify the array (assume the array is read only).
You must use only constant, O(1) extra space.
Your runtime complexity should be less than O(n2).
There is only one duplicate number in the array, but it could be repeated more than once.
*/

class Solution {
private:
    int solution1(std::vector<int>& nums) {
        /*
        Time-Complexity:    O(N)
        Space-Complexity:   O(1)
        */
        
        const int N = nums.size();
        int duplicate = -1;
        for (int i = 0; i < N; ++i) {
            int index = std::abs(nums[i]) - 1;
            if (nums[index] < 0) {
                duplicate = index + 1;
                break;
            }
            nums[index] *= -1;
        }
        
        for (int i = 0; i < N; ++i) {
            nums[i] = std::abs(nums[i]);
        }
        
        return duplicate;
    }

public:
    int findDuplicate(vector<int>& nums) {
        return solution1(nums);
    }
};
