/*
Given a positive integer n, break it into the sum of at least two positive integers and maximize the product of those integers. 
Return the maximum product you can get.

Example 1:
Input: 2
Output: 1
Explanation: 2 = 1 + 1, 1 × 1 = 1.

Example 2:
Input: 10
Output: 36
Explanation: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36.

Note: 
You may assume that n is not less than 2 and not larger than 58.
*/


class Solution {
private:
	int solution1(const int N) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(1)
         * */
        // NOTE:
        // This problem was percieved as "tricky" by my mind.
        // I was going to try to optimize the brute-force solution which
        // involved producing all partitions of N and taking the one
        // with the biggest produce but it seemed difficult to improve.
        // In fact, the solution hinted at the existence of an O(N)
        // solution, so I instead focused on understanding that solution
        // and at how one could come up with such a concept.
        // 
        // The idea behind it is as follows:
        // For now, suppose N is "sufficiently" large and that we can
        // partition N into real numbers (not simply discrete).
        // Perhaps there exists one real number that gives the optimal
        // solution, call this number `x` and assume that N is a multiple
        // of x so that we can parition N into a sum of x's.
        // In other words, we will have (N/x) number of x's.
        // So this will yield a product of x^(N/x).
        // Let f(x) = x^(N/x).
        // It is obvious that we want the x that yields the larget value
        // of f(x).
        // So we maximize f(x) by taking its derivative and finding its
        // peak values:
        // D(f(x)) = N * x^(N/x-2) * (1 - ln(x))
        // By analyzing this derivative, we see that it is positive
        // when 0 < x < e, equal to 0 when x = e, and negative when
        // e < x <= N.
        // This reveals that f(x) reaches a maximum when x = e.
        // Now, by shifting our focus back to the discrete case, it becomes
        // aparent that we want to partition N into integers that are as
        // close as possible to the number e; namely, the number 3.
        //
        // In additon to the above discussion, consider this other viewpoint:
        // if the optimal product contains any factor m >= 4, then you can replace
        // f with 2 and (m-2) since 2 * (m - 2) >= m, and so you never require
        // a factor greater or equal to 4.
        // Meaning you only need the values {1,2,3}, however, the value 1 is useless
        // since x * 1 = x (no improvement).
        
        if (N == 2) {
            return 1;
        } else if (N == 3) {
            return 2;
        }

        int prod = 1;
        
        while (N > 4) {
            prod *= 3;
            N -= 3;
        }

        prod *= N;

        return prod;
	}
public:
    int integerBreak(int n) {
     	return solution1(n);
    }
};
