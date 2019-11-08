/*

Given a string S and a string T, count the number of distinct subsequences of S which equals T.
A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. 
(ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).

Example 1:
Input: S = "rabbbit", T = "rabbit"
Output: 3
Explanation:
As shown below, there are 3 ways you can generate "rabbit" from S.
(The caret symbol ^ means the chosen letters)
rabbbit
^^^^ ^^
rabbbit
^^ ^^^^
rabbbit
^^^ ^^^

Example 2:
Input: S = "babgbag", T = "bag"
Output: 5
Explanation:
As shown below, there are 5 ways you can generate "bag" from S.
(The caret symbol ^ means the chosen letters)
babgbag
^^ ^
babgbag
^^    ^
babgbag
^    ^^
babgbag
  ^  ^^
babgbag
    ^^^

*/

class Solution {
private:
    int M;
    int N;
    /************************************************************************************/
    int** cache1;
    void init_cache1() {
        cache1 = new int*[M+1];
        for (int i = 0; i <= M; ++i) {
            cache1[i] = new int[N+1];
            for (int j = 0; j <= N; ++j) {
                cache1[i][j] = -1;
            }
        }
    }
    void destory_cache1() {
        for (int i = 0; i <= M; ++i) {
            delete[] cache1[i];
        }
        delete[] cache1;
    }
    bool in_cache1(const int i, const int j) {
        return cache1[i][j] >= 0;
    }
    int set_cache1(const int i, const int j, const int val) {
        return cache1[i][j] = val;
    }
    int recurse1(const std::string& s, const std::string& t, const int i, const int j) {
        if (in_cache1(i, j)) {
            return cache1[i][j];
        }

        int subsqns;
        if (i == M) {
            subsqns = j == N;
        } else if (j == N) {
            subsqns = 1;
        } else {
            subsqns = recurse1(s, t, i+1, j) + (s[i] == t[j] ? recurse1(s, t, i+1, j+1) : 0);
        }
        return set_cache1(i, j, subsqns);
    }
	int solution1(const std::string& s, const std::string& t) {
        M = s.size();
        N = t.size();
        if (M < N) {
            return 0;
        }
        init_cache1();
        int count = recurse1(s, t, 0, 0);
        destory_cache1();
        return count; 
	}
    /************************************************************************************/
    int solution2(const std::string& s, const std::string& t) {
        M = s.size();
        N = t.size();
        if (M < N) {
            return 0;
        }
        auto DP = std::vector<std::vector<int>>(M+1, std::vector<int>(N+1));
        for (int i = 0; i <= M; ++i) {
           DP[i][N] = 1;
        }
        for (int j = 0; j < N; ++j) {
           DP[M][j] = 0;
        }
        for (int i = M-1; i >= 0; --i) {
           for (int j = N-1; j >= 0; --j) {
              DP[i][j] = DP[i+1][j] + (s[i] == t[j] ? DP[i+1][j+1] : 0);
           }
        }
        return DP[0][0];
    } 
    /************************************************************************************/       
public:
    int numDistinct(string s, string t) {
  		return solution2(s, t);
    }
};
