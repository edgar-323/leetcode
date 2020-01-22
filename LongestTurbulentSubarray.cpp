/*
A subarray A[i], A[i+1], ..., A[j] of A is said to be turbulent if and only if:

For i <= k < j, A[k] > A[k+1] when k is odd, and A[k] < A[k+1] when k is even;
OR, for i <= k < j, A[k] > A[k+1] when k is even, and A[k] < A[k+1] when k is odd.
That is, the subarray is turbulent if the comparison sign flips between each adjacent pair of elements in the subarray.

Return the length of a maximum size turbulent subarray of A.

 

Example 1:

Input: [9,4,2,10,7,8,8,1,9]
Output: 5
Explanation: (A[1] > A[2] < A[3] > A[4] < A[5])
Example 2:

Input: [4,8,12,16]
Output: 2
Example 3:

Input: [100]
Output: 1
 

Note:

1 <= A.length <= 40000
0 <= A[i] <= 10^9
*/

class Solution {
private:
	int solution1(const std::vector<int>& A) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(1)
         */
        // EXPLANATION:
        // Used technique analogous to Kandane's Algorithm which is leveraged to acquire
        // maximum subarray of an array.
        // Of course, this problem is slightly different but the idea is the same once you 
        // look for corner cases.
        const int N = A.size();

        int global_max = 1;
        int local_max = 1;
        for (int i = 1; i < N; ++i) {
            if (A[i] - A[i-1] == 0) {
                // Reset because (A[i-1], A[i]) absolutely breaks chain
                local_max = 1;
            } else if (local_max == 1) {
                // (A[i-1], A[i]) Are the beginning of a new chain
                ++local_max;
            } else {
                const int diff1 = A[i-2] - A[i-1];
                const int diff2 = A[i-1] - A[i];
                if ((diff1 < 0 and diff2 < 0) or (diff1 > 0 and diff2 > 0)) {
                    // Subarray {A[i-2], A[i-1], A[i]} is not turbulent.
                    // Let's make {A[i-1], A[i]} new turbulent array.
                    local_max = 2;
                } else {
                    ++local_max;
                }
            }

            global_max = std::max(global_max, local_max);
        }

        return global_max;
	}
public:
    int maxTurbulenceSize(vector<int>& A) {
  		return solution1(A);      
    }
};
