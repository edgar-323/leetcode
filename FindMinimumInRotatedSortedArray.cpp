/*
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).

Find the minimum element.

You may assume no duplicate exists in the array.

Example 1:

Input: [3,4,5,1,2] 
Output: 1
Example 2:

Input: [4,5,6,7,0,1,2]
Output: 0
*/
class Solution {
private:
    int solution1(const std::vector<int>& A) {
        const int N = A.size();
        if (N == 1 or A[N-1] > A[0]) {
            // if only one element or if it's completely sorted then minimum is @ A[0]
            return A[0];
        }
        
        int left = 0;
        int right = N-1;

        while (left <= right) {
            const int mid = left + (right - left) / 2;

            if (A[mid] > A[mid+1]) {
                return A[mid+1];
            } else if (A[mid-1] > A[mid]) {
                return A[mid];
            } else if (A[mid] > A[0]) {
                left = mid+1;
            } else {
                right = mid-1;
            }
        }

        return INT_MAX;
    }
public:
    int findMin(vector<int>& nums) {
        return solution1(nums);       
    }
};
