/*
Given an integer array, you need to find one continuous subarray that if you only sort this subarray in ascending order, then the whole array will be sorted in ascending order, too.
You need to find the shortest such subarray and output its length.

Example 1:
Input: [2, 6, 4, 8, 10, 9, 15]
Output: 5
Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array sorted in ascending order.

Note:
Then length of the input array is in range [1, 10,000].
The input array may contain duplicates, so ascending order here means <=.
*/

class Solution {
private:
    int findMin(std::vector<int>& nums, int start, int end) {
        int minVal = INT_MAX;
        while (start < end) {
            minVal = min(minVal, nums[start++]);
        }
        return minVal;
    }
    int findMax(std::vector<int>& nums, int start, int end) {
        int maxVal = INT_MIN;
        while (start < end) {
            maxVal = max(maxVal, nums[start++]);
        }
        return maxVal;
    }
    int bsLeft(std::vector<int>& nums, 
                int left, int right, int val) {
        const int N = nums.size();
        int index = right;
        int mid, i;
        while (left <= right) {
            mid = (left + right) / 2;
            i = max(0, min(mid, N-1));
            if (nums[i] <= val) {
                left = (left == mid) ? mid+1 : mid;
            } else {
                index = i;
                right = (right == mid) ? mid-1 : mid;
            }
        }
        return index;
    }
    int bsRight(std::vector<int>& nums, 
                int left, int right, int val) {
        const int N = nums.size();
        int index = right;
        int mid, i;
        while (left <= right) {
            mid = (left + right) / 2;
            i = max(0, min(mid, N-1));
            if (nums[i] >= val) {
                right = (right == mid) ? mid-1 : mid;
            } else {
                index = i;
                left = (left == mid) ? mid+1 : mid;
            }
        }
        return index;
    }
    
    int firstSortedSubArrayEnd(std::vector<int>& nums) {
        const int N = nums.size();
        int p1 = 1;
        while (p1 < N && 
               nums[p1-1] <= nums[p1]) {
            ++p1;
        }
        return p1;
    }
    
    int lastSortedSubArrayStart(std::vector<int>& nums) {
        const int N = nums.size();
        int p2 = N-1;
        while (p2 > 0 && 
               nums[p2-1] <= nums[p2]) {
            --p2;
        }
        return p2;
    }
    
    int solution1(std::vector<int>& nums) {
        /*
        ****************************************************
        Time-Complexity:  
            ==> 2*N + 2*lg(N)
            ==> 2*(N + lg(N))
            ==> O(N + lg(N))
            ==> O(N)
        Space-Complexity:   
            ==> O(1)
        ****************************************************
        */
        
        int N = nums.size();
        if (N <= 1) {
            return 0;
        }
        
        // O(N)-Time
        int e1 = firstSortedSubArrayEnd(nums);
        int minVal = findMin(nums, e1, N);
        if (e1 == N) {
            return 0;
        }
        // O(N)-Time
        int s2 = lastSortedSubArrayStart(nums);
        int maxVal = findMax(nums, 0, s2);

        // O(lg(N))-Time
        int start = bsLeft(nums, 0, e1, minVal);
        // O(lg(N))-Time
        int end = bsRight(nums, s2, N, maxVal);
        
        return (1+end-start);
    }
public:    
    int findUnsortedSubarray(vector<int>& nums) {
        return solution1(nums);
    }
};
