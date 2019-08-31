/*
Write a function that takes a string as input and reverse only the vowels of a string.

Example 1:
Input: "hello"
Output: "holle"

Example 2:
Input: "leetcode"
Output: "leotcede"

Note:
Vowels: [a, e, i, o, u]
The vowels does not include the letter "y".
*/

class Solution {
private:
    bool is_vowel(const char c) {
        return c == 'a' or c == 'A' or 
                c == 'e' or c == 'E' or 
                c == 'i' or c == 'I' or 
                c == 'o' or c == 'O' or 
                c == 'u' or c == 'U';
    }
    void solution1(std::string& s) {
        /* 
         * Time-Complexity:     O( N )
         * Space-Complexity:    O( 1 )
         * */
        const int N = s.size();
        for (int l = 0, r = N-1; l < r; ++l, --r) {
            while (l < r and !is_vowel( s[l] )) {
                ++l;
            }
            while (l < r and !is_vowel( s[r] )) {
                --r;
            }
            if (l < r) {
                std::swap( s[l], s[r] );
            }
        }
    }
public:
    std::string reverseVowels(std::string s) {
		solution1( s );
        return s;
    }
};
