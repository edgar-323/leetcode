/*
Given a non-negative integer n, count all numbers with unique digits, x, where 0 ≤ x < 10^n

Example:
Input: 2
Output: 91 
Explanation: The answer should be the total numbers in the range of 0 ≤ x < 100, 
             excluding 11,22,33,44,55,66,77,88,99
*/

class Solution {
private:
    bool has_unique_digits(unsigned long long x) {
        int digits = 0;
        for (; x; x /=10) {
            const int digit = x%10;
            if (digits & (1 << digit)) {
                return false;
            }
            digits = digits | (1 << digit);
        }
        return true;
    }
	int solution1(const int N) {
        /* Time-Complexity:     O(10^N)
         * Space-Complexity:    O(  1 )
         * */
        // BRUTE-FORCE 
        int ans = 0;
        
        const unsigned long long M = (unsigned long long) pow(10.0, N);
        for (unsigned long long x = 0; x < M; ++x) {
            if (has_unique_digits(x)) {
                ++ans;
            }
        }

        return ans;
	}
    
    int solution2(int N) {
        /* Time-Complexity:     O()
         * Space-Complexity:    O()
         */
        // Explanation:
        // This will be a slightly mathematically inclined solution.
        // We know that the objective is to find all integers x € [0, 10^N)
        // such that all digits d € x are unique.
        // Let S = [0, 10^N) be the interval of interest.
        // Notice that we can divide S into partions Sk such that
        // all numbers in partion Sk have exactly k digits.
        // I.e.,
        //  S = [0, 10^N) = [0, 10^1) U [10^1,10^2) U ... U [10^N-1,10^N)
        // Then, if we let F(k) be number of integers that are represented 
        // by exactly k digits, we see that:
        //  F(k) = (10 - 1) * (10 - 1) * (10 - 2) * (10 - 3) * ... * (10 - #digits_left)
        // Reasoing for above formula is:
        //  For any integer x of exectly k unique digits, read from left to right, 
        //  for digit 1 we have 9 possible digits to choose from (digits 1 through 9), 
        //  then for digit1 we have 9 possible to choose from (digits 0 through 9, 
        //  exlcuding the digit chosen for digit0), and also for digit2 we have 8 possible
        //  choices (digits 1 through 9 excluding digits chosen for digit0 and digit1),
        //  and so on...
        // Notice that this formula, tells us that any number x >= 10^10 will have a 
        // repeating digit with probability 1, due to pigeon hole principle (i.e., we have
        // 11 position and only 10 digits to assign each position.).
        // Ultimately, the answer we seek is:
        //  ∑ { F(k) | k € [0, N) }
       
        N = std::min(N, 10);
        auto F = std::vector<int>(N+1, 0);
        F[1] = 10; // Initial value (1 digit, we have 10 possible choices, all unique).
        for (int k = 2; k <= N; ++k) {
            F[k] = 9;
            for (int i = 8, j = 0; j < k-1; ++j, --i) {
                F[k] *= i;
            }
        }
        return std::accumulate(F.begin(), F.end(), 0);
    }
public:
    int countNumbersWithUniqueDigits(int n) {
		return solution2(n);
    }
};
