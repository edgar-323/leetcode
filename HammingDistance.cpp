/*
The Hamming distance between two integers is the number of positions at which the corresponding bits are different.

Given two integers x and y, calculate the Hamming distance.

Note:
0 ≤ x, y < 231.

Example:

Input: x = 1, y = 4

Output: 2

Explanation:
1   (0 0 0 1)
4   (0 1 0 0)
       ↑   ↑

The above arrows point to positions where the corresponding bits are different.
*/

class Solution {
private: 
    int solution1(int x, int y) {
        int hamDist = 0;
        const int ONE = 1;
        for (int i = 0; i < 31; ++i) {
            if (((x >> i) & ONE) ^ ((y >> i) & ONE)) {
                ++hamDist;
            }
        }
        return hamDist;
    }
    
    int solution2(int x, int y) {
        int hamDist = 0;
        int z = x ^ y;
        const int ONE = 1;
        for (int i = 0; i < 31; ++i) {
            if ((z >> i) & ONE) {
                ++hamDist;
            }
        }
        return hamDist;
    }    
    
public:
    int hammingDistance(int x, int y) {
        return solution2(x, y);
    }
};
