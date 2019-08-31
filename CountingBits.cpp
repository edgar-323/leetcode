/*
Given a non-negative integer number num. 
For every numbers i in the range 0 ≤ i ≤ num calculate the number of 1's in their binary representation and return them as an array.

Example 1:
Input: 2
Output: [0,1,1]

Example 2:
Input: 5
Output: [0,1,1,2,1,2]

Follow up:
It is very easy to come up with a solution with run time O(n*sizeof(integer)). But can you do it in linear time O(n) /possibly in a single pass?
Space complexity should be O(n).
Can you do it like a boss? Do it without using any builtin function like __builtin_popcount in c++ or in any other language.
*/

class Solution {
private:
    bool isPowerOfTwo(int num) {
        return (__builtin_popcount(num) == 1);
    }
    
    int bitCount(int num) {
        int ones = 0;
        for (int i = 0; i < 31; ++i) {
            ones += ((num >> i) & 1) ? 1 : 0;
        }
        return ones;
    }
    
    std::vector<int> solution1(int N) {
        /*
        Time-Complexity:    O(N*m)
        Space-Complexity:   O(1)
            Where
                m = O(__builtin_popcount(i)) 
            is a very fast (machine) instruction
        */
        std::vector<int> bits;
        for (int i = 0; i <= N; ++i) {
            bits.push_back(__builtin_popcount(i));
        }
        return bits;
    }
    
    std::vector<int> solution2(int N) {
        /*
        Time-Complexity:    O(N*q)
        Space-Complexity:   O(1)
            Where
                q = max_integer_size 
        */
        std::vector<int> bits;
        for (int i = 0; i <= N; ++i) {
            bits.push_back(bitCount(i));
        }
        return bits;
    }
    
    std::vector<int> solution3(int N) {
        std::vector<int> bits(N+1, 0);
        bits[0] = 0;
        if (N == 0) {
            return bits;
        }
        bits[1] = 1;
        for (int i = 2, k = 0; i <= N; ++i, ++k) {
            if (isPowerOfTwo(i)) {
                k = 0;
            }
            bits[i] = 1 + bits[k];
        }
        return bits;
    }
    
    std::vector<int> solution4(int N) {
        /*
        Time-Complexity:    O(N)
        Space-Complexity:   O(1)
        
        This is a dynamic solution but we 
        use the output array as our space 
        since we have to return it anyways.
        It doesnt need to do any bit counting.
        */
        std::vector<int> bits(N+1, 0);
        bits[0] = 0;
        if (N == 0) {
            return bits;
        }
        bits[1] = 1;
        for (int i = 2, k = 0, lim = 4; i <= N; ++i, ++k) {
            if (i >= lim) {
                k = 0;
                lim *= 2;
            }
            bits[i] = 1 + bits[k];
        }
        return bits;
    }
    
public:
    vector<int> countBits(int num) {
        return solution4(num);
    }
};
