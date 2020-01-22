/*
Given an array nums of n integers and an integer target, are there elements a, b, c, and d in nums such that a + b + c + d = target? 
Find all unique quadruplets in the array which gives the sum of target.
Note:
The solution set must not contain duplicate quadruplets.

Example:
Given array nums = [1, 0, -1, 0, -2, 2], and target = 0.

A solution set is:
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]
*/
class Solution {
private:
    void two_sum1(
        	const std::vector<int>& A,
            int left,
            int right,
            const int target,
            const int K,
            std::vector<int>& curr,
            std::vector<std::vector<int>>& results) {
		while (left < right) {
            const auto sum = A[left] + A[right];
            if (sum < target) {
                ++left;
            } else if (sum > target) {
                --right;
            } else {
                curr.push_back(A[left]);
                curr.push_back(A[right]);
                results.push_back(curr);
                curr.pop_back();
                curr.pop_back();
                ++left;
                while (left < right and A[left-1] == A[left]) {
                    ++left;
                }
            }
        }
    }

    void recurse1(
            const std::vector<int>& A,
            const int left,
            const int right,
            const int target,
            const int K,
            std::vector<int>& curr,
            std::vector<std::vector<int>>& results) {
        // Early Termination: 
        if (right - left + 1 < K or
            K < 2 or
            target < A[left] * K or
            target > A[right] * K ) {
            return;
        }
        // Two-Sum
        if (K == 2) {
            two_sum1(A, left, right, target, K, curr, results);
            return;
        }
        // General K-Sum
        for (int i = left; i <= right; ++i) {
            if (i == left or A[i-1] != A[i]) {
                curr.push_back(A[i]);
                recurse1(A, i+1, right, target - A[i], K-1, curr, results);
                curr.pop_back();
            }
        }
    }

	std::vector<std::vector<int>> solution1(std::vector<int>& A, const int target) {
        std::sort(A.begin(), A.end());
        auto results = std::vector<std::vector<int>>();
        auto curr = std::vector<int>();
        recurse1(A, 0, A.size()-1, target, 4, curr, results);

        return results;
	}
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
 		return solution1(nums, target);       
    }
};
