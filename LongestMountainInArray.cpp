/*
Let's call any (contiguous) subarray B (of A) a mountain if the following properties hold:
    1) B.length >= 3
    2) There exists some 0 < i < B.length - 1 such that B[0] < B[1] < ... B[i-1] < B[i] > B[i+1] > ... > B[B.length - 1]
(Note that B could be any subarray of A, including the entire array A.)
Given an array A of integers, return the length of the longest mountain. 
Return 0 if there is no mountain.

Example 1:
Input: [2,1,4,7,3,2,5]
Output: 5
Explanation: The largest mountain is [1,4,7,3,2] which has length 5.

Example 2:
Input: [2,2,2]
Output: 0
Explanation: There is no mountain.

Note:
0 <= A.length <= 10000
0 <= A[i] <= 10000

Follow up:
Can you solve it using only one pass?
Can you solve it in O(1) space?
*/
class Solution {
private:
    int solution1(const std::vector<int>& A) {
        const int N = A.size(); 

        int max_len = 0;
        int left = 0;
        int right = 0;
        
        while (right < N) {
            // lets get next mountain.
            while (right < N-1 and A[right] < A[right+1]) {
                ++right;
            }
            if (left == right) {
                left = ++right;
                continue;
            }
            int peak = right;
            while (right < N-1 and A[right] > A[right+1]) {
                ++right;
            }
            if (right > peak and right - left >= 2) {
                max_len = std::max( max_len, right - left + 1);
            }
            left = right;  
        }

        return max_len;
    }
public:
    int longestMountain(vector<int>& A) {
        return solution1(A); 
    }
};