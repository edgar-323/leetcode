/*
There are N piles of stones arranged in a row.  
The i-th pile has stones[i] stones.
A move consists of merging exactly K consecutive piles into one pile, 
and the cost of this move is equal to the total number of stones in these K piles.
Find the minimum cost to merge all piles of stones into one pile.  
If it is impossible, return -1.

Example 1:
Input: stones = [3,2,4,1], K = 2
Output: 20
Explanation: 
We start with [3, 2, 4, 1].
We merge [3, 2] for a cost of 5, and we are left with [5, 4, 1].
We merge [4, 1] for a cost of 5, and we are left with [5, 5].
We merge [5, 5] for a cost of 10, and we are left with [10].
The total cost was 20, and this is the minimum possible.

Example 2:
Input: stones = [3,2,4,1], K = 3
Output: -1
Explanation: 
After any merge operation, there are 2 piles left, and we can't merge anymore.  
So the task is impossible.

Example 3:
Input: stones = [3,5,1,2,6], K = 3
Output: 25
Explanation: 
We start with [3, 5, 1, 2, 6].
We merge [5, 1, 2] for a cost of 8, and we are left with [3, 8, 6].
We merge [3, 8, 6] for a cost of 17, and we are left with [17].
The total cost was 25, and this is the minimum possible.

Note:
1 <= stones.length <= 30
2 <= K <= 30
1 <= stones[i] <= 100
*/
class Solution {
private:
    int K;

    int recurse1(const int i, const int j, const int piles, const std::vector<int>& prefix_sum, std::vector<std::vector<std::vector<int>>>& cache) {
        if (cache[i][j][piles] >= 0) {
            return cache[i][j][piles];
        }

        int min_cost;
        if (j - i + 1 < piles) {
            // Impossible to make `piles` out of less than `piles` elements
            min_cost = INT_MAX;
        } else if (i == j) {
            // Only one element so can only make exactly one pile.
            min_cost = piles == 1 ? 0 : INT_MAX; 
        } else if (piles == 1) {
            // Want to make one pile out of elements stones[i:j].
            // We know that We can merge K at a time.
            // So we first want to make stones[i:j] into exactly K piles.
            // Then we turn these K piles into one pile by adding sum(i, j) to the cost
            min_cost = recurse1(i, j, K, prefix_sum, cache);
            if (min_cost != INT_MAX) {
                min_cost += prefix_sum[j] - prefix_sum[i-1];
            }
        } else {
            // Want to make stones[i:j] into `piles` piles.
            // There will be some index k (i <= k < j) such that
            // stones[k+1:j] will be the LAST pile.
            // This means that our answer would be recurse1(i, k, piles-1) + recurse1(k+1, j, 1).
            // But we don't know which k gives the minimal value so we try all values of k.
            min_cost = INT_MAX;
            for (int k = i; k < j; ++k) {
                const auto left_cost = recurse1(i, k, piles - 1, prefix_sum, cache);
                if (left_cost == INT_MAX) {
                    continue;
                }
                const auto right_cost = recurse1(k+1, j, 1, prefix_sum, cache);
                if (right_cost == INT_MAX) {
                    continue;
                }
                min_cost = std::min(min_cost, left_cost + right_cost);
            }
        }

        return cache[i][j][piles] = min_cost;
    }

    int solution1(const std::vector<int>& stones, const int K) {
        this->K = K;
        const int N = stones.size();
        auto prefix_sum = std::vector<int>(N+1, 0);
        for (int i = 1; i <= N; ++i) {
            prefix_sum[i] = prefix_sum[i-1] + stones[i-1];
        }
        auto cache = std::vector<std::vector<std::vector<int>>>(N+1, std::vector<std::vector<int>>(N+1, std::vector<int>(K+1,-1)));
        const auto min_cost = recurse1(1, N, 1, prefix_sum, cache);
        return min_cost == INT_MAX ? -1 : min_cost;
    }
public:
    int mergeStones(vector<int>& stones, int K) {
        return solution1(stones, K);        
    }
};
