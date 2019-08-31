/*
Given an array of non-negative integers, you are initially positioned at the first index of the array.
Each element in the array represents your maximum jump length at that position.
Determine if you are able to reach the last index.

Example 1:
Input: [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.

Example 2:
Input: [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum
             jump length is 0, which makes it impossible to reach the last index.
*/

class Solution {
private:
    bool solution1(vector<int>& nums) {
        /*
        MY SOLUTION
        Time-Complexity:    O(N^2)
        Space-Complexity:   O(1)   
        Very Slow ... Beats 23.90% of other submissions
        */
        const int N = nums.size();
        if (N <= 0) {
            return false;
        } 
        nums[N-1] = 1;
        int jump;
        for (int index = N-2; index > -1; --index) {
            jump = nums[index];
            nums[index] = 0;
            if (index+jump >= N-1) {
                nums[index] = 1;
                jump = 0;
            } 
            while (jump > 0) {
                if (nums[index+jump] > 0) {
                    nums[index] = 1;
                    break;
                } 
                --jump;
            } 
        } 
        return (nums[0] > 0);
    }
    
    bool topDown(vector<int>& nums, int index, const int N) {
        if (index >= N || nums[index] == -1) {
            return true;
        }
        while (nums[index] > 0) {
            if (topDown(nums, index + nums[index], N)) {
                nums[index] = -1;
                return true;
            }
            --nums[index];
        }
        return false;
    }
    
    bool solution2(vector<int>& nums) {
        /*
        MY SOLUTION
        */
        const int N = nums.size();
        if (!N) {
            return false;
        }
        nums[N-1] = -1;
        return topDown(nums, 0, N);
    }
    
    bool solution3(vector<int>& nums) {
        /*
        APPROACH 4: "GREEDY"
        Time-Complexity:    O(N)
        Space-Complexity:   O(1)
        */
        const int N = nums.size();
        int pointer = N-1;
        for (int index = N-1; index > -1; --index) {
            pointer = ((index + nums[index]) >= pointer) ? 
                        index : pointer;
        }
        return pointer == 0;
    }
    
public:
    bool canJump(vector<int>& nums) {
        return solution3(nums);
    }
};
