/*
Given an unsorted array of integers, find the number of longest increasing subsequence.

Example 1:
Input: [1,3,5,4,7]
Output: 2
Explanation: The two longest increasing subsequence are [1, 3, 4, 7] and [1, 3, 5, 7].

Example 2:
Input: [2,2,2,2,2]
Output: 5
Explanation: The length of longest continuous increasing subsequence is 1, and there are 5 subsequences' length is 1, so output 5.

Note: Length of the given array will be not exceed 2000 and the answer is guaranteed to be fit in 32-bit signed int.
*/

class Solution {
private:
    bool edge_exists(const int u, const int v, const std::vector<int>& nums) {
        // Does edge <u, v> exist in DAG of LIS(nums)?
        return nums[v] > nums[u];
    }

	int solution1(const std::vector<int>& nums) {
        /* Time-Complexity:     O( N^2 )
         * Space-Complexity:    O(  N  )
         * */
        const int N = nums.size();
        if (N == 0) {
            return 0;
        }
        
        // DP[i] = length of LIS ending @ index i
        auto DP     = std::vector<int>( N, 1 );
        // counts[i] = # of paths who of length DP[i] ending @ index i
        auto counts = std::vector<int>( N, 1 );
        // max_subsq = LIS
        int max_subsq = 1;
        // Resolve (DP[], counts[], max_subsq)
        for (int v = 1; v < N; ++v) {
            for (int u = 0; u < v; ++u) {
                if (edge_exists(u, v, nums)) {
                    if (DP[u] >= DP[v]) {
                        DP[v] = DP[u] + 1;
                        counts[v] = counts[u];
                    } else if (DP[v] == DP[u] + 1) {
                        counts[v] += counts[u];
                    }
                }
            }
            max_subsq = std::max( max_subsq, DP[v] );
        }
        // Now that (DP[], counts[], max_subsq) have been resolved,
        // return ∑ { counts[i] | DP[i] == max_subsq, i € [0,N) }
        int num_lis = 0;
	    for (int i = 0; i < N; ++i) {
            num_lis +=  DP[i] == max_subsq ? 
                        counts[i] : 
                        0;
        }	
		return num_lis;
    }

public:
    int findNumberOfLIS(vector<int>& nums) {
    	return solution1( nums );    
    }
};
