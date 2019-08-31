/*
Given an encoded string, return its decoded string.
The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. 
Note that k is guaranteed to be a positive integer.
You may assume that the input string is always valid; No extra white spaces, square brackets are well-formed, etc.
Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there won't be input like 3a or 2[4].

Examples:
s = "3[a]2[bc]", return "aaabcbc".
s = "3[a2[c]]", return "accaccacc".
s = "2[abc]3[cd]ef", return "abcabccdcdcdef".
*/

class Solution {
private:    
    std::string S;
    int N;
    int pos;
    
    int toDigit(const char& c) {
        switch (c) {
            case '0': return 0;
            case '1': return 1;
            case '2': return 2;
            case '3': return 3;
            case '4': return 4;
            case '5': return 5;
            case '6': return 6;
            case '7': return 7;
            case '8': return 8;
            case '9': return 9;
            default: return -1;
        }
    }
    
    bool isDigit(const char& c) {
        return ('0' <= c) && (c <= '9');
    }
    
    std::string repeat(const std::string& s, const int& k) {
        // As long as we parsed correctly, k > 0.
        std::string repeatedStr = "";
        repeatedStr.reserve( k * s.size() );

	   	while (k > 0) {
            repeatedStr += s;
            --k;
        }
        return repeatedStr;
    }
    
    int parseNum() {
        int end = pos+1;
        while (isDigit(S[end])) {
            ++end;
        }
        int k = 0; 
        for (int dec = 1, i = end-1; i >= pos; --i, dec *= 10) {
            k += (dec*toDigit(S[i]));
        }
        pos = end;
        return k;
    }
    
    std::string decode() {
        std::string decodedStr = "";
        
        while (pos < N && S[pos] != ']') {
            if (isDigit(S[pos])) {
                const int k = parseNum();
                ++pos; // [
                std::string s = decode();
                decodedStr += repeat(s, k);
                ++pos; // ]
            } else {
                decodedStr += S[pos];
                ++pos;
            }
        }
        
        return decodedStr;
    }
    
    std::string solution1(std::string& s) {
        /*
        Time-Complexity:    ?
        Space-Complexity:   ?
        */
        S = s;
        N = S.size();
        pos = 0;
        
        return decode();
    }
    
public:
    string decodeString(string s) {
        return solution1(s);
    }
};
