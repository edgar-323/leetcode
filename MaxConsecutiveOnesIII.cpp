/*
Given an array A of 0s and 1s, we may change up to K values from 0 to 1.
Return the length of the longest (contiguous) subarray that contains only 1s. 

Example 1:
Input: A = [1,1,1,0,0,0,1,1,1,1,0], K = 2
Output: 6
Explanation: 
[1,1,1,0,0,1,1,1,1,1,1]
Bolded numbers were flipped from 0 to 1.  The longest subarray is underlined.

Example 2:
Input: A = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], K = 3
Output: 10
Explanation: 
[0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
Bolded numbers were flipped from 0 to 1.  The longest subarray is underlined.

Note:
1 <= A.length <= 20000
0 <= K <= A.length
A[i] is 0 or 1 
*/
class Solution {
private:
    int solution1(const std::vector<int>& A, const int K) {
        const int N = A.size();
        auto deque = std::deque<int>();     
        int left = 0;
        int right = 0;    
        // initial population of deque
        while (right < N and deque.size() < K) {
            if (not A[right++]) {
                deque.push_back(right);
            }
        }
        int longest_stream = 0;
        while (right < N) {
            if (not A[right++]) {
                longest_stream = std::max(longest_stream, right - left - 1);
                if (deque.empty()) {
                    left = right;
                } else {
                    left = deque.front(); deque.pop_front();
                    deque.push_back(right);
                }
            }
        }
        longest_stream = std::max(longest_stream, right - left);
        return longest_stream;
    }

public:
    int longestOnes(vector<int>& A, int K) {
        return solution1(A, K);
    }
};
