/*
Given a string, find the first non-repeating character in it and return it's index. If it doesn't exist, return -1.

Examples:

s = "leetcode"
return 0.

s = "loveleetcode",
return 2.

Note: You may assume the string contain only lowercase letters.
*/

class Solution {
private:
    static const size_t ALPH_SZ = 26;
    int map[ALPH_SZ];
    size_t index(char& c) {
        return c - 'a';
    }
    int solution1(std::string& s) {
        /*
         * Time-Complexity:
         *  ALPH_SZ + 2*N => O( N )
         * Space-Complexity:
         *  ALPH_SZ => O( 1 )
         *  */
        for (size_t i = 0; i < ALPH_SZ; ++i) {
            map[i] = 0;
        }
        for (char& c : s) {
            ++map[index(c)];
        }
        const size_t N = s.size();
        for (size_t pos = 0; pos < N; ++pos) {
            if (map[index(s[pos])] == 1) {
                return pos;
            }
        }
        return -1;
    }
public:
    int firstUniqChar(string s) {
        return solution1( s ); 
    }
};
