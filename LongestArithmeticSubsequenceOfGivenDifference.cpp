/*
Given an integer array arr and an integer difference, 
return the length of the longest subsequence in arr which is an arithmetic sequence 
such that the difference between adjacent elements in the subsequence equals difference.

Example 1:
Input: arr = [1,2,3,4], difference = 1
Output: 4
Explanation: The longest arithmetic subsequence is [1,2,3,4].

Example 2:
Input: arr = [1,3,5,7], difference = 1
Output: 1
Explanation: The longest arithmetic subsequence is any single element.

Example 3:
Input: arr = [1,5,7,8,5,3,4,2,1], difference = -2
Output: 4
Explanation: The longest arithmetic subsequence is [7,5,3,1].

Constraints:
1 <= arr.length <= 10^5
-10^4 <= arr[i], difference <= 10^4
*/

class Solution {
private:
	int solution1(const std::vector<int>& A, const int diff) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         */
        const int N = A.size();
        if (not N) {
            return 0;
        }
        auto longest_arithmetic_sqn = 0;
        auto diff_to_index = std::unordered_map<int,int>();
        auto DP = std::vector<int>(N, 1);

        for (int i = 0; i < N; ++i) {
            if (diff_to_index.count(A[i] - diff)) {
               DP[i] += DP[diff_to_index[A[i] - diff]];
            } 
            diff_to_index[A[i]] = i;
            longest_arithmetic_sqn = std::max(longest_arithmetic_sqn, DP[i]);
        }

        return longest_arithmetic_sqn;
	}
public:
    int longestSubsequence(vector<int>& arr, int difference) {
      	return solution1(arr, difference); 
    }
};
