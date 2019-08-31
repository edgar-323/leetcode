/*
Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent.
A mapping of digit to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.

Example:
Input: "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

Note:
Although the above answer is in lexicographical order, your answer could be in any order you want.
*/
class Solution {
private:
    int N;
    std::vector<std::vector<char>> map; 

    int index(const char& c) {
        return int( c - '2' );
    }

    void dfs(
            const std::string& digits, 
            const int i, 
            const std::string curr, 
            std::vector<std::string>& results) {
        if (i >= N) {
            if (curr.size()) {
                results.push_back(curr);
            }
            return;
        }
        for (const char& c : map[index(digits[i])]) {
            dfs( digits, i + 1, curr + std::string( 1, c ), results );
        } 
    }
    
    std::vector<std::string> solution1(const std::string& digits) {
        N = digits.size();
        std::vector<std::string> results;
        dfs(digits, 0, "", results);
        return results;
    }
public:
   	Solution() {
        map.reserve( 8 );
        map.push_back( std::vector<char> { 'a', 'b', 'c' } ); 
        map.push_back( std::vector<char> { 'd', 'e', 'f' } );
        map.push_back( std::vector<char> { 'g', 'h', 'i' } );
        map.push_back( std::vector<char> { 'j', 'k', 'l' } ); 
        map.push_back( std::vector<char> { 'm', 'n', 'o' } );
        map.push_back( std::vector<char> { 'p', 'q', 'r', 's' } ); 
        map.push_back( std::vector<char> { 't', 'u', 'v' } );
        map.push_back( std::vector<char> { 'w', 'x', 'y', 'z' } );
    } 
    std::vector<std::string> letterCombinations(std::string digits) {
        return solution1( digits );
    }
};
