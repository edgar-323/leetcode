/*
This question is the same as "Max Chunks to Make Sorted" except the integers of the given array are not necessarily distinct, 
the input array could be up to length 2000, and the elements could be up to 10^8.
Given an array arr of integers (not necessarily distinct), we split the array into some number of "chunks" (partitions), and individually sort each chunk.  
After concatenating them, the result equals the sorted array.
What is the most number of chunks we could have made?

Example 1:
Input: arr = [5,4,3,2,1]
Output: 1
Explanation:
Splitting into two or more chunks will not return the required result.
For example, splitting into [5, 4], [3, 2, 1] will result in [4, 5, 1, 2, 3], which isn't sorted.

Example 2:
Input: arr = [2,1,3,4,4]
Output: 4
Explanation:
We can split into two chunks, such as [2, 1], [3, 4, 4].
However, splitting into [2, 1], [3], [4], [4] is the highest number of chunks possible.

Note:
    1)  arr will have length in range [1, 2000].
    2)  arr[i] will be an integer in range [0, 10**8].
*/
class Solution {
private:
    int solution1(const std::vector<int>& A) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         */

        const int N = A.size();
        auto post_min = std::vector<int>(N);
        post_min[N-1] = A[N-1]; 
        for (int i = N-2; i >= 0; --i) {
            post_min[i] = std::min(A[i], post_min[i+1]);
        }
        auto pre_max = std::vector<int>(N);
        pre_max[0] = A[0];
        for (int i = 1; i < N; ++i) {
            pre_max[i] = std::max(A[i], pre_max[i-1]);
        } 
        int chunks = 0;
        for (int i = 0; i < N-1; ++i) { 
            if (pre_max[i] <= post_min[i+1]) {
                ++chunks;
            }
        }
        
        return chunks+1;
    }
public:
    int maxChunksToSorted(vector<int>& arr) {
        return solution1(arr);
    }
};
