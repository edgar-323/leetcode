/*
Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.

Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
For example, two is written as II in Roman numeral, just two one's added together. Twelve is written as, XII, which is simply X + II. The number twenty seven is written as XXVII, which is XX + V + II.

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not IIII. Instead, the number four is written as IV. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as IX. There are six instances where subtraction is used:

I can be placed before V (5) and X (10) to make 4 and 9. 
X can be placed before L (50) and C (100) to make 40 and 90. 
C can be placed before D (500) and M (1000) to make 400 and 900.
Given a roman numeral, convert it to an integer. Input is guaranteed to be within the range from 1 to 3999.

Example 1:

Input: "III"
Output: 3
Example 2:

Input: "IV"
Output: 4
Example 3:

Input: "IX"
Output: 9
Example 4:

Input: "LVIII"
Output: 58
Explanation: L = 50, V= 5, III = 3.
Example 5:

Input: "MCMXCIV"
Output: 1994
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.

*/

class Solution {
private:
    const size_t I = 1;
    const size_t V = 5;
    const size_t X = 10;
    const size_t L = 50;
    const size_t C = 100;
    const size_t D = 500;
    const size_t M = 1000;


    int solution1(std::string& s) {
        int sum = 0;
        const size_t N = s.size();
        int i = int(N)-1;

        while (i > -1) {
            if (s[i] == 'I') {
                while (i > -1 and s[i] == 'I') {
                    sum += I;
                    --i;
                }
                ++i;
            } else if (s[i] == 'V') {
                sum += V;
                if (i > 0 and s[i-1] == 'I') {
                    sum -= I;
                    --i;
                }
            } else if (s[i] == 'X') {
                sum += X;
                if (i > 0 and s[i-1] == 'I') {
                    sum -= I;
                    --i;
                }
            } else if (s[i] == 'L') {
                sum += L;
                if (i > 0 and s[i-1] == 'X') {
                    sum -= X;
                    --i;
                }
            } else if (s[i] == 'C') {
                sum += C;
                if (i > 0 and s[i-1] == 'X') {
                    sum -= X;
                    --i;
                }
            } else if (s[i] == 'D') {
                sum += D;
                if (i > 0 and s[i-1] == 'C') {
                    sum -= C;
                    --i;
                }
            } else if (s[i] == 'M') {
                sum += M;
                if (i > 0 and s[i-1] == 'C') {
                    sum -= C;
                    --i;
                }
            } else {
                return -1;
            }
            --i;
        }
        
        return sum;
    }

public:
    int romanToInt(string s) {
        return solution1(s);       
    }
};
