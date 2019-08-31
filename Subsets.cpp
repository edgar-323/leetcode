/*
Given a set of distinct integers, nums, return all possible subsets (the power set).

Note: The solution set must not contain duplicate subsets.

Example:

Input: nums = [1,2,3]
Output:
[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
*/

class Solution {
private:
    void recurse1(vector<int>& nums, int pos, vector<int>& curr, 
                 vector<vector<int>>& results, const int N) {
        if (pos >= N) {
            results.push_back(curr);
            return;
        }
        recurse1(nums, pos+1, curr, results, N);
        vector<int> v = vector(curr);
        v.push_back(nums[pos]);
        recurse1(nums, pos+1, v, results, N);
    }
    
    std::vector<std::vector<int>> solution1(std::vector<int>& nums) {
        std::vector<std::vector<int>> results;
        std::vector<int> empty;
        recurse1(nums, 0, empty, results, nums.size());
        return results;
    }
    
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        return solution1(nums);
    }
};
