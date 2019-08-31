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
            std::vector<std::vector<int>>& permutations, 
            std::vector<int>& nums, 
            const int pos) {
        if (pos >= N) {
            // We have produced a permutation
            permutations.push_back(nums);   
        }
        // We will swap nums[pos] with all values in nums[pos:N)
        // And we will produce permutations in this manner.
        for (int i = pos; i < N; ++i) {
            std::swap(nums[pos], nums[i]);
            recurse1(permutations, nums, pos+1);
            std::swap(nums[pos], nums[i]);
        }
    }
    
    std::vector<std::vector<int>> solution1(std::vector<int>& nums) {
        N = nums.size();
        std::vector<std::vector<int>> permutations;
        recurse1(permutations, nums, 0);
        return permutations;
    }
    
public:
    vector<vector<int>> permute(vector<int>& nums) {
        return solution1(nums);
    }
};
