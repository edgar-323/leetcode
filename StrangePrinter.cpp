/*
There is a strange printer with the following two special requirements:

    1) The printer can only print a sequence of the same character each time.
    2) At each turn, the printer can print new characters starting from and ending at any places, and will cover the original existing characters.

Given a string consists of lower English letters only, your job is to count the minimum number of turns the printer needed in order to print it.

Example 1:
Input: "aaabbb"
Output: 2
Explanation: Print "aaa" first and then print "bbb".

Example 2:
Input: "aba"
Output: 2
Explanation: Print "aaa" first and then print "b" from the second place of the string, which will cover the existing character 'a'.

Hint: Length of the given string will not exceed 100.
*/


class Solution {
private:
    int N;
    int** cache1;
    void init_cache1() {
        cache1 = new int*[N];
        for (int i = 0; i < N; ++i) {
            cache1[i] = new int[N];
            for (int j = 0; j < N; ++j) {
                cache1[i][j] = -1;
            }
        }
    }
    void destroy_cache1() {
        for (int i = 0; i < N; ++i) {
            delete[] cache1[i];
        }
        delete[] cache1;
    }
    int recurse1(const int i, const int j, const std::string& S) {
        if (i > j) {
            return 0;
        } else if (cache1[i][j] >= 0) {
            return cache1[i][j];
        }

        int min_turns;
        min_turns = 1 + recurse1(i+1, j, S);
        for (int k = i+1; k <= j; ++k) {
            if (S[k] == S[i]) {
                min_turns = std::min(min_turns, recurse1(i, k-1, S) + recurse1(k+1, j, S));
            }
        }

        return cache1[i][j] = min_turns;
    }
	int solution1(const std::string& S) {
        N = S.size();
        init_cache1();
        const int min_turns = recurse1(0, N-1, S);
        destroy_cache1();
        
        return min_turns;
	}
public:
    int strangePrinter(string s) {
        return solution1(s);
    }
};
