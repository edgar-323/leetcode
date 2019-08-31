/*
Implement pow(x, n), which calculates x raised to the power n (x^n).

Example 1:

Input: 2.00000, 10
Output: 1024.00000
Example 2:

Input: 2.10000, 3
Output: 9.26100
Example 3:

Input: 2.00000, -2
Output: 0.25000
Explanation: 2-2 = 1/22 = 1/4 = 0.25
Note:

-100.0 < x < 100.0
n is a 32-bit signed integer, within the range [−2^31, 2^31 − 1]
*/

class Solution {
private:
    double helper3(double x, size_t n) {
        /*
         * Time-Complexity:     O( lg( n ) )
         * Space: Complexity:   O(    1    )
         * */
        double pow = 1.0;
        while ( n ) {
            if ( n&1 ) {
                pow *= x;
            }

            n = n >> 1;
            x *= x;
        }

        return pow;
    }

    double helper2(double x, size_t n) {
        /*
         * Time-Complexity:     O( lg( n ) )
         * Space-Complexity:    O( lg( n ) )
         * */
        if ( !n ) {
            return 1.0;
        }
        double pow = helper2( x, n/2 );
        return ( n&1 ) ? 
                pow * pow * x : 
                pow * pow; 
    }

    double helper1(double x, size_t n) {
        /*
         * Time-Complexity:     O( n )
         * Space-Complexity:    O( 1 )
         * */
        double pow = 1.0;
        while ( n ) {
            pow *= x;
            --n;
        } 
        return pow;
    }
public:
    double myPow(double x, int n) {
        double pow = helper3( x, std::abs( (long long) n ) );
        return (n < 0) ? (1.0 / pow) : pow;
    }
};
