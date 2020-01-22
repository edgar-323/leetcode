/*
You are given K eggs, and you have access to a building with N floors from 1 to N. 
Each egg is identical in function, and if an egg breaks, you cannot drop it again.
You know that there exists a floor F with 0 <= F <= N such that any egg dropped at a floor higher than F will break, and any egg dropped at or below floor F will not break.
Each move, you may take an egg (if you have an unbroken one) and drop it from any floor X (with 1 <= X <= N). 
Your goal is to know with certainty what the value of F is.
What is the minimum number of moves that you need to know with certainty what F is, regardless of the initial value of F?

Example 1:
Input: K = 1, N = 2
Output: 2
Explanation: 
Drop the egg from floor 1.  If it breaks, we know with certainty that F = 0.
Otherwise, drop the egg from floor 2.  If it breaks, we know with certainty that F = 1.
If it didn't break, then we know with certainty F = 2.
Hence, we needed 2 moves in the worst case to know what F is with certainty.

Example 2:
Input: K = 2, N = 6
Output: 3

Example 3:
Input: K = 3, N = 14
Output: 4 

Note:
1 <= K <= 100
1 <= N <= 10000
*/

class Solution {
private:
    /************************************************************************************************************/
    int** cache1;
    void init_cache1(const int K, const int N) {
        cache1 = new int*[K+1];
        for (int k = 0; k <= K; ++k) {
            cache1[k] = new int[N+1];
            for (int n = 0; n <= N; ++n) {
                cache1[k][n] = -1;
            }
        }
    }
    void destroy_cache1(const int K) {
        for (int k = 0; k <= K; ++k) {
            delete[] cache1[k];
        }
        delete[] cache1;
    }
    bool in_cache1(const int K, const int N) {
        return cache1[K][N] >= 0;
    }
    int get_cache1(const int K, const int N) {
        return cache1[K][N];
    }
    int set_cache1(const int K, const int N, const int val) {
        return cache1[K][N] = val;
    }
    int recurse1(const int K, const int N) {
        if (in_cache1(K, N)) {
            return get_cache1(K, N);
        }
        int min_moves;
        if (N == 0) {
            min_moves = 0;
        } else if (K == 1) {
            min_moves = N;
        } else {
            int left = 1;
            int right = N;
            
            while (left < right-1) {
                const int x = (left + right) / 2;
                const int t1 = recurse1(K - 1, x - 1);
                const int t2 = recurse1(K, N - x);
                
                if (t1 < t2) {
                    left = x;
                } else if (t1 > t2) {
                    right = x;
                } else {
                    left = right = x;
                }
            }
            min_moves = 1 + std::min(
                                std::max(recurse1(K - 1, left - 1), recurse1(K, N - left)),
                                std::max(recurse1(K - 1, right - 1), recurse1(K, N - right)));
        }

        return set_cache1(K, N, min_moves);
    }
	int solution1(const int K, const int N) {
        /* Time-Complexity:     O(K * N * log(N))
         * Space-Complexity:    O(K * N)
         * */

        init_cache1(K, N);
        const int min_moves = recurse1(K, N);
        destroy_cache1(K);
        return min_moves;
	}
    /************************************************************************************************************/
public:
    int superEggDrop(int K, int N) {
  		return solution1(K, N);      
    }
};
