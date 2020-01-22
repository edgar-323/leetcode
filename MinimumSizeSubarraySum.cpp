/*
Given an array of n positive integers and a positive integer s, find the minimal length of a contiguous subarray of which the sum ≥ s. If there isn't one, return 0 instead.

Example: 
Input: s = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: the subarray [4,3] has the minimal length under the problem constraint.
Follow up:
If you have figured out the O(n) solution, try coding another solution of which the time complexity is O(n log n). 
*/
class Solution {
private:
    int solution1(const int S, const std::vector<int>& A) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(1)
         */

        const int N = A.size();
        int min_len = INT_MAX;

        int left = 0;
        int right = 0;
        int sum = 0; 
        
        while (right <= N) {
            if (sum >= S) {
                min_len = std::min( min_len, right - left ); 
                sum -= A[left++];
            } else {
                if (right < N) {
                    sum += A[right];
                }
                ++right;
            }
        }

        return min_len == INT_MAX ? 0 : min_len; 
    }
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        return solution1(s, nums);        
    }
};
