/*
We can rotate digits by 180 degrees to form new digits. 
When 0, 1, 6, 8, 9 are rotated 180 degrees, they become 0, 1, 9, 8, 6 respectively. 
When 2, 3, 4, 5 and 7 are rotated 180 degrees, they become invalid.
A confusing number is a number that when rotated 180 degrees becomes a different number with each digit valid.
(Note that the rotated number can be greater than the original number.)
Given a positive integer N, return the number of confusing numbers between 1 and N inclusive.

Example 1:
Input: 20
Output: 6
Explanation: 
The confusing numbers are [6,9,10,16,18,19].
6 converts to 9.
9 converts to 6.
10 converts to 01 which is just 1.
16 converts to 91.
18 converts to 81.
19 converts to 61.

Example 2:
Input: 100
Output: 19
Explanation: 
The confusing numbers are [6,9,10,16,18,19,60,61,66,68,80,81,86,89,90,91,98,99,100].

Note:
1 <= N <= 10^9
*/
class Solution {
private:
    std::array<int,5> valid_digits = {0, 1, 6, 8, 9};
    std::array<int,10> mappings = {0, 1, -1, -1, -1, -1, 9, -1, 8, 6};
    
    int N;
    int confusing_nums;
    
    bool is_confusing(int x) {
        int digits[10];
        int i = 0;
        while (x) {
            digits[i++] = x % 10;
            x /= 10;
        }
        for (int left = 0, right = i-1; left <= right; ++left, --right) {
            if (digits[left] != mappings[digits[right]]) {
                return true;
            }
        }

        return false; 
    }

    void recurse1(const long long x) {
        if (x > N) {
            return;
        }
        if (is_confusing(x)) {
            ++confusing_nums;
        }
        for (const auto y : valid_digits) {
            recurse1(10*x + y);
        }
    }

    int solution1(const int N) {
        this->N = N;
        confusing_nums = 0;
        for (const auto x : {1, 6, 8, 9}) {
            recurse1(x);
        }
        return confusing_nums;
    }
public:
    int confusingNumberII(int N) {
        return solution1(N); 
    }
};
