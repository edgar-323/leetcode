/*
Implement int sqrt(int x).

Compute and return the square root of x, where x is guaranteed to be a non-negative integer.

Since the return type is an integer, the decimal digits are truncated and only the integer part of the result is returned.

Example 1:

Input: 4
Output: 2
Example 2:

Input: 8
Output: 2
Explanation: The square root of 8 is 2.82842..., and since 
             the decimal part is truncated, 2 is returned.
*/

class Solution {
private:
    int cmp(long long _y, long long _x) {
        double y = double(_y);
        double x = double(_x);
        if (y > x/y) {
            // y is too big
            return 1;
        } else if ( (y + 1.0) <= (x / (y+1.0))) {
            // y is too small
            return -1;
        } else {
            return 0;
        }
        
    }

    int solution1(long long x) {
        /*
         * Time-Complexity:     O( lg( x ) )
         * Space-Complexity:    O(    1    )
         * */

        /* We to find an integer y s.t 
         *  y^2 <= x AND (y+1)^2 > x
         * This implies:
         *  y <= x/y AND (y+1) > x/(y+1)
         * */
        if (x <= 1) {
            return x;
        }
        long long l = 1;
        long long r = x;
        
        while (l <= r) {
            long long y = (l + r) / 2;
            int c = cmp( y, x );
            if (c == 0) {
                return y;
            } else if (c < 0) {
                l = (l == r) ? l+1 : y; 
            } else {
                r = (r == l) ? r-1 : y;
            }
        }

        return -1;
    }
public:
    int mySqrt(int x) {
        return solution1( x ); 
    }
};


