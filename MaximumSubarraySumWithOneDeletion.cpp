/*
Given an array of integers, return the maximum sum for a non-empty subarray (contiguous elements) with at most one element deletion. 
In other words, you want to choose a subarray and optionally delete one element from it so that there is still at least one element left and the sum of the remaining elements is maximum possible.
Note that the subarray needs to be non-empty after deleting one element.
 
Example 1:
Input: arr = [1,-2,0,3]
Output: 4
Explanation: Because we can choose [1, -2, 0, 3] and drop -2, thus the subarray [1, 0, 3] becomes the maximum value.

Example 2:
Input: arr = [1,-2,-2,3]
Output: 3
Explanation: We just choose [3] and it's the maximum sum.

Example 3:
Input: arr = [-1,-1,-1,-1]
Output: -1
Explanation: The final subarray needs to be non-empty. You can't choose [-1] and delete -1 from it, then get an empty subarray to make the sum equals to 0.
 
Constraints:
1 <= arr.length <= 10^5
-10^4 <= arr[i] <= 10^4
*/

class Solution {
private:
	int solution1(const std::vector<int>& A) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         */
        const int N = A.size();
        auto left = std::vector<int>(N);
        auto right = std::vector<int>(N);

        left[0] = A[0];
        right[N-1] = A[N-1];
        for (int i = 1; i < N; ++i) {
            left[i] = std::max(A[i], A[i] + left[i-1]);
            right[N-1-i] = std::max(A[N-1-i], A[N-1-i] + right[N-i]);
        }

        int max_sum = left[0];
        for (int i = 1; i < N-1; ++i) {
            max_sum = std::max<int>({left[i-1] + right[i+1], left[i], max_sum});
        }
        max_sum = std::max<int>({max_sum, right[N-1]});

        return max_sum;
	}
public:
    int maximumSum(vector<int>& arr) {
  		return solution1(arr);      
    }
};
