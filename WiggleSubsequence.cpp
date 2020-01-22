/*
A sequence of numbers is called a wiggle sequence if the differences between successive numbers strictly alternate between positive and negative. 
The first difference (if one exists) may be either positive or negative. A sequence with fewer than two elements is trivially a wiggle sequence.

For example, [1,7,4,9,2,5] is a wiggle sequence because the differences (6,-3,5,-7,3) are alternately positive and negative. 
In contrast, [1,4,7,2,5] and [1,7,4,5,5] are not wiggle sequences, the first because its first two differences are positive and the second because its last difference is zero.

Given a sequence of integers, return the length of the longest subsequence that is a wiggle sequence. 
A subsequence is obtained by deleting some number of elements (eventually, also zero) from the original sequence, leaving the remaining elements in their original order.

Example 1:
Input: [1,7,4,9,2,5]
Output: 6
Explanation: The entire sequence is a wiggle sequence.

Example 2:
Input: [1,17,5,10,13,15,10,5,16,8]
Output: 7
Explanation: There are several subsequences that achieve this length. One is [1,17,10,13,10,16,8].

Example 3:
Input: [1,2,3,4,5,6,7,8,9]
Output: 2

Follow up:
Can you do it in O(n) time?
*/

class Solution {
private:
    /*****************************************************************************************/
	int solution1(const vector<int>& A) {
        /* Time-Complexity:     O(N^2)
         * Space-Complexity:    O(N)
         */

        const int N = A.size();
        if (not N) {
            return 0;
        }

        int max_wiggle = 0;

        auto positive = vector<int>(N, 1);
        auto negative = vector<int>(N, 1);

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < i; ++j) {
                if (A[j] > A[i]) {
                    positive[i] = max(positive[i], 1 + negative[j]);
                } else if (A[j] < A[i]) {
                    negative[i] = max(negative[i], 1 + positive[j]);
                }
            }
            max_wiggle = max<int>({ max_wiggle, positive[i], negative[i] });
        }
        
        return max_wiggle;
	}
    /*****************************************************************************************/
    int solution2(const vector<int>& A) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         */
        
        const int N = A.size();
        if (not N) {
            return 0;
        }
        
        auto positive = vector<int>(N);
        auto negative = vector<int>(N);

        positive[0] = 1;
        negative[0] = 1;
        for (int i = 1; i < N; ++i) {
            if (A[i] > A[i-1]) {
                positive[i] = 1 + negative[i-1];
                negative[i] = negative[i-1];
            } else if (A[i] < A[i-1]) {
                negative[i] = 1 + positive[i-1];
                positive[i] = positive[i-1];
            } else {
                positive[i] = positive[i-1];
                negative[i] = negative[i-1];
            }
        }

        return max(positive[N-1], negative[N-1]);
    }
    /*****************************************************************************************/       
public:
    int wiggleMaxLength(vector<int>& nums) {
  		return solution2(nums);      
    }
};
