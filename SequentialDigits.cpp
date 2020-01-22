/*
An integer has sequential digits if and only if each digit in the number is one more than the previous digit.
Return a sorted list of all the integers in the range [low, high] inclusive that have sequential digits.

Example 1:
Input: low = 100, high = 300
Output: [123,234]

Example 2:
Input: low = 1000, high = 13000
Output: [1234,2345,3456,4567,5678,6789,12345] 

Constraints:
10 <= low <= high <= 10^9
*/
class Solution {
private:
    std::vector<int> solution1(const int low, const int high) {
        auto Q = std::queue<int>();
        for (int i = 1; i <= 9; i++) {
            Q.push(i);
        }
        auto results = std::vector<int>();

        while (not Q.empty()) {
            const auto num = Q.front(); Q.pop();
            if (low <= num and num <= high) {
                results.push_back(num);
            } else if (num > high) {
                break;
            }
            const int rem = num % 10;
            if (rem < 9) {
                // Add next sequential digit to current number
                Q.push(10*num + (rem + 1));
            }
        }

        return results; 
      
    }

public:
    vector<int> sequentialDigits(int low, int high) {
        return solution1(low, high);    
    }
};
