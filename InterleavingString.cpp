/*
Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

Example 1:
Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
Output: true

Example 2:
Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
Output: false
*/

class Solution {
private:
    int M, N;
    /******************************************************************************************************************/ 
    int*** cache1;
    void init_cache1() {
        cache1 = new int**[M+1];
        for (int i = 0; i <= M; ++i) {
            cache1[i] = new int*[N+1];
            for (int j = 0; j <= N; ++j) {
                cache1[i][j] = new int[M+N+1];
                for (int k = 0; k <= M+N; ++k) {
                    cache1[i][j][k] = -1;
                }
            }
        }
    }
    void destory_cache1() {
        for (int i = 0; i <= M; ++i) {
            for (int j = 0; j <= N; ++j) {
                delete[] cache1[i][j];
            }
            delete[] cache1[i];
        }
        delete[] cache1;
    }
    bool in_cache1(const int i, const int j, const int k) {
        return cache1[i][j][k] >= 0;
    }
    bool set_cache1(const int i, const int j, const int k, const bool val) {
        cache1[i][j][k] = val ? 1 : 0;
        return val;
    }
    bool recurse1(
            const std::string& s1,
            const std::string& s2,
            const std::string& s3,
            const int i,
            const int j,
            const int k) {
        if (in_cache1(i, j, k)) {
            return cache1[i][j][k];
        }
        bool interleaved;
        if (k == M+N) {
            interleaved =   i == M and 
                            j == N;
        } else if (i == M) {
            interleaved =   j < N and 
                            s2[j] == s3[k] and 
                            recurse1(s1, s2, s3, i, j+1, k+1);
        } else if (j == N) {
            interleaved =   s1[i] == s3[k] and 
                            recurse1(s1, s2, s3, i+1, j, k+1);
        } else {
            interleaved =   (s1[i] == s3[k] and recurse1(s1, s2, s3, i+1, j, k+1)) or
                            (s2[j] == s3[k] and recurse1(s1, s2, s3, i, j+1, k+1));
        }
        return set_cache1(i, j, k, interleaved); 
    }
	bool solution1(const std::string& s1, const std::string& s2, const std::string& s3) {
        /* Time-Complexity:     O(M*N*(M+N))
         * Space-Complexity:    O(M*N*(M+N))
         */
        M = s1.size();
        N = s2.size(); 
        if (s3.size() != M+N) {
            return false;
        }
        init_cache1();
        bool is_interleaving = recurse1(s1, s2, s3, 0, 0, 0);
        destory_cache1(); 
        return is_interleaving; 
    }
    /******************************************************************************************************************/
    int** cache2;
    void init_cache2() {
        cache2 = new int*[M+1];
        for (int i = 0; i <= M; ++i) {
            cache2[i] = new int[N+1];
            for (int j = 0; j <= N; ++j) {
                cache2[i][j] = -1;
            }
        }
    }
    void destory_cache2() {
        for (int i = 0; i <= M; ++i) {
            delete[] cache2[i];
        }
        delete[] cache2;
    }
    bool in_cache2(const int i, const int j) {
        return cache2[i][j] >= 0;
    }
    bool set_cache2(const int i, const int j, const bool val) {
        cache2[i][j] = val ? 1 : 0;
        return val;
    }
    bool recurse2(const std::string& s1, const std::string& s2, const std::string s3, const int i, const int j) {
        if (in_cache2(i, j)) {
           return cache2[i][j];
        }
        const int k = i+j;
        bool interleaved;
        if (k == M+N) {
            interleaved = true;
        } else if (i == M) {
            interleaved = s2[j] == s3[k] and recurse2(s1, s2, s3, i, j+1);
        } else if (j == N) {
            interleaved = s1[i] == s3[k] and recurse2(s1, s2, s3, i+1, j);
        } else {
            interleaved =   (s1[i] == s3[k] and recurse2(s1, s2, s3, i+1, j)) or
                            (s2[j] == s3[k] and recurse2(s1, s2, s3, i, j+1));
        }
        return set_cache2(i, j, interleaved);
    }
    bool solution2(const std::string& s1, const std::string& s2, const std::string& s3) {
        /* Time-Complexity:     O(M*N)
         * Space-Complexity:    O(M*N)
         */
        // SAME AS solution1() EXCEPT THAT WE CAN SEE IN THIS SOLUTION THAT THE THIRD 
        // PARAMTER TO recurse() CAN BE ELIMINATED BY NOTICING THAT:
        //  k = i + j
        // AT ALL TIMES. 
       	M = s1.size();
        N = s2.size();
        if (s3.size() != M+N) {
            return false;
        }
        init_cache2();
        const bool is_interleaving = recurse2(s1, s2, s3, 0, 0);
        destory_cache2();
        return is_interleaving;
    }
    /******************************************************************************************************************/
    bool solution3(const std::string& s1, const std::string& s2, const std::string& s3) {
        /* Time-Complexity:     O(M*N)
         * Space-Complexity:    O(M*N)
         */
        // DP VERSION OF solution2() 
        M = s1.size();
        N = s2.size();
        if (s3.size() != M+N) {
          return false;
        }
        auto DP = std::vector<std::vector<bool>>(N+1, std::vector<bool>(M+1));
        DP[M][N] = true;
        for (int j = N-1; j >= 0; --j) {
            DP[M][j] = s2[j] == s3[M+j] and DP[M][j+1];
        }
        for (int i = M-1; i >= 0; --i) {
            DP[i][N] = s1[i] == s3[i+N] and DP[i+1][N];
        }
        for (int i = M-1; i >= 0; --i) {
            for (int j = N-1; j >= 0; --j) {
                DP[i][j] =  (s1[i] == s3[i+j] and DP[i+1][j]) or
                            (s2[j] == s3[i+j] and DP[i][j+1]);
            }
        }
        return DP[0][0];
    }
    /******************************************************************************************************************/
public:
    bool isInterleave(string s1, string s2, string s3) {
  		return solution3(s1, s2, s3);
    }
};
