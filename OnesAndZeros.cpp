/*
In the computer world, use restricted resource you have to generate maximum benefit is what we always want to pursue.
For now, suppose you are a dominator of m 0s and n 1s respectively. 
On the other hand, there is an array with strings consisting of only 0s and 1s.

Now your task is to find the maximum number of strings that you can form with given m 0s and n 1s. Each 0 and 1 can be used at most once.

Note:
The given numbers of 0s and 1s will both not exceed 100
The size of given string array won't exceed 600.
 

Example 1:
Input: Array = {"10", "0001", "111001", "1", "0"}, m = 5, n = 3
Output: 4
Explanation: This are totally 4 strings can be formed by the using of 5 0s and 3 1s, which are “10,”0001”,”1”,”0”
 

Example 2:
Input: Array = {"10", "0", "1"}, m = 1, n = 1
Output: 2

Explanation: You could form "10", but then you'd have nothing left. Better form "0" and "1".
*/

class Solution {
private:
    int L;
    /************************************************************************************************/ 
    int*** cache;
    void cache_init(const int M, const int N) {
        cache = new int**[L];
        for (int i = 0; i < L; ++i) {
            cache[i] = new int*[M+1];
            for (int j = 0; j <= M; ++j) {
                cache[i][j] = new int[N+1];
                for (int k = 0; k <= N; ++k) {
                    cache[i][j][k] = -1;
                }
            }
        }
    }
    void cache_destroy(const int M, const int N) {
        for (int i = 0; i < L; ++i) {
            for (int j = 0; j <= M; ++j) {
                delete[] cache[i][j];
            }
            delete[] cache[i];
        }
        delete[] cache;
    }
    std::pair<int,int>* word_cost;
    void word_cost_init(const std::vector<std::string>& strs) {
        word_cost = new std::pair<int,int>[L];
        for (int i = 0; i < L; ++i) {
            const std::string& str = strs[i];
            int m = 0;
            int n = 0;
            for (const auto& c : str) {
                if (c == '0') {
                    ++m;
                } else {
                    ++n;
                }
            }
            word_cost[i] = std::make_pair(m, n);
        }
    }
    void word_cost_destroy() {
        delete[] word_cost;
    }
	int recurse1(const int i, const int M, const int N) {
        if (i >= L) {
            return 0;
        } else if (cache[i][M][N] >= 0) {
            return cache[i][M][N];
        }
        
        const int m = M - word_cost[i].first;
        const int n = N - word_cost[i].second;

        return cache[i][M][N] = std::max(
                                    recurse1(i+1, M, N),
                                    m < 0 or n < 0 ? 0 :
                                    recurse1(i+1, m, n) + 1);
    }
    int solution1(const std::vector<std::string>& strs, const int M, const int N) {
        L = strs.size();
        if (!L) {
            return 0;
        }
        cache_init(M, N);
        word_cost_init(strs);
        int result = recurse1(0, M, N);
        cache_destroy(M, N);
        word_cost_destroy();
        return result;
	}
    /************************************************************************************************/
    int solution2(const std::vector<std::string>& strs, const int M, const int N) {
        /* Time-Complexity:     O(L*M*N + P)
         * Space-Complexity:    O(  L*M*N  )
         *  where:
         *      P = ∑ { size(str) | str € strs }
         * */
        L = strs.size();
        if (!L) {
            return 0;
        }
        
        // O(P)-Time Complexity
        auto str_cost = std::vector<std::pair<int,int>>(L);
        for (int i = 0; i < L; ++i) {
            const std::string& str = strs[i];
            int m = 0;
            int n = 0;
            for (const auto& c : str) {
                if (c == '0') {
                    ++m;
                } else {
                    ++n;
                }
            }
            str_cost[i].first = m;
            str_cost[i].second = n;
        }
        
        // O(L*M*N)-Time Complexity
        auto DP = std::vector<std::vector<std::vector<int>>>(
                        L+1, 
                        std::vector<std::vector<int>>(
                            M+1, std::vector<int>(
                                N+1, 
                                0)));
        for (int i = L-1; i >= 0; --i) {
            for (int m = 0; m <= M; ++m) {
                for (int n = 0; n <= N; ++n) {
                    int m2 = m - str_cost[i].first;
                    int n2 = n - str_cost[i].second;
                    DP[i][m][n] = std::max(
                                    DP[i+1][m][n],
                                    m2 < 0 or n2 < 0 ? 0 :
                                    DP[i+1][m2][n2] + 1);
                }
            }
        }
        
        return DP[0][M][N];
    }
    /************************************************************************************************/
public:
    int findMaxForm(std::vector<std::string>& strs, int m, int n) {
        return solution2(strs, m, n);     
    }
};
