/*
Given integers n and k, find the lexicographically k-th smallest integer in the range from 1 to n.
Note: 1 ≤ k ≤ n ≤ 109.

Example:
Input:
n: 13   k: 2
Output:
10
Explanation:
The lexicographical order is [1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9], so the second smallest number is 10.
*/
class Solution {
private:
    int solution1(int N, int K) {
        /
        int curr = 1;
        --K;
        while (K) {
            const auto steps = calc_steps(N, curr, curr+1);
            if (K >= steps) {
                curr = curr + 1;
                K -= steps;
            } else {
                curr = curr * 10;
                --K;
            }
        }
        return curr;
    }

    int calc_steps(const long long N, long long a, long long b) {
        // This function returns total number of lexicographic
        // integers v s.t. every for all v -> int(v) <= N and v <= b
        // If we didnt have restriction v <= N then there would be infinite amount.
        // initially a == b+1
        int steps = 0;
        while (a <= N) {
            steps += std::min(N+1, b) - a;
            a *= 10;
            b *= 10;
        }
        return steps;
    }
public:
    int findKthNumber(int n, int k) {
        return solution1(n, k);       
    }
};
