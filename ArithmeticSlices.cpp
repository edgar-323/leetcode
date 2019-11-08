/*
A sequence of number is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.

For example, these are arithmetic sequence:

1, 3, 5, 7, 9
7, 7, 7, 7
3, -1, -5, -9
The following sequence is not arithmetic.

1, 1, 2, 5, 7

A zero-indexed array A consisting of N numbers is given. A slice of that array is any pair of integers (P, Q) such that 0 <= P < Q < N.

A slice (P, Q) of array A is called arithmetic if the sequence:
A[P], A[p + 1], ..., A[Q - 1], A[Q] is arithmetic. In particular, this means that P + 1 < Q.

The function should return the number of arithmetic slices in the array A.


Example:

A = [1, 2, 3, 4]

return: 3, for 3 arithmetic slices in A: [1, 2, 3], [2, 3, 4] and [1, 2, 3, 4] itself.
*/

class Solution {
private:
    bool is_arithmetic_sqn1(const std::vector<int>& A, const int N, int& end) { 
        // Assumes end <= N-3
        if (A[end] - A[end+1] != A[end+1] - A[end+2]) {
            return false;
        }
        while (end < N-2 and A[end] - A[end+1] == A[end+1] - A[end+2]) {
            ++end;
        }
        ++end;
        return true;
    }
    int compute_k_value2(int k) {
        // Assumes k >= 3
        k -= 2;
        return (k * (k+1)) / 2;
    }
    int solution1(const std::vector<int>& A) {
        /* Time-Complexity:     O( N )
         * Space-Complexity:    O( 1 )
         * */
        int results = 0;
        const int N = A.size();
        for (int i = 0; i < N-2;) {
            int end = i;
            if (is_arithmetic_sqn1( A, N, end )) {
                results += compute_k_value2( end-i + 1 );
                i = end;
            } else {
                ++i;
            }
        }

        return results;
    }
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        return solution1( A ); 
    }
};
