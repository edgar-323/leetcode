/*
Given a string which contains only lowercase letters, remove duplicate letters so that every letter appears once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.

Example 1:
Input: "bcabc"
Output: "abc"

Example 2:
Input: "cbacdcbc"
Output: "acdb"
*/

class Solution {
private:
    static const int ALPH_SZ = 26;

    int index(const char c) {
        return c - 'a';
    }

    std::string remove_all(const std::string& S, const char remove) {
        auto output = std::string("");
        output.reserve(S.size());
        for (const auto c : S) {
            if (c != remove) { 
                output += std::string(1, c);
            }
        }
        return output;
    }

    std::string recurse1(const std::string& S) {
        if (S.empty()) {
            return "";
        }

        auto count = std::vector<int>(ALPH_SZ, 0);
        for (const auto c : S) {
            ++count[index(c)];
        }
        const int N = S.size();
        int pos = 0;
        for (int i = 0; i < N; ++i) {
            if (S[i] < S[pos]) {
                pos = i;
            } 
            if (--count[index(S[i])] == 0) {
                break;
            }
        }

        return std::string(1, S[pos]) + recurse1( remove_all( S.substr(pos+1), S[pos] ) ); 
    }

    std::string solution1(const std::string& S) {
        return recurse1(S);
    }
public:
    string removeDuplicateLetters(string s) {
        return solution1(s);        
    }
};
