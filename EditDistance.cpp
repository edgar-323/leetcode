/*
Given two words word1 and word2, find the minimum number of operations required to convert word1 to word2.

You have the following 3 operations permitted on a word:

Insert a character
Delete a character
Replace a character
Example 1:

Input: word1 = "horse", word2 = "ros"
Output: 3
Explanation: 
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')
Example 2:

Input: word1 = "intention", word2 = "execution"
Output: 5
Explanation: 
intention -> inention (remove 't')
inention -> enention (replace 'i' with 'e')
enention -> exention (replace 'n' with 'x')
exention -> exection (replace 'n' with 'c')
exection -> execution (insert 'u')
*/
class Solution {
private:
    int min(int a, int b) {
        return (a < b) ? a : b;
    }
    
    int min(int a, int b, int c) {
        return min(a, min(b, c));
    }
    
    int solution1(string& a, string& b) {
        /*
        Time-Complexity:    O(M*N)
        Space-Complexity:   O(M*N)
        */
        const int M = a.size();
        const int N = b.size();
        int dp[M+1][N+1];
        dp[0][0] = 0;
        for (int i = 1; i <= M; ++i) {
            dp[i][0] = i;
        }
        for (int j = 1; j <= N; ++j) {
            dp[0][j] = j;
        }
        for (int i = 1; i <= M; ++i) {
            for (int j = 1; j <= N; ++j) {
                dp[i][j] = min(
                            dp[i-1][j] + 1, 
                            dp[i][j-1] + 1, 
                            dp[i-1][j-1] + 
                            ((a[i-1] == b[j-1]) ? 0 : 1));
            }
        }
        return dp[M][N];
    }
    
public:
    int minDistance(string word1, string word2) {
        /*
        OPS: 
            1. Insertion
            2. Deletion
            3. Substitution
        */
        return solution1(word1, word2);
    }
};
