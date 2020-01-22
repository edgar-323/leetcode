/*
Given an array of integers A, find the sum of min(B), where B ranges over every (contiguous) subarray of A.
Since the answer may be large, return the answer modulo 10^9 + 7.

Example 1:
Input: [3,1,2,4]
Output: 17
Explanation: Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4]. 
Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.  Sum is 17.

Note:
1 <= A.length <= 30000
1 <= A[i] <= 30000
*/
class Solution {
private:
    static const int MOD_VAL = 1e9 + 7;

    int solution1(const std::vector<int>& A) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         */
        /* EXPLANATION:
         * Consider A[i].
         * How many subarrays of A[] exist s.t. A[i] is the minimum element?
         * Suppose x < i is the biggest index s.t. A[x] < A[i].
         * Suppose y > i is the smallest index s.t.t A[y] < A[i].
         * In otherwords, A[x] is the previous less element (PLE) of A[i] and A[y] is the next less element (NLE) of A[i].
         * Then, A[i] is the min element for all subarrays with start-end indices (index1, index2) s.t. x < index1 <= index2 < y.
         * How many such subarrays are there ? 
         * There are (i - x) * (y - i) such subarrays.
         * If we know this information for all indices i, then the answer we look for is ∑ { A[i] * (i - x[i]) * (y[i] - i) | i € {0,...,N-1} }
         * Okay, let's define: 
         *      left_min[i]     = j s.t. j < i is the biggest index that obeys:  A[j] < A[i] (j = -1 if no such A[j] exists)
         *      right_min[i]    = k s.t. i < k is the smallest index that obeys: A[k] < A[i] (k =  N if no such A[k] exists)  
         *
         * We can use stack data-structures to compute left_min[] and right_min[].
         * See https://leetcode.com/problems/sum-of-subarray-minimums/discuss/178876/stack-solution-with-very-detailed-explanation-step-by-step
         */
        const int N = A.size();

        auto ple_stack = std::stack<int>(); // Previous Less Element (PLE) Stack
        auto nle_stack = std::stack<int>(); // Next Less Element (NLE) Stack

        // Initialize left_min[] & right_min[]
        auto left_min = std::vector<int>(N, -1);
        auto right_min = std::vector<int>(N, N);

        for (int index = 0; index < N; ++index) {
            // PLE
            while (not ple_stack.empty() and A[index] < A[ple_stack.top()]) {
                ple_stack.pop();
            }
            if (not ple_stack.empty()) {
                left_min[index] = ple_stack.top(); // Update left_min[index]
            }
            ple_stack.push(index);
            // NLE
            while (not nle_stack.empty() and A[index] < A[nle_stack.top()]) {
                right_min[nle_stack.top()] = index; // Update right_min[stack.top()]
                nle_stack.pop();
            }
            nle_stack.push(index);
        }
        // Final Answer
        int results = 0;
        for (int i = 0; i < N; ++i) {
            results = (results + A[i] * (i - left_min[i]) * (right_min[i] - i)) % MOD_VAL;
        }

        return results;
    }

public:
    int sumSubarrayMins(vector<int>& A) {
        return solution1(A);        
    }
};
