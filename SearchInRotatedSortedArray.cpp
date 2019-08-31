/*
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
(i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).
You are given a target value to search. If found in the array return its index, otherwise return -1.
You may assume no duplicate exists in the array.
Your algorithm's runtime complexity must be in the order of O(log n).

Example 1:
Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4

Example 2:
Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1
*/

class Solution {
private:
    int max(int x, int y) {
        return (x < y) ? y : x;
    }
    int min(int x, int y) {
        return (x < y) ? x : y;
    }
    int findPivot(vector<int>& nums) {
        int pivot = -1;
        const int N = nums.size();
        int val1, val2, val3;
        int left = 0;
        int right = N;
        int mid;
        while (left <= right) {
            mid = (right + left) / 2;
            val1 = nums[left];
            val2 = nums[mid];
            val3 = nums[min(N-1, max(0, right))];
            if (val1 <= val2 && val2 <= val3) {
                pivot = left;
                break;
            } else if (val2 >= val3) {
                if (val3 == val2) {
                    right = (right == mid) ? (right - 1) : mid;
                } else {
                    left = (left == mid) ? (left + 1) : mid;
                }
            } else if (val1 >= val2) {
                if (val1 == val2) {
                    left = (left == mid) ? (left + 1) : mid;
                } else {
                    right = (right == mid) ? (right - 1) : mid;
                }
            } else {
                int x = 1 / 0;
            }
        }
        return pivot;
    }
    int binarySearch(vector<int>& nums, int start, int end, int target) {
        // search nums[start, end) 
        // (which is assumed to be sorted) for target.
        int val;
        int index;
        int left = start;
        int right = end;
        int mid;
        while (left <= right) {
            mid = (right + left) / 2;
            index = min(max(0, end-1), mid);
            val = nums[index];
            if (val == target) {
                return mid;
            } else if (val < target) {
                left = (left == mid) ? (left + 1) : mid;
            } else {
                right = (right == mid) ? (right - 1) : mid;
            }
        }
        return -1;
    }
public:
    int search(vector<int>& nums, int target) {
        if (nums.size() == 0) {
            return -1;
        }
        int pivot = findPivot(nums);
        int index = binarySearch(nums, pivot, nums.size(), target);
        return (index >= 0) ? index : binarySearch(nums, 0, pivot, target);
    }
};
