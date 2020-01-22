/*
Given a positive integer n, find the number of non-negative integers less than or equal to n, whose binary representations do NOT contain consecutive ones.

Example 1:
Input: 5
Output: 5
Explanation: 
Here are the non-negative integers <= 5 with their corresponding binary representations:
0 : 0
1 : 1
2 : 10
3 : 11
4 : 100
5 : 101
Among them, only integer 3 disobeys the rule (two consecutive ones) and the other 5 satisfy the rule. 

Note: 1 <= n <= 109
*/

class Solution {
private:
	int solution1(const int N) {
        auto DP = std::vector<int>(32);
        DP[0] = 1;
        DP[1] = 2;
        for (int i = 2; i < 32; ++i) {
            DP[i] = DP[i-1] + DP[i-2];
        }
        int ansr = 0;
        for (int i = 30, prev_bit = 0; i >= 0; --i) {
            if (N & (1 << i)) {
                ansr += DP[i];
                if (prev_bit == 1) {
                    --ansr;
                    break;
                }
                prev_bit = 1;
            } else {
                prev_bit = 0;
            }
        }
        
        return ansr + 1;
	}    
public:
    int findIntegers(int num) {
     	return solution1(num);   
    }
};
