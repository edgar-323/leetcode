/*
You are given a list of non-negative integers, a1, a2, ..., an, and a target, S. Now you have 2 symbols + and -. 
For each integer, you should choose one from + and - as its new symbol.
Find out how many ways to assign symbols to make sum of integers equal to target S.

Example 1:
Input: nums is [1, 1, 1, 1, 1], S is 3. 
Output: 5
Explanation: 
-1+1+1+1+1 = 3
+1-1+1+1+1 = 3
+1+1-1+1+1 = 3
+1+1+1-1+1 = 3
+1+1+1+1-1 = 3
There are 5 ways to assign symbols to make the sum of nums be target 3.
Note:

The length of the given array is positive and will not exceed 20.
The sum of elements in the given array will not exceed 1000.
Your output answer is guaranteed to be fitted in a 32-bit integer.
*/

class Solution {
private:
    /***********************************************************************/
    int N;
    int S;
    int recurse(const std::vector<int>& nums, const int pos, const int sumSoFar) {
        if (pos >= N) {
            return ((sumSoFar == S) ? 1 : 0);
        }
        
        return recurse(nums, pos+1, sumSoFar - nums[pos]) + recurse(nums, pos+1, sumSoFar + nums[pos]);
    }
    int solution1(const std::vector<int>& nums, const int S) {
        /* 
         * Time-Complexity:     O( 2^N )
         * Space-Complexity:    O(  N  )
         * */
        /* Explanation:
         * BRUTE-FORCE (Check all possibilities until we encounter `S`)
         * */
        N = nums.size();
        this->S = S;
        return recurse(nums, 0, 0);
    }
    /***********************************************************************/
    std::unordered_map<int, std::unordered_map<int,int>> memo;
    int recurse2(const std::vector<int>& nums, const int pos, const int sumSoFar) {
        if (pos == N) {
            return sumSoFar == S ? 1 : 0;
        }
        if (memo.count(pos) and memo[pos].count(sumSoFar)) {
            return memo[pos][sumSoFar];
        }

        int ans = recurse2( nums, pos+1, sumSoFar - nums[pos] ) + recurse2( nums, pos+1, sumSoFar + nums[pos] );
        auto it = memo.find( pos );
        if (it == memo.end()) {
            memo.insert( std::make_pair( pos, std::unordered_map<int,int>() ) );
            it = memo.find( pos );
        }
        auto& map = it->second;
        map.insert( std::make_pair( sumSoFar, ans ) );

        return memo[pos][sumSoFar];
    }
    int solution2(const std::vector<int>& nums, const int S) {
        /* Time-Complexity:     O( N*S )
         * Space-Complexity:    O( N*S )
         * */
        // MEMOIZED VERSION OF SOLUTION1()
        N = nums.size();
        this->S = S;
        memo.clear();
        return recurse2( nums, 0, 0 );
    }
    /***********************************************************************/
    int solution3(const std::vector<int>& V, const int S) {
        /* Time-Complexity:     O( N*MAX_SUM )
         * Space-Complexity:    O( N*MAX_SUM )
         * */
        // DP VERSION OF SOLUTION1()*/
        /* EXPLANATION:
         * We follow the same procedure as in solution1, however in order to
         * account for negative values of `sumSoFar`, we always add `MAX_SUM`
         * to the current sum.
         * I.e, `MAX_SUM` maps to 0.
         * */ 

        const int MAX_SUM = std::accumulate( V.begin(), V.end(), 0 );
        const int W = 2*MAX_SUM + 1;
        const int N = V.size();
        
        if (S > MAX_SUM) {
            return 0;
        } 

        std::vector<std::vector<int>> DP( N+1, std::vector<int>( W, 0 ) );
        
        DP[0][MAX_SUM] = 1;
        for (int i = 1; i <= N; ++i) {
            for (int j = 0; j < W; ++j) {
                DP[i][j] += ((j+V[i-1]  < W  ? DP[i-1][j+V[i-1]] : 0) + 
                            ( j-V[i-1] >= 0  ? DP[i-1][j-V[i-1]] : 0));
            }
        }
        
        return DP[N][S+MAX_SUM];
    }
    /***********************************************************************/
    int subsetSums(const std::vector<int>& V, const int S) {
        /* Time-Complexity:     O( N * S )
         * Space-Complexity:    O(   S   )
         *  where N = size(V)
         * */
        // Assumes S >= 0.
        // Also assumes `v >= 0` for all `v € V`.
        /* EXPLANATION: 
         * 
         * */

        std::vector<int> DP( S+1, 0 );
        DP[0] = 1;

        for (const int& v : V) {
            for (int i = S; i >= v; --i) {
                DP[i] += DP[i - v];
            }
        }

        return DP[S];
    }
    int solution4(const std::vector<int>& V, const int S) {
        /* Explanation:
         * Notice that, for all `v € V`, we have `v >= 0`.
         * The problem is asking to find the # of ways we can partition `V`
         * into two sets `P` (positives) and `N` (negatives) s.t.:
         *      UNION{P,N}          = V
         *      INTERSECTION{P,N}   = Ø
         *      SUM{P} - SUM{N}     = S
         * We will see how, by transforming the above (third) equation, we can transform
         * the problem to a problem which we can solve via `SubsetSums`.
         *
         * We begin by letting:
         *      MAX_SUM = SUM{V}
         * Then, we restate the original equation and apply manipulations:
         *      SUM{P} - SUM{N} = S
         *      ==> SUM{P} - SUM{N} + SUM{V}            = S + SUM{V}
         *      ==> SUM{P} - SUM{N} + SUM{UNION{P,N}}   = S + MAX_SUM
         *      ==> SUM{P} - SUM{N} + SUM{P} + SUM{N}   = S + MAX_SUM
         *      ==> 2*SUM{P}                            = S + MAX_SUM
         *      ==> SUM{P}                              = (S + MAX_SUM)/2
         * So we see, that the problem is asking us to find the # of subsets
         * `P` of `V` s.t.:
         *      SUM{P} = (S+MAX_SUM)/2
         * First, we notice that one of the conditions for this to be true
         * is that `(S+MAX_SUM)` must be of even parity.
         * Second, we need to return the total number of sets `P` whose
         * sum is `(S+MAX_SUM)/2` which is the central problem to `SubsetSums()`.
         * So we return `SubsetSums( V, (S+MAX_SUM)/2 )`.
         * */ 
        
        const int MAX_SUM = std::accumulate( V.begin(), V.end(), 0 );
        return (MAX_SUM < S ||  (S+MAX_SUM) & 1) ? 0 : subsetSums( V, (S+MAX_SUM) >> 1 ); 
    }
    /***********************************************************************/ 
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        return solution2(nums, S);
    }
};
