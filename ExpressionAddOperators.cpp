/*
Given a string that contains only digits 0-9 and a target value, 
return all possibilities to add binary operators (not unary) +, -, or * between the digits so they evaluate to the target value.

Example 1:
Input: num = "123", target = 6
Output: ["1+2+3", "1*2*3"] 

Example 2:
Input: num = "232", target = 8
Output: ["2*3+2", "2+3*2"]

Example 3:
Input: num = "105", target = 5
Output: ["1*0+5","10-5"]

Example 4:
Input: num = "00", target = 0
Output: ["0+0", "0-0", "0*0"]

Example 5:
Input: num = "3456237490", target = 9191
Output: []
*/
class Solution {
private:
    int N;
    int T;
    
    int get_digit(const char c) {
        return c - '0';
    }
    
    std::string get_expression(const std::vector<std::string>& combo) {
        auto str = std::string("");
        const int K = combo.size();
        for (int i = 1; i < K; ++i) {
            str += combo[i];
        }
        return str;
    }

    void recurse1(
            const int i,
            const long long prev_num,
            const long long curr_num,
            const long long value,
            const std::string& digits,
            std::vector<std::string>& combo,
            std::vector<std::string>& results) {

        if (i == N) {
            if (value == T and curr_num == 0) {
                results.push_back(get_expression(combo));
            }
            return;
        }
        
        const auto new_num = 10*curr_num + get_digit(digits[i]);
        const auto new_num_str = std::to_string(new_num);

        if (new_num) {
            recurse1(i+1, prev_num, new_num, value, digits, combo, results);
        }
        
        // Addition
        combo.push_back("+");
        combo.push_back(new_num_str);
        recurse1(i+1, new_num, 0, value + new_num, digits, combo, results);
        combo.pop_back();
        combo.pop_back();

        if (not combo.empty()) {
            // Subtraction
            combo.push_back("-");
            combo.push_back(new_num_str);
            recurse1(i+1, -new_num, 0, value - new_num, digits, combo, results);
            combo.pop_back();
            combo.pop_back();
            // Multiplication
            combo.push_back("*");
            combo.push_back(new_num_str);
            recurse1(i+1, prev_num*new_num, 0, value + prev_num*(new_num - 1), digits, combo, results);
            combo.pop_back();
            combo.pop_back();
        }
    }

    std::vector<std::string> solution1(const std::string& digits, const int target) {
        if (digits.empty()) {
            return {};
        }

        N = digits.size();
        T = target;
        auto combo = std::vector<std::string>();
        auto results = std::vector<std::string>();
        recurse1(0, 0, 0, 0, digits, combo, results);

        return results; 
    }
public:
    vector<string> addOperators(string num, int target) {
        return solution1(num, target);        
    }
};
