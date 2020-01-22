/*
Validate if a given string can be interpreted as a decimal number.

Some examples:
"0" => true
" 0.1 " => true
"abc" => false
"1 a" => false
"2e10" => true
" -90e3   " => true
" 1e" => false
"e3" => false
" 6e-1" => true
" 99e2.5 " => false
"53.5e93" => true
" --6 " => false
"-+3" => false
"95a54e53" => false

Note: It is intended for the problem statement to be ambiguous. You should gather all requirements up front before implementing one. However, here is a list of characters that can be in a valid decimal number:
Numbers 0-9
Exponent - "e"
Positive/negative sign - "+"/"-"
Decimal point - "."
Of course, the context of these characters also matters in the input.

Update (2015-02-10):
The signature of the C++ function had been updated. If you still see your function signature accepts a const char * argument, please click the reload button to reset your code definition.

*/
class Solution {
private:
    std::string strip(const std::string& S) {
        const int N = S.size();
        int i = 0;
        while (i < N and S[i] == ' ') {
            ++i;
        }
        int j = N-1;
        while (j >= i and S[j] == ' ') {
            --j;
        }

        return i > j ? "" : S.substr(i, j - i + 1); 
    }

    bool is_digit(const char c) {
        return '0' <= c and c <= '9';
    }

    bool solution1(const std::string& S) {
        // remove unnecessary whotespace
        const auto T = strip(S);
        // if its empty then there was no #
        if (T.empty()) {
            return false;
        }
        const int N = T.size();
        int start = 0;
        // -/+ sign (consume it)
        if (T[start] == '-' or T[start] == '+') {
            ++start;
        }
        // -/+ sign by itself is not a number
        if (start == N) {
            return false;
        }
        int i = start;
        // consume as many digits as possible
        while (i < N and is_digit(T[i])) {
            ++i;
        }
        // We didn't consume any digits
        if (i == start and (T[i] != '.' or i >= N-1 or not is_digit(T[i+1]))) {
            // we could have something like '.' or '.e1'which is bad
            return false;
        }
        // Here we assume w have something like -/+83928.
        if (i == N or i == N-1 and T[i] == '.') {
            return true;
        }
        
        if (T[i] == '.') {
            ++i;
        }
        
        while (i < N and is_digit(T[i])) {
            ++i;
        }
        if (i == N) {
            return true;
        }
        if (T[i] != 'e') {
            return false;
        }
        ++i;
        if (i == N) {
            return false;
        }
        if (T[i] == '-' or T[i] == '+') {
            ++i;
        }
        if (i == N) {
            return false;
        }
        start = i;
        while (i < N and is_digit(T[i])) {
            ++i;
        }
        return i == N;
    }
public:
    bool isNumber(string s) {
        return solution1(s);        
    }
};
