/*
Given an array of integers nums and an integer k. 
A subarray is called nice if there are k odd numbers on it.
Return the number of nice sub-arrays.

Example 1:
Input: nums = [1,1,2,1,1], k = 3
Output: 2
Explanation: The only sub-arrays with 3 odd numbers are [1,1,2,1] and [1,2,1,1].

Example 2:
Input: nums = [2,4,6], k = 1
Output: 0
Explanation: There is no odd numbers in the array.

Example 3:
Input: nums = [2,2,2,1,2,2,1,2,2,2], k = 2
Output: 16

Constraints:
1 <= nums.length <= 50000
1 <= nums[i] <= 10^5
1 <= k <= nums.length
*/
class Solution {
private:
    int solution1(const std::vector<int>& A, const int K) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         */
        /* Explanation:
         * We will use a Deque data-structure and two pointers (left, right) to solve this problem.
         * First, within the deque will be indices i of of A[] s.t. A[i-1] is odd.
         * The size of the deque will always be K (i.e., k indices where the elements are odd).
         * Left will always be the position after some odd number (except initially in which left = 0).
         * Then, we continue to expand right until we encounter another odd number.
         * At this point we know that we have K+1 odd numbers.
         * So within A[left:right] (not including right) there are K odd numbers.
         * The first odd number starts at deque.front() and the last odd number is at deque.back().
         * So what are the number of subarrays in A[left:right] that include these endpoints ?
         * It is,
         *      (right - (deque.back() - 1)) * (deque.front() - left)
         */
        const int N = A.size();
        int left = 0;
        int right = 0;
        auto deque = std::deque<int>();
        while (right < N and deque.size() < K) { 
            if (A[right++] & 1) {
                deque.push_back(right);
            }
        }
        int nice_arrays = 0;
        while (right < N) {
            if (A[right++] & 1) {
                const int first = deque.front();
                const int last = deque.back();
                nice_arrays += (right - last) * (first - left);
                left = first;
                deque.pop_front();
                deque.push_back(right);
            }
        }
        if (deque.size() == K) {
            const int first = deque.front();
            const int last = deque.back();
            nice_arrays += (right - (last - 1)) * (first - left);
        }

        return nice_arrays;
    }
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        return solution1(nums, k);        
    }
};
