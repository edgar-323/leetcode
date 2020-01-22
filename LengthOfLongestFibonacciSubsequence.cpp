/*
A sequence X_1, X_2, ..., X_n is fibonacci-like if:
    1) n >= 3
    2) X_i + X_{i+1} = X_{i+2} for all i + 2 <= n
Given a strictly increasing array A of positive integers forming a sequence, find the length of the longest fibonacci-like subsequence of A.  If one does not exist, return 0.
(Recall that a subsequence is derived from another sequence A by deleting any number of elements (including none) from A, without changing the order of the remaining elements.  For example, [3, 5, 8] is a subsequence of [3, 4, 5, 6, 7, 8].)
 
Example 1:

Input: [1,2,3,4,5,6,7,8]
Output: 5
Explanation:
The longest subsequence that is fibonacci-like: [1,2,3,5,8].

Example 2:
Input: [1,3,7,11,12,14,18]
Output: 3
Explanation:
The longest subsequence that is fibonacci-like:
[1,11,12], [3,11,14] or [7,11,18].

Note:
3 <= A.length <= 1000
1 <= A[0] < A[1] < ... < A[A.length - 1] <= 10^9
(The time limit has been reduced by 50% for submissions in Java, C, and C++.)
*/

class Solution {
private:
	int solution1(const std::vector<int>& A) {
        /* Time-Complexity:     O(N^2)
         * Space-Complexity:    O(N^2)
         */
        /*
        Intuition
        Think of two consecutive terms A[i], A[j] in a fibonacci-like subsequence as a single node (i, j), and the entire subsequence is a path between these consecutive nodes. 
        For example, with the fibonacci-like subsequence (A[1] = 2, A[2] = 3, A[4] = 5, A[7] = 8, A[10] = 13), we have the path between nodes (1, 2) <-> (2, 4) <-> (4, 7) <-> (7, 10).

        The motivation for this is that two nodes (i, j) and (j, k) are connected if and only if A[i] + A[j] == A[k], and we needed this amount of information to know about this connection. 
        Now we have a problem similar to Longest Increasing Subsequence.

        Algorithm
        Let longest[i, j] be the longest path ending in [i, j]. 
        Then longest[j, k] = longest[i, j] + 1 if (i, j) and (j, k) are connected. 
        Since i is uniquely determined as A.index(A[k] - A[j]), this is efficient: we check for each j < k what i is potentially, and update longest[j, k] accordingly.
        */

        const int N = A.size();
        
        int longest_fib_sqn = 0;

        auto index_map = std::unordered_map<int,int>();
        for (int i = 0; i < N; ++i) {
            index_map[A[i]] = i;
        }
        auto DP = std::vector<std::vector<int>>(N, std::vector<int>(N, 0));
        for (int k = 0; k < N; ++k) {
            for (int j = 0; j < k; ++j) {
                if (not index_map.count(A[k] - A[j])) {
                    continue;
                }
                const int i = index_map[A[k] - A[j]];
                if (i >= j) {
                    continue;
                }
                DP[j][k] =  DP[i][j] > 2 ? DP[i][j] + 1 : 3;
                longest_fib_sqn = std::max(longest_fib_sqn, DP[j][k]);
            }
        }

        return longest_fib_sqn >= 3 ? longest_fib_sqn : 0; 
	}
public:
    int lenLongestFibSubseq(vector<int>& A) {
  		return solution1(A);      
    }
};
