/*
Given an array of integers nums and a positive integer k, find whether it's possible to divide this array into k non-empty subsets whose sums are all equal. 

Example 1:
Input: nums = [4, 3, 2, 3, 5, 2, 1], k = 4
Output: True
Explanation: It's possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.

Note:
1 <= k <= len(nums) <= 16.
0 < nums[i] < 10000.
*/

class Solution {
private:
    // target == ∑ {v | v € V} / K
    int target;
    // `V` is a global copy of input `nums`
    std::vector<int> V;
    // size of `V`
    int N;
    // `subsetSum[i]` represents sum of i-th subset of `V`
    std::vector<int> subsetSum;
    // size of `subsetSum`
    int K;

    bool recurse1(const int i) {
        // This routine tries to place `V[i]` into "appropriate" subset.
        // It begins trying to fill first bucket, see if it succeeds,
        // then second bucket, and see if it succeeds, and so on.
        // If no subset succeeds, it will return false.
        // Will also short circuit and return false if we tried to 
        // fill a (currently) empty subset, which fails.
        // This is because it fills subsets from left to right, and so
        // if current bucket is empty (and failed), the next subset will
        // also be empty and fail.
        if (i >= N) {
            // Filled all subsets
            return true;
        }
        for (int k = 0; k < K; ++k) {
            if (subsetSum[k] + V[i] > target) {
                continue;
            }
            subsetSum[k] += V[i];
            if (recurse1(i+1)) {
                return true;
            }
            subsetSum[k] -= V[i];
            if (not subsetSum[k]) {
                return false;
            }
        }
        
        return false;    
    }
	bool solution1(const std::vector<int>& nums, const int k) {
        /* Time-Complexity:     O()
         * Space-Complexity:    O()
         */
        K = k;
        if (K == 1) {
            return true;
        }
        V = nums;
        N = nums.size();
        const int total_sum = std::accumulate(V.begin(), V.end(), 0);
        if (total_sum % K) {
            // total sum must be divisible by K
            return false;
        }
        target = total_sum / K;
        subsetSum = std::vector<int>(K, 0);
        // sort in descending order
        std::sort(V.rbegin(), V.rend());

        return recurse1(0);
	}
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
  		return solution1(nums, k);
    }
};
