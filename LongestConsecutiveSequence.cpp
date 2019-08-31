/*
Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
Your algorithm should run in O(n) complexity.

Example:
Input: [100, 4, 200, 1, 3, 2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.
*/

class Solution {
private:
    void dfs(int num, std::unordered_map<int, int>& seen) {
        if (seen.count(num) == 0 || seen.at(num) > 1) {
            return;
        } 
        dfs(num+1, seen);
        seen.at(num) += ((seen.count(num+1) > 0) ? seen.at(num+1) : 0);
    }
    
    int solution1(vector<int>& nums) {
        int maxSeq = 0;
        const int N = nums.size();
        std::unordered_map<int, int> seen;
        for (auto& num : nums) {
            if (seen.count(num) == 0) {
                seen.emplace(num, 1);
            }
        }
        for (auto& pair : seen) {
            dfs(pair.first, seen);
            maxSeq = max(maxSeq, seen.at(pair.first));
        }
        return maxSeq;
    }
    
public:
    int longestConsecutive(vector<int>& nums) {
        return solution1(nums);
    }
};
