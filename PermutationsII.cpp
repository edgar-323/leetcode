/*
Given a collection of numbers that might contain duplicates, return all possible unique permutations.

Example:
Input: [1,1,2]
Output:
[
  [1,1,2],
  [1,2,1],
  [2,1,1]
]
*/
class Solution {
private:
    int N;

    void recurse1(
            std::vector<int>& curr_nums,
            std::vector<bool>& visited,
            const std::vector<int>& nums,
            std::vector<std::vector<int>>& results) {
        if (curr_nums.size() == N) {
            results.push_back(curr_nums);
            return;
        }
        for (int i = 0; i < N; ++i) {
            if (visited[i] or (i and nums[i] == nums[i-1] and visited[i-1])) {
                continue;
            }
            curr_nums.push_back(nums[i]);
            visited[i] = true;
            recurse1(curr_nums, visited, nums, results);
            curr_nums.pop_back();
            visited[i] = false;
        }
    }

	std::vector<std::vector<int>> solution1(std::vector<int>& nums) {
        N = nums.size();
        std::sort(nums.begin(), nums.end());
        auto curr_nums = std::vector<int>();
        curr_nums.reserve(N);
        auto visited = std::vector<bool>(N, false);
        auto results = std::vector<std::vector<int>>();
        recurse1(curr_nums, visited, nums, results);

        return results;
	}
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
  		return solution1(nums);      
    }
};
