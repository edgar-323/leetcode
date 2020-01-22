/*
Given an array A of positive integers, call a (contiguous, not necessarily distinct) subarray of A good if the number of different integers in that subarray is exactly K.
(For example, [1,2,3,1,2] has 3 different integers: 1, 2, and 3.)
Return the number of good subarrays of A.

Example 1:
Input: A = [1,2,1,2,3], K = 2
Output: 7
Explanation: Subarrays formed with exactly 2 different integers: [1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2].

Example 2:
Input: A = [1,2,1,3,4], K = 3
Output: 3
Explanation: Subarrays formed with exactly 3 different integers: [1,2,1,3], [2,1,3], [1,3,4].

Note:
1 <= A.length <= 20000
1 <= A[i] <= A.length
1 <= K <= A.length
*/
class Solution {
private:
    int at_most_k_distinct(const std::vector<int>& A, const int K) {
        const int N = A.size();
        auto count = std::vector<int>(N+1, 0);
        int i = 0;
        int results = 0;
        int distinct = 0;
        for (int j = 0; j < N; ++j) {
            if (not count[A[j]]++) {
                ++distinct;
            }
            while (distinct > K) {
                if (not --count[A[i++]]) {
                    --distinct;
                }
            }
            results += (j - i + 1);
        }
        return results;
    }

    int solution1(const std::vector<int>& A, const int K) {
        return at_most_k_distinct(A, K) - at_most_k_distinct(A, K-1);
    }
    
    int solution2(const std::vector<int>& A, const int K) {
        int results = 0;
        
        const int N = A.size();
        auto count = std::vector<int>(N+1, 0);
        int i = 0;
        int prefix = 0;
        int distinct = 0;
        for (int j = 0; j < N; ++j) {
            if (not count[A[j]]++) {
                ++distinct;
            }
            if (distinct > K) {
                --count[A[i++]];
                --distinct;
                prefix = 0;
            }
            while (count[A[i]] > 1) {
                --count[A[i++]];
                ++prefix;
            }
            if (distinct == K) {
                results += 1 + prefix;
            }
        }

        return results;
    }

public:
    int subarraysWithKDistinct(vector<int>& A, int K) {
        return solution2(A, K);        
    }
};

