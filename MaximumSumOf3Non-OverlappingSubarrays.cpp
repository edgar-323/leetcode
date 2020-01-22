/*
In a given array nums of positive integers, find three non-overlapping subarrays with maximum sum.
Each subarray will be of size k, and we want to maximize the sum of all 3*k entries.
Return the result as a list of indices representing the starting position of each interval (0-indexed). If there are multiple answers, return the lexicographically smallest one.

Example:
Input: [1,2,1,2,6,7,5,1], 2
Output: [0, 3, 5]
Explanation: Subarrays [1, 2], [2, 6], [7, 5] correspond to the starting indices [0, 3, 5].
We could have also taken [2, 1], but an answer of [1, 3, 5] would be lexicographically larger.

Note:
nums.length will be between 1 and 20000.
nums[i] will be between 1 and 65535.
k will be between 1 and floor(nums.length / 3).
*/
class Solution {
private:
    std::vector<int> solution1(const std::vector<int>& A, const int K) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         */
        const int N = A.size();
        auto prefix_sum = std::vector<int>(N+1);
        prefix_sum[0] = 0;
        for (int i = 1; i <= N; ++i) {
            prefix_sum[i] = prefix_sum[i-1] + A[i-1];
        }
        auto position_left = std::vector<int>(N, 0);
        for (int i = K, max_sum = prefix_sum[K] - prefix_sum[0]; i < N; ++i) {
            const auto curr_sum = prefix_sum[i+1] - prefix_sum[i+1-K];
            if (curr_sum > max_sum) {
                position_left[i] = i+1-K;
                max_sum = curr_sum;
            } else {
                position_left[i] = position_left[i-1];
            }
        }
        auto position_right = std::vector<int>(N, N-K);
        for (int i = N-K-1, max_sum = prefix_sum[N] - prefix_sum[N-K]; i >= 0; --i) {
            const auto curr_sum = prefix_sum[i+K] - prefix_sum[i];
            if (curr_sum >= max_sum) {
                position_right[i] = i;
                max_sum = curr_sum;
            } else {
                position_right[i] = position_right[i+1];
            }
        }
        auto results = std::vector<int>(3);
        int max_sum = 0;
        for (int i = K; i <= N-2*K; ++i) {
            const auto left_pos = position_left[i-1];
            const auto right_pos = position_right[i+K];
            const int curr_sum =    (prefix_sum[left_pos+K] - prefix_sum[left_pos]) + 
                                    (prefix_sum[i+K] - prefix_sum[i]) + 
                                    (prefix_sum[right_pos+K] - prefix_sum[right_pos]);
            if (curr_sum > max_sum) {
                max_sum = curr_sum;
                results = { left_pos, i, right_pos };
            }
        }

        return results;
    }
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        return solution1(nums, k);        
    }
};
