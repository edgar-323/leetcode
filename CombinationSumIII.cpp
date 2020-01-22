/*
Find all possible combinations of k numbers that add up to a number n, given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.

Note:
All numbers will be positive integers.
The solution set must not contain duplicate combinations.

Example 1:
Input: k = 3, n = 7
Output: [[1,2,4]]

Example 2:
Input: k = 3, n = 9
Output: [[1,2,6], [1,3,5], [2,3,4]]
*/
class Solution {
private:
    static const int MAX_NUM = 9;
    int N, K;
    
    bool available(const int num, const int available_nums) {
        return available_nums & (1 << num);
    }
    
    int pick_number(const int num, const int available_nums) {
        return available_nums & (~(1 << num));
    }

    void recurse1(
            const int curr_sum,
            std::vector<int>& curr_nums,
            const int available_nums,
            std::vector<bool>& seen,
            std::vector<std::vector<int>>& results) {
        if (curr_sum == N and curr_nums.size() == K) {
            if (not seen[available_nums]) {
                results.push_back(curr_nums);
                seen[available_nums] = true;
            }
            return;
        }
        for (int num = 0; num < MAX_NUM; ++num) {
            if (available(num, available_nums) and curr_sum + num + 1 <= N and curr_nums.size() < K) {
                curr_nums.push_back(num+1);
                recurse1(curr_sum + num + 1, curr_nums, pick_number(num, available_nums), seen, results);
                curr_nums.pop_back();
            }
        }
    }

	std::vector<std::vector<int>> solution1(const int K, const int N) {
        this->N = N;
        this->K = K;
        auto results = std::vector<std::vector<int>>();
        auto seen = std::vector<bool>(1 << MAX_NUM, false);
        auto curr_nums = std::vector<int>();
        curr_nums.reserve(K);
        recurse1(0, curr_nums, (1 << MAX_NUM) - 1, seen, results);

        return results;
	}
public:
    vector<vector<int>> combinationSum3(int k, int n) {
  		return solution1(k, n);      
    }
};
