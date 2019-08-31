/*
Given a 32-bit signed integer, reverse digits of an integer.

Example 1:
Input: 123
Output: 321

Example 2:
Input: -123
Output: -321

Example 3:
Input: 120
Output: 21

Note:
Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−231,  231 − 1]. For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.
*/

class Solution {
private: 
    int solution1(int x) {
        /*
        Time-Complexity:    O(log10(x))
        Space-Complexity:   O(1)
        */
        if (x == INT_MIN) {
            return 0;
        }
        bool neg = false;
        if (x < 0) {
            x *= -1;
            neg = true;
        }
        long y = 0;
        for (; x > 0; y *= 10, y += (x % 10), x /= 10);
        y = neg ? -y : y;
        return (y < INT_MIN || y > INT_MAX) ? 0 : (int) y;
    }
    
public:    
    int reverse(int x) {
        return solution1(x);
    }
};
