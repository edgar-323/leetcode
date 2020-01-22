/*
Given a chemical formula (given as a string), return the count of each atom.
An atomic element always starts with an uppercase character, then zero or more lowercase letters, representing the name.
1 or more digits representing the count of that element may follow if the count is greater than 1. If the count is 1, no digits will follow. For example, H2O and H2O2 are possible, but H1O2 is impossible.

Two formulas concatenated together produce another formula. For example, H2O2He3Mg4 is also a formula.

A formula placed in parentheses, and a count (optionally added) is also a formula. For example, (H2O2) and (H2O2)3 are formulas.

Given a formula, output the count of all elements as a string in the following form: the first name (in sorted order), followed by its count (if that count is more than 1), followed by the second name (in sorted order), followed by its count (if that count is more than 1), and so on.

Example 1:
Input: 
formula = "H2O"
Output: "H2O"
Explanation: 
The count of elements are {'H': 2, 'O': 1}.
Example 2:
Input: 
formula = "Mg(OH)2"
Output: "H2MgO2"
Explanation: 
The count of elements are {'H': 2, 'Mg': 1, 'O': 2}.
Example 3:
Input: 
formula = "K4(ON(SO3)2)2"
Output: "K4N2O14S4"
Explanation: 
The count of elements are {'K': 4, 'N': 2, 'O': 14, 'S': 4}.
Note:

All atom names consist of lowercase letters, except for the first character which is uppercase.
The length of formula will be in the range [1, 1000].
formula will only consist of letters, digits, and round parentheses, and is a valid formula as defined in the problem.
*/
class Solution {
private:
    typedef std::pair<std::string,int> Node;

    bool is_lowercase(const char c) {
        return 'a' <= c and c <= 'z';
    }

    bool is_digit(const char c) {
        return '0' <= c and c <= '9';
    }

    std::string get_atom(const std::string& formula, int& pos) {
        const int N = formula.size(); 
        auto atom = std::string(1, formula[pos++]); 
        while (pos < N and is_lowercase(formula[pos])) {
            atom += formula[pos++];
        }
        return atom;
    }

    int get_count(const std::string& formula, int& pos) {
        const int N = formula.size();
        const int start = pos;
        while (pos < N and is_digit(formula[pos])) {
            ++pos;
        }
        return pos == start ? 1 : std::stoi(formula.substr(start, pos - start));
    }

    std::string solution1(const std::string& formula) {
        const int N = formula.size();
        int pos = 0;
        auto stack = std::stack<Node>();
        while (pos < N) {
            if (formula[pos] == ')') {
                const auto count = get_count(formula, ++pos);
                auto temp_stack = std::stack<Node>();
                while (stack.top().first != "(") {
                    temp_stack.push({ stack.top().first, stack.top().second * count });
                    stack.pop();
                }
                stack.pop();
                while (not temp_stack.empty()) {
                    stack.push(temp_stack.top());
                    temp_stack.pop();
                }
            } else if (formula[pos] == '(') {
                stack.push({"(", -1});
                ++pos;
            } else {
                stack.push({ get_atom(formula, pos), get_count(formula, pos) });
            }
        }
        auto atoms = std::map<std::string, int>();
        while (not stack.empty()) {
            const auto node = stack.top(); stack.pop();
            atoms[node.first] += node.second;
        }
        auto result = std::string("");
        for (const auto& atom : atoms) {
            result += atom.first;
            if (atom.second > 1) {
                result += std::to_string(atom.second);
            }
        }
        return result;
    }
public:
    string countOfAtoms(string formula) {
        return solution1(formula); 
    }
};
