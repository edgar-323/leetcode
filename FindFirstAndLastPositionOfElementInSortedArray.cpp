/*
Given an array of integers nums sorted in ascending order, find the starting and ending position of a given target value.
Your algorithm's runtime complexity must be in the order of O(log n).
If the target is not found in the array, return [-1, -1].

Example 1:
Input: nums = [5,7,7,8,8,10], target = 8
Output: [3,4]

Example 2:
Input: nums = [5,7,7,8,8,10], target = 6
Output: [-1,-1]
*/

class Solution {
private:
    vector<int> solution1(vector<int>& nums, int target) {
        vector<int> range;
        range.push_back(-1);
        range.push_back(-1);
        const int N = nums.size();
        if (N <= 0) {
            return range;
        }
        int v1, v2, v3;
        int val;
        int left = 0;
        int right = N;
        int mid;
        while (left <= right) {
            mid = (right + left) / 2;
            if (mid < 0 || mid >= N) {
                break;
            }
            val = nums[mid];
            
            if (val == target) {
                if (mid > 0 && nums[mid-1] == target) {
                    right = (right == mid) ? right-1 : mid;
                } else {
                    range[0] = mid;
                    break;
                }
            } else if (val < target) {
                left = (left == mid) ? left+1 : mid;
            } else {
                right = (right == mid) ? right-1 : mid;
            }
        }
        if (range[0] < 0) {
            return range;
        }
        left = 0;
        right = N;
        while (left <= right) {
            mid = (right + left) / 2;
            if (mid < 0 || mid >= N) {
                break;
            }
            val = nums[mid];
            
            if (val == target) {
                if (mid < N-1 && nums[mid+1] == target) {
                    left = (left == mid) ? left+1 : mid;
                } else {
                    range[1] = mid;
                    break;
                }
            } else if (val < target) {
                left = (left == mid) ? left+1 : mid;
            } else {
                right = (right == mid) ? right-1 : mid;
            }
        }
        return range;
    }
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        return solution1( nums, target );
    }
};
