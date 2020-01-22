/*
You are given an integer array A.
From some starting index, you can make a series of jumps.
The (1st, 3rd, 5th, ...) jumps in the series are called odd numbered jumps, and the (2nd, 4th, 6th, ...) jumps in the series are called even numbered jumps.
You may from index i jump forward to index j (with i < j) in the following way:
    1)  During odd numbered jumps (ie. jumps 1, 3, 5, ...), you jump to the index j such that A[i] <= A[j] and A[j] is the smallest possible value.  
        If there are multiple such indexes j, you can only jump to the smallest such index j.
    2)  During even numbered jumps (ie. jumps 2, 4, 6, ...), you jump to the index j such that A[i] >= A[j] and A[j] is the largest possible value.  
        If there are multiple such indexes j, you can only jump to the smallest such index j.
(It may be the case that for some index i, there are no legal jumps.)
A starting index is good if, starting from that index, you can reach the end of the array (index A.length - 1) by jumping some number of times (possibly 0 or more than once.)
Return the number of good starting indexes.

Example 1:
Input: [10,13,12,14,15]
Output: 2
Explanation: 
From starting index i = 0, we can jump to i = 2 (since A[2] is the smallest among A[1], A[2], A[3], A[4] that is greater or equal to A[0]), then we can't jump any more.
From starting index i = 1 and i = 2, we can jump to i = 3, then we can't jump any more.
From starting index i = 3, we can jump to i = 4, so we've reached the end.
From starting index i = 4, we've reached the end already.
In total, there are 2 different starting indexes (i = 3, i = 4) where we can reach the end with some number of jumps.

Example 2:
Input: [2,3,1,1,4]
Output: 3
Explanation: 
From starting index i = 0, we make jumps to i = 1, i = 2, i = 3:
During our 1st jump (odd numbered), we first jump to i = 1 because A[1] is the smallest value in (A[1], A[2], A[3], A[4]) that is greater than or equal to A[0].
During our 2nd jump (even numbered), we jump from i = 1 to i = 2 because A[2] is the largest value in (A[2], A[3], A[4]) that is less than or equal to A[1].  
A[3] is also the largest value, but 2 is a smaller index, so we can only jump to i = 2 and not i = 3.
During our 3rd jump (odd numbered), we jump from i = 2 to i = 3 because A[3] is the smallest value in (A[3], A[4]) that is greater than or equal to A[2].
We can't jump from i = 3 to i = 4, so the starting index i = 0 is not good.
In a similar manner, we can deduce that:
From starting index i = 1, we jump to i = 4, so we reach the end.
From starting index i = 2, we jump to i = 3, and then we can't jump anymore.
From starting index i = 3, we jump to i = 4, so we reach the end.
From starting index i = 4, we are already at the end.
In total, there are 3 different starting indexes (i = 1, i = 3, i = 4) where we can reach the end with some number of jumps.

Example 3:
Input: [5,1,3,4,2]
Output: 3
Explanation: 
We can reach the end from starting indexes 1, 2, and 4.

Note:
1 <= A.length <= 20000
0 <= A[i] < 100000
*/
class Solution {
private:
    int N;

    std::vector<int> get_next(const std::vector<int>& sorted_indices) {
        const int N = sorted_indices.size();
        auto next_greater_than = std::vector<int>(N, -1);
        auto index_stack = std::stack<int>();

        for (const auto curr_index : sorted_indices) {
            while (not index_stack.empty() and curr_index > index_stack.top()) {
                next_greater_than[index_stack.top()] = curr_index;
                index_stack.pop();
            }
            index_stack.push(curr_index);
        }

        return next_greater_than;
    }

    bool recurse1(
            const int i,
            const bool is_odd_jump,
            std::vector<std::vector<int>>& cache,
            const std::vector<int>& next_greater_than,
            const std::vector<int>& next_less_than) {
        if (cache[i][is_odd_jump] >= 0) {
            return cache[i][is_odd_jump];
        }
        bool can_jump;
        if (i == N-1) {
            can_jump = true;
        } if (is_odd_jump) {
            can_jump =  next_greater_than[i] >= 0 and 
                        recurse1(next_greater_than[i], not is_odd_jump, cachem next_greater_than, next_less_than);
        } else {
            can_jump =  next_less_than[i] >= 0 and 
                        recurse1(next_less_than[i], not is_odd_jump, cache, next_greater_than, next_less_than);
        }
        return cache[i][is_odd_jump] = can_jump;
    }

