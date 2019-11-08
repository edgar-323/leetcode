/*
We partition a row of numbers A into at most K adjacent (non-empty) groups, then our score is the sum of the average of each group. 
What is the largest score we can achieve?
Note that our partition must use every number in A, and that scores are not necessarily integers.

Example:
Input: 
A = [9,1,2,3,9]
K = 3
Output: 20
Explanation: 
The best choice is to partition A into [9], [1, 2, 3], [9]. The answer is 9 + (1 + 2 + 3) / 3 + 9 = 20.
We could have also partitioned A into [9, 1], [2], [3, 9], for example.
That partition would lead to a score of 5 + 2 + 6 = 13, which is worse.

Note:
1 <= A.length <= 100.
1 <= A[i] <= 10000.
1 <= K <= A.length.
Answers within 10^-6 of the correct answer will be accepted as correct.
*/

class Solution {
private:
    /************************************************************************************************/
    int N;
    int* running_sum;
    void init_running_sum(const std::vector<int>& A) {
        running_sum = new int[N];
        running_sum[0] = A[0];
        for (int i = 1; i < N; ++i) {
            running_sum[i] = running_sum[i-1] + A[i];
        }
    }
    void destroy_runnning_sum() {
        delete[] running_sum;
    }
    double average(const int i, const int j) {
        return double(running_sum[j-1] - (i ? running_sum[i-1] : 0)) / double(j-i);
    }
    /************************************************************************************************/
    double*** cache1;
    bool*** in_cache1;
    void init_cache1(const int K) {
        cache1 = new double**[N+1];
        in_cache1 = new bool**[N+1];

        for (int i = 0; i <= N; ++i) {
            cache1[i] = new double*[N+1];
            in_cache1[i] = new bool*[N+1];

            for (int j = 0; j <= N; ++j) {
                cache1[i][j] = new double[K+1];
                in_cache1[i][j] = new bool[K+1];

                for (int k = 0; k <= K; ++k) {
                    in_cache1[i][j][k] = false;
                }
            }
        }
    }
    void destroy_cache1() { 
        for (int i = 0; i <= N; ++i) {
            for (int j = 0; j <= N; ++j) {
                delete[] cache1[i][j];
                delete[] in_cache1[i][j];
            }
            delete[] cache1[i];
            delete[] in_cache1[i];
        }
        delete[] cache1;
        delete[] in_cache1;
    }
    double set_cache1(const int i, const int j, const int k, const double val) {
        in_cache1[i][j][k] = true;
        return cache1[i][j][k] = val;
    }

    double recurse1(const int begin, const int end, const int K) {
        if (in_cache1[begin][end][K]) {
            return cache1[begin][end][K];
        }
        double score = average(begin, end);
        if (K == 1 or end - begin == 1) {
            return set_cache1(begin, end, K, score);
        }
        for (int i = begin+1; i < end; ++i) {
            for (int k = 1; k < K; ++k) {
                score = std::max(score, recurse1(begin, i, k) + recurse1(i, end, K-k));
            }
        }
         
        return set_cache1(begin, end, K, score);
    }
	double solution1(const std::vector<int>& A, const int K) {
        /* Time-Complexity:     O(N^3 * K^2 )
         * Space-Complexity:    O(N^2 * K   )
         */ 
        // MY SOLUTION
        // TIME-LIMIT-EXCEEDED
        N = A.size();
        if (not N) {
            return 0.00;
        }
        init_running_sum(A);
        init_cache1(K);
        const double max_avg_sum = recurse1(0, N, K);
        destroy_cache1();
        destroy_runnning_sum();

        return max_avg_sum; 
	}
    /************************************************************************************************/
    double** cache2;
    bool** in_cache2;
    void init_cache2(const int K) {
        cache2 = new double*[N+1];
        in_cache2 = new bool*[N+1];
        for (int i = 0; i <= N; ++i) {
            cache2[i] = new double[K+1];
            in_cache2[i] = new bool[K+1];    
            for (int k = 0; k <= K; ++k) {
                in_cache2[i][k] = false;
            }
        }   
    }
    void destroy_cache2() {
        for (int i = 0; i <= N; ++i) {
            delete[] cache2[i];
            delete[] in_cache2[i];
        }
        delete[] cache2;
        delete[] in_cache2;
    }
    double set_cache2(const int i, const int K, const double val) {
        in_cache2[i][K] = true;
        return cache2[i][K] = val;
    }
    double recurse2(const int i, const int K) {
        if (in_cache2[i][K]) {
           return cache2[i][K];
        }
        double score = average(i, N);
        if (K == 1 or i == N-1) {
            return set_cache2(i, K, score);
        }
        for (int j = i+1; j < N; ++j) {
            score = std::max(score, average(i, j) + recurse2(j, K-1));
        }

        return set_cache2(i, K, score);
    }
    double solution2(const std::vector<int>& A, const int K) {
        /* Time-Complexity:     O(N^2 * K)
         * Space-Complexity:    O(N * K  )
         */
        // TOOK CONCPET FROM OFFICIAL LEETCODE SOLUTION
        N = A.size();
        if (not N) {
           return 0.000;
        }
        init_running_sum(A);
        init_cache2(K);
        const double max_avg_sum = recurse2(0, K);
        destroy_cache2();
        destroy_runnning_sum();     

        return max_avg_sum;
    }
    /************************************************************************************************/
public:
    double largestSumOfAverages(std::vector<int>& A, int K) {
  		return solution2(A, K);      
    }
};
