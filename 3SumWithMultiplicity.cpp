/*
Given an integer array A, and an integer target, return the number of tuples i, j, k  such that i < j < k and A[i] + A[j] + A[k] == target.
As the answer can be very large, return it modulo 10^9 + 7.

Example 1:
Input: A = [1,1,2,2,3,3,4,4,5,5], target = 8
Output: 20
Explanation: 
Enumerating by the values (A[i], A[j], A[k]):
(1, 2, 5) occurs 8 times;
(1, 3, 4) occurs 8 times;
(2, 2, 4) occurs 2 times;
(2, 3, 3) occurs 2 times.

Example 2:
Input: A = [1,1,2,2,2,2], target = 5
Output: 12
Explanation: 
A[i] = 1, A[j] = A[k] = 2 occurs 12 times:
We choose one 1 from [1,1] in 2 ways,
and two 2s from [2,2,2,2] in 6 ways.

Note:
3 <= A.length <= 3000
0 <= A[i] <= 100
0 <= target <= 300
*/
class Solution {
private:
    static const int MOD_VAL = 1e9 + 7;
    static const int MAX_VAL = 100;

    int solution1(std::vector<int>& A, const int target) {
        /* Time-Complexity:     O(N^2)
         * Space-Complexity:    O(1)
         */
        const int N = A.size();
        std::sort(A.begin(), A.end());
        int tuples = 0;
        for (int i = 0; i < N; ++i) {
            int j = i+1;
            int k = N-1;
            while (j < k) {
                const auto sum = A[i] + A[j] + A[k];
                if (sum < target) { 
                    ++j;
                } else if (sum > target) {
                    --k;
                } else if (A[j] != A[k]) {
                    int left = 1;
                    int right = 1;
                    while (j+1 < k and A[j] == A[j+1]) {
                        ++left;
                        ++j;
                    }
                    while (k-1 > j and A[k-1] == A[k]) {
                        ++right;
                        --k;
                    }
                    tuples = (tuples + left*right) % MOD_VAL;
                    ++j;
                    --k;
                } else {
                    const int M = k - j;
                    const int val = M & 1 ? M * ((M+1)/2) : (M/2) * (M+1);
                    tuples = (tuples + val) % MOD_VAL;
                    j = k;
                }
            }
        }
        return tuples;
    }
public:
    int threeSumMulti(vector<int>& A, int target) {
        return solution1(A, target);       
    }
};
