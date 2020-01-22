/*
Your music player contains N different songs and she wants to listen to L (not necessarily different) songs during your trip.  
You create a playlist so that:
Every song is played at least once
A song can only be played again only if K other songs have been played
Return the number of possible playlists.  As the answer can be very large, return it modulo 10^9 + 7.

Example 1:
Input: N = 3, L = 3, K = 1
Output: 6
Explanation: There are 6 possible playlists. [1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1].

Example 2:
Input: N = 2, L = 3, K = 0
Output: 6
Explanation: There are 6 possible playlists. [1, 1, 2], [1, 2, 1], [2, 1, 1], [2, 2, 1], [2, 1, 2], [1, 2, 2]

Example 3:
Input: N = 2, L = 3, K = 1
Output: 2
Explanation: There are 2 possible playlists. [1, 2, 1], [2, 1, 2]

Note:
0 <= K < N <= L <= 100
*/
class Solution {
private:
    typedef long long LL;
    static const int MOD_VAL = 1e9 + 7;

    int solution1(const int N, const int L, const int K) {
        /* Time-Complexity:     O(L*N)
         * Space-Complexity:    O(L*N)
         */
        /*
         * INTUITION: 
         * Let dp[i][j] be the number of playlists of length i that have exactly j unique songs.
         * We want dp[L][N], and it seems likely we can develop a recurrence for dp.
         *
         * ALGORITHM:
         * Consider dp[i][j].
         * Last song, we either played a song for the first time or we didn't.
         * If we did, then we had dp[i-1][j-1] * (N-(j-1)) ways to choose it.
         * If we didn't, then we repeated a previous song in dp[i-1][j] * max(j-K, 0) ways 
         * (j of them, except the last K ones played are banned.)
         *
         */
        auto DP = std::vector<std::vector<LL>>(L+1, std::vector<LL>(N+1, 0));
        DP[0][0] = 1;
        for (int i = 1; i <= L; ++i) {
            for (int j = 1; j <= N; ++j) {
                DP[i][j] = (DP[i][j] + DP[i-1][j-1] * (N-(j-1))) % MOD_VAL;
                DP[i][j] = (DP[i][j] + DP[i-1][j] * std::max(j - K, 0)) % MOD_VAL;
            }
        }
        return int(DP[L][N]);
    }
public:
    int numMusicPlaylists(int N, int L, int K) {
        return solution1(N, L, K);        
    }
};
