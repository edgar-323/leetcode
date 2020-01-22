/*
Your are given an array of positive integers nums.

Count and print the number of (contiguous) subarrays where the product of all the elements in the subarray is less than k.

Example 1:
Input: nums = [10, 5, 2, 6], k = 100
Output: 8
Explanation: The 8 subarrays that have product less than 100 are: [10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6].
Note that [10, 5, 2] is not included as the product of 100 is not strictly less than k.
Note:

0 < nums.length <= 50000.
0 < nums[i] < 1000.
0 <= k < 10^6.
*/
class Solution {
private:
    int count(const int M) {
        return  M & 1 ?
                M * ((M+1)/2):
                (M/2) * (M+1); 
    }

    int solution1(const std::vector<int>& A, const int K) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(1)
         */
        const int N = A.size();
        int left = 0;
        int right = 0; 
        int subarrays = 0;
        int prod = 1;
        while (right < N) {
            if (A[right] >= K) {
                subarrays += count(right - left);
                while (right < N and A[right] >= K) {
                    ++right;
                }
                left = right;
                prod = 1;
            } else if (prod * A[right] >= K) {
                subarrays += count(right - left); 
                while (left < right and prod * A[right] >= K) {
                    prod /= A[left++];
                }
                subarrays -= count(right - left);
            }
            if (right < N) {
                prod *= A[right++];
            }
        }
        subarrays += count(right - left);

        return subarrays;
    }
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        return solution1(nums, k);        
    }
};
