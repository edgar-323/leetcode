/*
Given two strings str1 and str2, return the shortest string that has both str1 and str2 as subsequences.  
If multiple answers exist, you may return any of them.

(A string S is a subsequence of string T if deleting some number of characters from T (possibly 0, and the characters are chosen anywhere from T) results in the string S.)

Example 1:
Input: str1 = "abac", str2 = "cab"
Output: "cabac"
Explanation: 
str1 = "abac" is a subsequence of "cabac" because we can delete the first "c".
str2 = "cab" is a subsequence of "cabac" because we can delete the last "ac".
The answer provided is the shortest such string that satisfies these properties.
 
Note:
1 <= str1.length, str2.length <= 1000
str1 and str2 consist of lowercase English letters.
*/

class Solution {
private:
    int M,N;
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
    void destroy_cache1() {
        for (int i = 0; i <= M; ++i) {
            delete[] cache1[i];
        }
        delete[] cache1;
    }
    int recurse1(const int i, const int j, const std::string& S, const std::string& T) {
        if (cache1[i][j] >= 0) {
            return cache1[i][j];
        }
        int shortest;
        if (i == M and j == N) {
            shortest = 0;
        } else if (i == M) {
            shortest = N - j;
        } else if (j == N) {
            shortest = M - i;
        } else if (S[i] == T[j]) {
            shortest = 1 + recurse1(i+1, j+1, S, T);
        } else {
            shortest = 1 + std::min(recurse1(i+1, j, S, T), recurse1(i, j+1, S, T));
        }

        return cache1[i][j] = shortest;
    }
    std::string build1(const int i, const int j, const std::string& S, const std::string& T) {
        if (i == M and j == N) {
            return "";
        } else if (i == M) {
            return T.substr(j);
        } else if (j == N) {
            return S.substr(i);
        }
        return  S[i] == T[j]?
                std::string(1, S[i]) + build1(i+1, j+1, S, T):
                recurse1(i+1, j, S, T) < recurse1(i, j+1, S, T)?
                std::string(1, S[i]) + build1(i+1, j, S, T):
                std::string(1, T[j]) + build1(i, j+1, S, T);
    }
	std::string solution1(const std::string& S, const std::string& T) {
        /* Time-Complexity:     O(M * N * min{M, N})
         * Space-Complexity:    O(M * N * min{M, N})
         */
        M = S.size();
        N = T.size();

        init_cache1();
        const std::string shortest_super_sqn = build1(0, 0, S, T);
        destroy_cache1();

        return shortest_super_sqn;
	}
public:
    string shortestCommonSupersequence(string str1, string str2) {
  		return solution1(str1, str2);      
    }
};
