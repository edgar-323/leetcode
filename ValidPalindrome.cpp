/*
Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

Note: For the purpose of this problem, we define empty string as valid palindrome.

Example 1:

Input: "A man, a plan, a canal: Panama"
Output: true
Example 2:

Input: "race a car"
Output: false
*/

class Solution {
private:
    bool charsMatch(char c1, char c2) {
        if (isNumber(c1) and isNumber(c2)) {
            return c1 == c2;
        } else if (isLetter(c1) and isLetter(c2)) {
            int diff = std::abs(int(c1) - int(c2));
            return diff == 0 or diff == 32;
        }
        return false;
    }

    bool isLetter(char c) {
        return ('a' <= c and c <= 'z') or 
                ('A' <= c and c <= 'Z');
    }

    bool isNumber(char c) {
        return '0' <= c and c <= '9';
    }

    bool isAlphanumeric(char c) {
        return isLetter(c) or isNumber(c);
    }

    bool solution1(std::string& s) {
        std::string t = "";
        for (char c : s) {
            if (isAlphanumeric(c)) {
                t += c;
            }
        }

        const int N = t.size();
        for (int i = 0; i < N / 2; ++i) {
            if (!charsMatch(t[i], t[N-1 - i])) {
                return false;
            }
        }
        
        return true;   
    }
public:
    bool isPalindrome(std::string s) {
        return solution1(s);   
    }
};

