/*
 Given an integer, write a function to determine if it is a power of three.

Example 1:
Input: 27
Output: true

Example 2:
Input: 0
Output: false

Example 3:
Input: 9
Output: true

Example 4:
Input: 45
Output: false

Follow up:
Could you do it without using any loop / recursion?
*/

class Solution {
private:
    bool solution1(int N) {
        /*
         * Time-Complexity:     O( log( N ) )
         * Space-Complexity:    O(    1     )
         * */
        for (; N; N /= 3) {
            if ( N % 3 != 0 ) {
                return false;
            }
        }

        return true;
    }
    bool solution2(int N) {
        // convert to base 3 and check
    }
    bool solution3(int N) {
        return (std::log10( N ) / log10( 3 )) % 1 == 0;
    }
    bool solution4(int N) {
        return 1162261467 % N == 0;
    }
public:
    bool isPowerOfThree(int n) {
        return N and solution( std::abs( n  ));
    }
};
