/*
Remove the minimum number of invalid parentheses in order to make the input string valid. Return all possible results.
Note: The input string may contain letters other than the parentheses ( and ).

Example 1:
Input: "()())()"
Output: ["()()()", "(())()"]

Example 2:
Input: "(a)())()"
Output: ["(a)()()", "(a())()"]

Example 3:
Input: ")("
Output: [""]
*/

class Solution {
private:
    
    std::string s;
    int minRemoved;
    int N;
    std::unordered_set<std::string> set;
    
    void recurse1(std::string curr, int balance, int pos, int removed) {
        if (balance > N - pos) {
            return;
        }
        if (pos >= N) {
            if (balance == 0) {
                if (removed < minRemoved) {
                    set.clear();
                    set.emplace(curr);
                    minRemoved = removed;
                } else if (removed == minRemoved && 
                           set.count(curr) == 0) {
                    set.emplace(curr);
                }
            }
        } else if (s[pos] == ')') {
            if (balance > 0) {
                std::string str = curr + s[pos];
                recurse1(str, balance-1, pos+1, removed);
            } 
            if (removed+1 <= minRemoved) {
                recurse1(curr, balance, pos+1, removed+1);   
            }
        } else if (s[pos] == '(') {
            std::string str = curr + s[pos];
            recurse1(str, balance+1, pos+1, removed);
            if (removed+1 <= minRemoved) {
                recurse1(curr, balance, pos+1, removed+1);   
            }
        } else {
            std::string str = curr + s[pos];
            recurse1(str, balance, pos+1, removed);
        }
    }
    
    std::vector<std::string> solution1(std::string s) {
        /*
        Time-Complexity:    ?
        Space-Complexity:   ?
        */
        this->s = s;
        this->N = s.size();
        this->set.clear();
        this->minRemoved = INT_MAX;
        recurse1("", 0, 0, 0);
        std::vector<std::string> results;
        for (auto it = set.begin(); it != set.end(); ++it) {
            results.push_back(*it);
        }
        return results;
    }
    
public:
    vector<string> removeInvalidParentheses(string s) {
        return solution1(s);
    }
};
