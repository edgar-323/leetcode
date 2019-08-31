/*
Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.

Example 1:
Input: [3,2,1,5,6,4] and k = 2
Output: 5

Example 2:
Input: [3,2,3,1,2,4,5,5,6] and k = 4
Output: 4

Note: You may assume k is always valid, 1 ≤ k ≤ array's length.
*/

class Solution {
private:
    int solution1(std::vector<int>& nums, int k) {
        int N = nums.size();
        std::sort(nums.begin(), nums.end());
        int i = N-1;
        while (i > -1 && (N-i) < k) {
            --i;
        }
        
        return nums[i];
    }
    
public:
    int findKthLargest(vector<int>& nums, int k) {
        return solution1(nums, k);
    }
};
