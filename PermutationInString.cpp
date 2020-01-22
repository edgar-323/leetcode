/*
Given two strings s1 and s2, write a function to return true if s2 contains the permutation of s1. In other words, one of the first string's permutations is the substring of the second string.

Example 1:
Input: s1 = "ab" s2 = "eidbaooo"
Output: True
Explanation: s2 contains one permutation of s1 ("ba").

Example 2:
Input:s1= "ab" s2 = "eidboaoo"
Output: False

Note:
The input strings only contain lower case letters.
The length of both given strings is in range [1, 10,000].
*/
class Solution {
private:
    static const int ALPH_SZ = 26;

    int index(const char c) {
        return c - 'a';
    }

    bool solution1(const std::string& s, const std::string& t) {
        /* Time-Complexity:     O(M + ALPH_SZ*N)
         * Space-Complexity:    O(ALPH_SZ)
         */

        const int M = s.size();
        const int N = t.size();
        if (M > N) {
            return false;
        } 
        auto s_count =  std::vector<int>(ALPH_SZ, 0);
        for (int i = 0; i < M; ++i) {
            ++s_count[index(s[i])];
        }
        auto t_count = std::vector<int>(ALPH_SZ, 0);
        int j = 0;
        while (j < M) {
            t_count[index(t[j++])]++;
        }
        while (j < N) {
            if (s_count == t_count) {
                return true;
            }
            t_count[index(t[j-M])]--;
            t_count[index(t[j++])]++;
        }
        return t_count == s_count;
    }
public:
    bool checkInclusion(string s1, string s2) {
        return solution1(s1, s2);        
    }
};
