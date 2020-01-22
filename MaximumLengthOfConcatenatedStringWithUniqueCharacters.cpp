/*
Given an array of strings arr. String s is a concatenation of a sub-sequence of arr which have unique characters.
Return the maximum possible length of s.

Example 1:
Input: arr = ["un","iq","ue"]
Output: 4
Explanation: All possible concatenations are "","un","iq","ue","uniq" and "ique".
Maximum length is 4.

Example 2:
Input: arr = ["cha","r","act","ers"]
Output: 6
Explanation: Possible solutions are "chaers" and "acters".

Example 3:
Input: arr = ["abcdefghijklmnopqrstuvwxyz"]
Output: 26

Constraints:
1 <= arr.length <= 16
1 <= arr[i].length <= 26
arr[i] contains only lower case English letters.
*/
class Solution {
private:
    static const int MAX_LETTER = 26;

    int max_len;
    int N;
    
    int get_num_letters(const int letters) {
        int num_letters = 0;
        for (int i = 0; i < MAX_LETTER; ++i) {
            if (letters & (1 << i)) {
                ++num_letters;
            }
        }
        return num_letters;    
    }

    int letter(const char c) {
        return c - 'a';
    }
    
    int can_concatenate(const std::string& S, const int letters) {
        int new_letters = letters;
        for (const char c : S) {
            if (new_letters & (1 << letter(c))) {
                return false;
            }
            new_letters |= (1 << letter(c));
        }
        return true;
    }

    int concatenate(const std::string& S, const int letters) {
        int new_letters = letters;
        for (const char c : S) {
            new_letters |= (1 << letter(c));
        }
        return new_letters;
    }

    void recurse1(const int i, const int letters, const std::vector<std::string>& A) {
        max_len = std::max(max_len, get_num_letters(letters));
        for (int j = i; j < N; ++j) {
            if (can_concatenate(A[j], letters)) {
                recurse1(j+1, concatenate(A[j], letters), A);
            }
        }
    }

    int solution1(const std::vector<std::string>& A) {
        max_len = 0;
        N = A.size();
        recurse1(0, 0, A);
        
        return max_len;     
    }
public:
    int maxLength(vector<string>& arr) {
        return solution1(arr); 
    }
};
