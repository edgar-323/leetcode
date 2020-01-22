/*
Given a string S of digits, such as S = "123456579", we can split it into a Fibonacci-like sequence [123, 456, 579].
Formally, a Fibonacci-like sequence is a list F of non-negative integers such that:

0 <= F[i] <= 2^31 - 1, (that is, each integer fits a 32-bit signed integer type);
F.length >= 3;
and F[i] + F[i+1] = F[i+2] for all 0 <= i < F.length - 2.
Also, note that when splitting the string into pieces, each piece must not have extra leading zeroes, except if the piece is the number 0 itself.
Return any Fibonacci-like sequence split from S, or return [] if it cannot be done.

Example 1:
Input: "123456579"
Output: [123,456,579]

Example 2:
Input: "11235813"
Output: [1,1,2,3,5,8,13]

Example 3:
Input: "112358130"
Output: []
Explanation: The task is impossible.

Example 4:
Input: "0123"
Output: []
Explanation: Leading zeroes are not allowed, so "01", "2", "3" is not valid.

Example 5:
Input: "1101111"
Output: [110, 1, 111]
Explanation: The output [11, 0, 11, 11] would also be accepted.

Note:
1 <= S.length <= 200
S contains only digits.
*/
class Solution {
private:
    typedef long long LL;
    int N;

    bool recurse1(const int i, const LL num1, const LL num2, const std::string& S, std::vector<int>& F) {
        // Pick Third Number
        if (i == N) {
            return F.size() > 2;
        } else if (S[i] == '0') {
            return false;
        }
        for (int j = i; j < N; ++j) {
            const LL num3 = std::stoll(S.substr(i, j - i + 1));
            if (num3 > INT_MAX) {
                break;
            }
            if (num1 + num2 == num3) {
                F.push_back(num3);
                if (recurse1(j+1, num2, num3, S, F)) {
                    return true;
                }
                F.pop_back();
            }
        }
        return false;
    }

    void helper1(const std::string& S, std::vector<int>& F) {
        // Picks First Two Numbers  
        if (S.size() < 3) {
            return;
        }
        if (S[0] == '0' and S[1] == '0') {
            for (int i = 2; i < N; ++i) {
                if (S[i] != '0') {
                    return;
                }
            }
            F = std::vector<int>(N, 0);
            return;
        } else if (S[0] == '0') {
            F.push_back(0);
            for (int j = 1; j < N; ++j) {
                const LL num2 = std::stoll(S.substr(1, j));
                if (num2 > INT_MAX) {
                    break;
                }
                F.push_back(num2);
                if (recurse1(j+1, 0, num2, S, F)) {
                    return;
                }
                F.pop_back();
            }
            F.pop_back();
            return;
        }
        for (int i = 0; i < N; ++i) {
            const LL num1 = std::stoll(S.substr(0, i+1));
            if (num1 > INT_MAX) {
               break;
            }
            F.push_back(num1);
            for (int j = i+1; j < N; ++j) {
                const LL num2 =     S[i+1] == '0' ?
                                    0 :
                                    std::stoll(S.substr(i+1, j - (i+1) + 1));
                if (num2 > INT_MAX) {
                    break;
                }
				F.push_back(num2);
				if (recurse1(j+1, num1, num2, S, F)) {
					return;
				}
				F.pop_back();
            }
            F.pop_back(); 
        }
    }

    std::vector<int> solution1(std::string& S) {
        N = S.size();
        auto F = std::vector<int>();
        helper1(S, F);

        return F;   
    }
public:
    vector<int> splitIntoFibonacci(string S) {
        return solution1(S);       
    }
};
