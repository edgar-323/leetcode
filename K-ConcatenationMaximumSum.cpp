/*

Given an integer array arr and an integer k, modify the array by repeating it k times.
For example, if arr = [1, 2] and k = 3 then the modified array will be [1, 2, 1, 2, 1, 2].
Return the maximum sub-array sum in the modified array. 
Note that the length of the sub-array can be 0 and its sum in that case is 0.
As the answer can be very large, return the answer modulo 10^9 + 7.

Example 1:
Input: arr = [1,2], k = 3
Output: 9

Example 2:
Input: arr = [1,-2,1], k = 5
Output: 2

Example 3:
Input: arr = [-1,-2], k = 7
Output: 0
 
Constraints:
1 <= arr.length <= 10^5
1 <= k <= 10^5
-10^4 <= arr[i] <= 10^4

*/

class Solution {
private:
    static const int64_t MOD_VAL = 1e9 + 7;

    int solution1(const std::vector<int>& A, const int K) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(1)
         */
        /* EXPLANATION:
         * First, we don't actually have to reproduce `A` `K` times 
         * because we already know the elements of `A`. 
         * We can just use modular arithmetic to index into the m-th
         * copy of A to retrieve a certain value.
         * Second, we can make use of Kandane's Algorithm to retrieve
         * maximum subarray of any array.
         * Third, we only need to focus on firt two copies of `A`.
         * To begin explaning why, we know that there are three possible
         * cases of maximum subarray:
         * 1) The maxsubarray may be contained within a single copy of `A
         *    and so concatenating more copies won't help.
         *    in this case we just use Kandane's algo on one copy.
         * 2) The maxsubarray may be contained between tail of copy one
         *    and the head of copy two.
         *    In this case we just use Kandane on two copies of `A`.
         * 3) The maxsubarray may be all `K` copies of `A` concatenated
         *    together.
         *    Here is where we must be vigilant.
         *    Even in this case, it can be possible to shave off some
         *    elemented from the head of 1st copy and some elements
         *    from tail of Kth copy and increase our answer.
         *    To accomplish this, we take (K-2) copies of `A` and we
         *    run Kandane's algo on two copies of `A` (this will 
         *    account of shaved edges in case we need to shave).
         *
         * We return max of above three cases.     
         */ 
        const int N = A.size();
        int local_max = A[0];
        int global_max = A[0];
        for (int i = 1; i < N * std::min(K,2); ++i) {
            local_max = std::max(A[i % N], A[i % N] + local_max);
            global_max = std::max(global_max, local_max);
        }
        const int64_t total = std::accumulate(A.begin(), A.end(), 0);
        
        return std::max<int64_t>(
                    {
                        0,                                      // Always remain non-negative
                        global_max,                             // Cases 1 & 2
                        global_max + total*std:max(0,K-2)       // Case 3
                    }) % MOD_VAL;
    }
public:
    int kConcatenationMaxSum(vector<int>& nums, int k) {
    	return solution1(nums, k);    
    }
};
