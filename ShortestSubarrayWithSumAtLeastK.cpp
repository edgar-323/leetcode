/*
Return the length of the shortest, non-empty, contiguous subarray of A with sum at least K.
If there is no non-empty subarray with sum at least K, return -1.

Example 1:
Input: A = [1], K = 1
Output: 1

Example 2:
Input: A = [1,2], K = 4
Output: -1

Example 3:
Input: A = [2,-1,2], K = 3
Output: 3

Note:
1 <= A.length <= 50000
-10 ^ 5 <= A[i] <= 10 ^ 5
1 <= K <= 10 ^ 9
*/
class Solution {
private:
    typedef long long LL;
    
    LL sum(const int i, const int j, const std::vector<LL>& prefix_sum) {
        return prefix_sum[j] - prefix_sum[i];
    }

    int solution1(const std::vector<int>& A, const int K) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         */
        /* INTUITION:
         * First, we let:
         *      prefix_sum[i] = ∑ { A[k] | k € {0,...,i} }
         * So then:
         *      SUM[i,j] = ∑ { A[k] | k € {i,...,j} }
         *               = prefix_sum[j] - prefix_sum[i]
         * 
         * Let:
         *      OPT[y] = max{ x } s.t. SUM[x,y] >= K
         * Then:
         *      1)  If x1 < x2 and SUM[x1,x2] <= 0
         *          then x1 can never be a candidate for OPT[y]
         *          because, suppose SUM[x1,y] >= K, then
         *          SUM[x2,y] >= SUM[x1,y]
         *          (this is because SUM[x1,x2] is non-positive).
         *          Thus, x2 will be a better candidate for OPT[y]
         *          than x1.
         *          This implies that candidates x for OPT[y],
         *          will be monotonically increasing in prefix_sum[x].
         *      
         *      2)  Suppose OPT[y] = x.
         *          Then, there is no need to consider x as a candidate for OPT[y2]
         *          where y < y2.
         *          This is because, suppose x = OPT[y2], then we are looking at
         *          a subarray length of (y2 - x), which is bigger than (y - x).
         *
         * ALGORITHM:
         *
         * Maintain a montonic deque of indices of values of prefix_sum[].
         * I.e., a deque of {x0, x1, ...} s.t. prefix_sum[x0] <= prefix_sum[x1] <= ...
         *
         * When considering index y, we pop x_i from the end in order to maintain
         * our monotonic invariant.
         * I.e., prefix_sum[x0] <= prefix_sum[x1] <= ... <= prefix_sum[y].
         *
         * If SUM[x0,y] >= K, then we don't need to consider x0 again (so we can pop
         * it from the front of the deque while updating our answer).
         */
        const int N = A.size();

        auto prefix_sum = std::vector<LL>(N+1);
        prefix_sum[0] = 0;
        for (int i = 1; i <= N; ++i) {
            prefix_sum[i] = prefix_sum[i-1] + A[i-1];
        }
        
        int shortest_subarray = INT_MAX;
        
        auto deque = std::deque<int>();

        for (int y = 0; y <= N; ++y) {
            while (not deque.empty() and sum( deque.back(), y, prefix_sum ) <= 0) { 
                deque.pop_back();
            }
            while (not deque.empty() and sum( deque.front(), y, prefix_sum ) >= K) {
                shortest_subarray = std::min( shortest_subarray, y - deque.front() );
                deque.pop_front();
            }
            deque.push_back(y);
        } 

        return shortest_subarray == INT_MAX ? -1 : shortest_subarray; 
    }
public:
    int shortestSubarray(vector<int>& A, int K) {
        return solution1(A, K);        
    }
};
