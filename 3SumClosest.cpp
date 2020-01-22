/*
Given an array nums of n integers and an integer target, 
find three integers in nums such that the sum is closest to target. 
Return the sum of the three integers. 
You may assume that each input would have exactly one solution.

Example:
Given array nums = [-1, 2, 1, -4], and target = 1.
The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
*/
class Solution {
private:
    int solution1(std::vector<int>& A, const int target) {
        /* Time-Complexity:     O(N^2)
         * Space-Complexity:    O(1)  (Assuming Sorting Is Done In-Place)
         */

        // Assume A.size() >= 3 // else question makes no sense.
        // Also assume for distinct (i, j, k) 
        //      INT_MIN <= (A[i] + A[j] + A[k]) <= INT_MAX 
        //
        const int N = A.size();
        std::sort(A.begin(), A.end());
        
        int sum 
        int min_diff = INT_MAX;
        for (int i = 0; i < N; ++i) {
            int j = i+1;
            int k = N-1;
            while (j < k) {
                const auto curr_sum = A[i] + A[j] + A[k]; 
                const auto curr_diff = std::abs(target - curr_sum); 
                if (curr_diff < min_diff) {
                    sum = curr_sum;
                    min_diff = curr_diff;
                }
                if (curr_sum < target) {
                    // sum is too small -> increase it -> increment j
                    ++j;
                } else {
                    // sum is too big -> decrease it -> decrement k
                    --k; 
                }
            }
        }

        return sum;
    }
public:
    int threeSumClosest(vector<int>& nums, int target) {
        return solution1(nums, target);        
    }
};
