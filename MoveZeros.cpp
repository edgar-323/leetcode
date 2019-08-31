/*
Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.

Example:

Input: [0,1,0,3,12]
Output: [1,3,12,0,0]
Note:

You must do this in-place without making a copy of the array.
Minimize the total number of operations.
*/

class Solution {
private:
    void solution1(std::vector<int>& nums) {
        /*
        Time-Complexity:    O(N)
        Space-Complexity:   O(1)
        */
        int N = nums.size();
        int next = 0;
        for (int i = 0; i < N; ++i) {
            if (nums[i] != 0) {
                nums[next++] = nums[i];
            }
        }
        while (next < N) {
            nums[next++] = 0;
        }
    }
public:
    void moveZeroes(vector<int>& nums) {
        solution1(nums);
    }
};
