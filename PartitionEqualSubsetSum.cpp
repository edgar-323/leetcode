/*
Given a non-empty array containing only positive integers, find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.
Note:
Each of the array element will not exceed 100.
The array size will not exceed 200.
 
Example 1:
Input: [1, 5, 11, 5]
Output: true
Explanation: The array can be partitioned as [1, 5, 5] and [11].
 
Example 2:
Input: [1, 2, 3, 5]
Output: false
Explanation: The array cannot be partitioned into equal sum subsets.
*/

class Solution {
private:
    int sum(const std::vector<int>& nums) {
        return std::accumulate( nums.begin(), nums.end(), 0 );
    }
    
    bool helper(const std::vector<int>& V, const int S, const int i){
        if (i >= V.size() || S < V[i]) {
            return false;  
        } else if (S == V[i]) {
            return true;
        } 
        return helper( V, S-V[i], i+1 ) || helper( V, S, i+1);
    }
    
    int ZeroOneKS(const std::vector<int>& V, int W) {
        /* KNAPSACK WITHOUT REPITITION */
        /* Time-Complexity:     O( N*W )
         * Space-Complexity:    O( N*W )
         * */
        const int N = V.size();
        if (N == 0) {
            return 0;
        }
        
        int DP[N][W+1];
        
        for (int w = 0; w <= W; ++w) {
            DP[0][w] = (w < V[0]) ? 0 : V[0];
        }
        for (int i = 1; i < N; ++i) {
            for (int w = 0; w <= W; ++w) {
                DP[i][w] = (w < V[i]) ? 
                            DP[i-1][w] : 
                            max(DP[i-1][w], DP[i-1][w-V[i]] + V[i]);
            }
        }
        
        return DP[N-1][W];
    }
    
    bool solution1(const std::vector<int>& V) {
        /*
        Time-Complexity:    O(S*N)
        Space-Complexity:   O(S*N)
        Where:
            N = size(nums)
            S = sum(nums)
        */
        /* EXPLANATION:
         * We are looking for the existence subsets `A` and `B` s.t.:
         *      UNION{A, B}         = V
         *      INTERSECTION{A, B}  = Ø
         *      SUM(A) = SUM(B)     = k
         * for some integer k.
         *
         * Assume that `A` and `B` exist.
         * Let
         *      S = SUM{V}
         * Then (since `A` and `B` are disjoint)
         *      S = SUM{V} = SUM{UNION{A,B}} = SUM{A} + SUM{B} = k + k = 2*k
         * So
         *      S = 2*k
         * Which implies that `S` must be of even parity.      
         * Therefore, in order for `A` and `B` to exist, our first condition must be
         *      `S` is of even parity (i.e., S % 2 == 0)
         *
         * Furthemore, we see that
         *      k = S/2
         * So our second condition must that we can find a subset `C` of `V` s.t.:
         *      SUM{C} = S/2
         * I.e., does their exist a subset of `V` that sums up to `S/2`?
         * We can leverage `0/1 Knapsack Problem` with `W = S/2` and see if such a subset exists by ensuring that its return value is `S/2`.
         * 
         * In conclusion, the required conditions are:
         *      1) S is of even parity
         *      2) There exists a subset `C` of `V` s.t.:
         *              SUM{C} = S/2 
         * */
        int S = sum(V);
        return (S & 1) ? false :
                (ZeroOneKS(V, S/2) == (S/2));
    }
    
    bool solution2(std::vector<int>& V) {
        /* EXPLANATION:
         * Make sure to read explanation in solution1.
         * First we ensure that `S` is of even parity.
         * Then, we will search for existence of subset of `V` that sums to `S/2` without leveraging KNAPSACK.
         * Instead we will first sort `V`.
         * Then, we will look for `S/2` by utilizing `helper()`.
         * Notice how it returns false as soon as `S < V[i]`.
         * */
        int S = sum(nums);
        if (S & 1) {
            return false;
        }
        std::sort(V.rbegin(), V.rend());
        return helper(V, S/2, 0);
    }
    
public:
    bool canPartition(vector<int>& nums) {
        return solution2(nums);
    }
};
