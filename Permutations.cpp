/*
Given a recurse1ion of distinct integers, return all possible permutations.

Example:
Input: [1,2,3]
Output:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]
*/

class Solution {
private:
    int N;

    void recurse1(
            const int i,
            std::vector<int>& nums,
            std::vector<std::vector<int>>& results) {
        if (i == N) {
            // we've produced a permutation
            results.push_back(nums);
        }
        // For j € {i,...,N-1}, swap nums[i] with nums[j] and recurse on nums[i+1:N]
        // I.e., produces permuations where ith number switches with jth number
        for (int j = i; j < N; ++j) {
            std::swap(nums[i], nums[j]);
            recurse1(i+1, nums, results);
            std::swap(nums[i], nums[j]);
        }
    }
    
    std::vector<std::vector<int>> solution1(std::vector<int>& nums) {
        N = nums.size();
        auto results = std::vector<std::vector<int>>();
        recurse1(0, nums, results);

        return results;
    }
    
public:
    vector<vector<int>> permute(vector<int>& nums) {
        return solution1(nums);
    }
};

