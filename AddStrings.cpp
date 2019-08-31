/*
Given two non-negative integers num1 and num2 represented as string, return the sum of num1 and num2.

Note:
The length of both num1 and num2 is < 5100.
Both num1 and num2 contains only digits 0-9.
Both num1 and num2 does not contain any leading zero.
You must not use any built-in BigInteger library or convert the inputs to integer directly.
*/

class Solution {
private:
    int to_int(const char c) {
        return int(c - '0');
    }

    std::string to_string(int x) {
        switch(x) {
            case 0: return "0";
            case 1: return "1";
            case 2: return "2";
            case 3: return "3";
            case 4: return "4";
            case 5: return "5";
            case 6: return "6";
            case 7: return "7";
            case 8: return "8";
            case 9: return "9";
            default: return "ERROR";
        }
    }

    std::string solution1(const std::string& s, const std::string& t) {
        /* 
         * Time-Complexity:     O( S+T )
         * Space-Complexity:    O(  1  )
         * */
        const int S = s.size();
        const int T = t.size();
        
        std::string added_strs;
        added_strs.reserve( std::max( S, T ) + 1 );
        added_strs = "";
        const int min = std::min( S, T );
        int carry = 0;
        int sum;
        int i;
        for (i = 0; i < min; ++i) {
            sum = to_int( s[S-1-i] ) + to_int( t[T-1-i] ) + carry;
            added_strs += to_string( sum%10 );
            carry = sum/10; 
        }
        for (; i < S; ++i) {
            sum = to_int( s[S-1-i] ) + carry;
            added_strs += to_string( sum%10 );
            carry = sum/10;
        }
        for (; i < T; ++i) {
            sum = to_int( t[T-1-i] ) + carry;
            added_strs += to_string( sum%10 );
            carry = sum/10;
        }
        if ( carry ) {
            added_strs += to_string( carry );
        }
        
        return std::string( added_strs.rbegin(), added_strs.rend() ); 
    }
public:
    string addStrings(string num1, string num2) {
        return solution1( num1, num2 );
    }
};
