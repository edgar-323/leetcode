/*
Write a program that outputs the string representation of numbers from 1 to n.

But for multiples of three it should output “Fizz” instead of the number and for the multiples of five output “Buzz”. For numbers which are multiples of both three and five output “FizzBuzz”.

Example:

n = 15,

Return:
[
    "1",
    "2",
    "Fizz",
    "4",
    "Buzz",
    "Fizz",
    "7",
    "8",
    "Fizz",
    "Buzz",
    "11",
    "Fizz",
    "13",
    "14",
    "FizzBuzz"
]
*/
class Solution {
private:
	std::vector<std::string> solution1(int N) {
        std::vector<std::string> results;
        std::string s;
        for (int i = 1; i <= N; ++i) {
            if (i % 3 == 0) {
                s = "Fizz";
                if (i % 5 == 0) {
                    s += "Buzz";
                }
            } else if (i % 5 == 0) { 
                s = "Buzz";
            } else {
                s = std::to_string(i);
            }
            results.push_back(s);
        }
        return results;
	}
public:
    vector<string> fizzBuzz(int n) {
        return solution1(n);
    }
};

