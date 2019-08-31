/*
Given two strings s and t , write a function to determine if t is an anagram of s.

Example 1:

Input: s = "anagram", t = "nagaram"
Output: true
Example 2:

Input: s = "rat", t = "car"
Output: false
Note:
You may assume the string contains only lowercase alphabets.

Follow up:
What if the inputs contain unicode characters? How would you adapt your solution to such case?
*/

class Solution {
private:
    bool solution1(std::string& s, std::string& t) {
        /*
         * Time-Complexity:     O(N + M)
         * Space-Complexity:    O(1)
         * */
        const int ALPH_SZ = 26;
        const char a = 'a';
        int map_t[ALPH_SZ];
        int map_s[ALPH_SZ];
        for (int i = 0; i < ALPH_SZ; ++i) {
            map_t[i] = map_s[i] = 0;
        }
        const int M = s.size();
        const int N = t.size();
        for (int i = 0; i < M; ++i) {
            map_s[s[i] - a]++;
        }
        for (int i = 0; i < N; ++i) {
            map_t[t[i] - a]++;
        }
        for (int i = 0; i < ALPH_SZ; ++i) {
            if (map_t[i] != map_s[i]) {
                return false;
            }
        }
        return true;
    }
public:
    bool isAnagram(string s, string t) {
        return solution1(s, t);
    }
};
