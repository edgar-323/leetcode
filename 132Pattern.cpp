/*
Given a sequence of n integers a1, a2, ..., an, a 132 pattern is a subsequence ai, aj, ak such that i < j < k and ai < ak < aj. 
Design an algorithm that takes a list of n numbers as input and checks whether there is a 132 pattern in the list.
Note: n will be less than 15,000.

Example 1:
Input: [1, 2, 3, 4]
Output: False
Explanation: There is no 132 pattern in the sequence.

Example 2:
Input: [3, 1, 4, 2]
Output: True
Explanation: There is a 132 pattern in the sequence: [1, 4, 2].

Example 3:
Input: [-1, 3, 2, 0]
Output: True
Explanation: There are three 132 patterns in the sequence: [-1, 3, 2], [-1, 3, 0] and [-1, 2, 0].
*/
class Solution {
private:
    bool solution1(const std::vector<int>& nums) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         *      Where:
         *          N = len(nums)
         */
        /* Explanation:
         * Before we dwell into the problem, suppose (instead) we were trying to find tuple (i, j, k) s.t. 
         * A1 < A2 < A3 (A1 == A[i], A2 == A[j], A3 == A[k]). 
         * Then (if searching in reverse), we would first find A3, then A2, and finally A1.
         * Okay, now back to the actual problem.
         * In our case we want tuple (i, j, k) s.t. A1 < A3 < A2.
         * So, it may be beneficial to first search to A2, followed by A3, and finally A1.
         * Suppose we search for A2 is A[] (in reverse order).
         * Then, we want to maintain a stack that keeps possible values of A3.
         * In order to keep this invariant, suppose we are at nums[i].
         *  
         */
        auto stack = std::stack<int>();
        int s3 = INT_MIN;
        for (int i = nums.size() - 1; i >= 0; --i) {
            if (nums[i] < s3) {
                return true;
            }
            while (not stack.empty() and nums[i] > stack.top()) {
                s3 = stack.top();
                stack.pop();
            }
            stack.push(nums[i]);
        }
        return false;
    }
public:
    bool find132pattern(vector<int>& nums) {
        return solution1(nums);        
    }
};
