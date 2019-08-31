/*
Write a function to find the longest common prefix string amongst an array of strings.

If there is no common prefix, return an empty string "".

Example 1:
Input: ["flower","flow","flight"]
Output: "fl"

Example 2:
Input: ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.


Note:
All given inputs are in lowercase letters a-z.
*/

class Solution {
    private:
        std::string solution1(const std::vector<std::string>& strs) {
            std::string solution = "";

            const int N = strs.size();
            if (N == 0 or strs[0].size() == 0) {
                return solution;
            }
            
            solution = strs[0];
            
            for (const auto& str : strs) {
                const int M = std::min(solution.size(), str.size());
                int j = 0;
                for (j = 0; j < M; ++j) {
                    if (solution[j] != str[j]) {
                        break;
                    }
                }
                if (j != solution.size()) {
                    solution = solution.substr(0, j);
                }
            }

            return solution;
        }
    public:
        string longestCommonPrefix(vector<string>& strs) {
            return solution1(strs, solution);
        }
};
