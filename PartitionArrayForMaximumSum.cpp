/*
Given an integer array A, you partition the array into (contiguous) subarrays of length at most K.  
After partitioning, each subarray has their values changed to become the maximum value of that subarray.
Return the largest sum of the given array after partitioning.

Example 1:
Input: A = [1,15,7,9,2,5,10], K = 3
Output: 84
Explanation: A becomes [15,15,15,9,10,10,10]
 
Note:
1 <= K <= A.length <= 500
0 <= A[i] <= 10^6
*/
class Solution {
private:
    int* cache1;
    int N;
    int K;
    void init_cache1() {
        cache1 = new int[N+1];
        for (int i = 0; i <= N; ++i) {
            cache1[i] = -1;
        }
    }
    void destroy_cache1() {
        delete[] cache1;
    }
    int recurse1(const int i, const std::vector<int>& A) {
        if (cache1[i] >= 0) {
            return cache1[i];
        }
        int max_sum = 0;
        if (i < N) {
            const int M = std::min(i+K, N); 
            int max_elem = A[i]; 
            for (int j = i+1; j <= M; ++j) {
                max_elem = std::max(max_elem, A[j-1]);
                max_sum = std::max(max_sum, max_elem * (j - i) + recurse1(j, A));
            }
        }

        return cache1[i] = max_sum;
    }
    int solution1(const std::vector<int>& A, const int K) {
        this->N = A.size();
        this->K = K;

        init_cache1();
        const int max_sum = recurse1(0, A);
        destroy_cache1();

        return max_sum;
    }
public:
    int maxSumAfterPartitioning(vector<int>& A, int K) {
        return solution1(A, K);        
    }
};