    int solution1(const std::vector<int>& A) {
        /* Time-Complexity:     O(N * log(N))
         * Space-Complexity:    O(N)
         */
        /* Explanation:
         * Compute:
         *      next_greater_than[i]    =   j 
         *                                  where i < j and A[j] = min{ A[i+1], ..., A[N-1] } s.t. A[i] <= A[j] 
         *                                  (if multiple A[j] exist then j will be minimum index satisfying this requirement) 
         *                                  (if no such j exists, then next_greater_than[i] = -1)
         *      
         *      next_less_than[i]       =   j
         *                                  where i < j and A[j] = max{ A[i+1], ..., A[N-1] } s.t. A[i] >= A[j]
         *                                  (if multiple A[j] exist then j will be minimum index satisfying this requirement)
         *                                  (if no such j exists, then next_less_than[i] = -1)
         * 
         * By definition of this problem, if we are @ index i and the parity of our jump is odd, then we need to see if we can reach
         * the end by either already being there (i == N-1) or by jumping to next allowed position (next_greater_than[i], if it exists).
         * We can easily solve this in linear time using dynamic programming, assuming next_greater_than[] and next_less_than[] are 
         * correctly computed.
         *
         * How to compute next_greater_than[] ?
         * Consider the array of pairs B[], where
         *      B[i] = (A[i], i) = (b0, b1)
         * 
         * Let's sort B[] by its first pair values (i.e, sort by b0).
         * This is exactly the same as sorting A[] but by sorting B[], we get to see the former index of A[i].
         * Now we know that B[i][0] <= B[j][0] for all i <= j
         *
         * Lets traverse B[] in its now sorted order and maintain a stack `index_stack`.
         * Suppose, we are at B[k], and lets curr_index = B[k][1] (i.e., the index where A[k] was initially at).
         * If the stack is currently empty, we simply push curr_index to index_stack.
         * Otherwise, we check if the index at the top of the stack call it `top_index` is less than curr_index.
         * If so then we alrealdy know that A[top_index] <= A[curr_index] (because B[] is sorted this way) and since we also just
         * checked that top_index < curr_index, then we know that next_greater_than[top_index] = curr_index
         *
         * We continue to pop the stack until it satisfies this property, and all of these indices will have their next_greater_than[] 
         * set to curr_index.
         * 
         * This tells us that the stack is monotonically decreasing.
         * With this info we can successfully compute next_greater_than[i] where possible.
         * 
         * Building next_greater_than[] via this motonic stack takes O(N) time.
         * However, sorting B[] takes (N * log(N)) time.
         *
         * How to compute next_less_than[] ?
         * Again, consider B[], but now let's sort it in descending order.
         * With similar argument, when building the monotic stack and traversing B[].
         * We know that if curr_index > top_index, then it must be the case that A[top_index] >= A[curr_index],
         * and so we can be sure that next_less_than[top_index] = curr_index.        
         */
        N = A.size();

        auto indices = std::vector<int>(N);
        for (int index = 0; index < N; ++index) {
            indices[index] = index;
        }
        std::sort(indices.begin(), indices.end(),
                    [&A]
                    (const int i, const int j) -> bool {
                        return A[i] == A[j] ? i < j : A[i] < A[j];
                    }); 
        const auto  next_greater_than = get_next(indices);
        std::sort(indices.begin(), indices.end(),
                    [&A]
                    (const int i, const int j) -> bool {
                        return A[i] == A[j] ? i < j : A[i] > A[j];
                    });
        const auto next_less_than = get_next(indices);

        auto cache = std::vector<std::vector<int>>(N, std::vector<int>(2, -1));
        int ans = 0;
        for (int i = 0; i < N; ++i) {
            if (recurse1(i, true, cache, next_greater_than , next_less_than)) {
                ++ans;
            }
        }

        return ans;
    }
public:
    int oddEvenJumps(vector<int>& A) {
        return solution1(A);       
    }
};
