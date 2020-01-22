/*
Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

Example:
Input: n = 4, k = 2
Output:
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
*/
class Solution {
private:
    int N, K;

    void recurse1(const int i, std::vector<int>& curr_nums, std::vector<std::vector<int>>& results) {
        // If we already have a combination of K numbers, them add them to results and terminate recursion
        if (K == curr_nums.size()) {
            results.push_back(curr_nums);
            return;
        }
        // Assume only numbers {i,...,N} are available
        for (int j = i; j <= N; ++j) {
            // Add number j € {i,...,N} and find combinations in {j+1, ..., N}
            curr_nums.push_back(j);
            recurse1(j+1, curr_nums, results);
            curr_nums.pop_back();
        }
    }

	std::vector<std::vector<int>> solution1(const int N, const int K) {
        this->N = N;
        this->K = K;
        auto results = std::vector<std::vector<int>>();
        auto curr_nums = std::vector<int>();
        curr_nums.reserve(K);
        recurse1(1, curr_nums, results);

        return results;
	}

public:
    vector<vector<int>> combine(int n, int k) {
  		return solution1(n, k);      
    }
};
