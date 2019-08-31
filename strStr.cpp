/*
Implement strStr().
Return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

Example 1:
Input: haystack = "hello", needle = "ll"
Output: 2

Example 2:
Input: haystack = "aaaaa", needle = "bba"
Output: -1

Clarification:
What should we return when needle is an empty string? This is a great question to ask during an interview.
For the purpose of this problem, we will return 0 when needle is an empty string. This is consistent to C's strstr() and Java's indexOf().

*/
class Solution {
private:
    int solution1(std::string& haystack, std::string& needle) {
        /*
        Time-Complexity:    O(M*N)
        Space-Complexity:   O(1)
        */
        const int M = haystack.size();
        const int N = needle.size();
        const int L = M - N + 1;
        for (int i = 0; i < L; ++i) {
            bool match = true;
            for (int j = 0; j < N; ++j) {
                if (haystack[i+j] != needle[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return i;
            }
        }
        return -1;
    }

    int index(int i) {
        return i-1;
    }
    
    int solution2(std::string& T, std::string& P) {
        /*
        Z-Algorithm
        **********************************************************
        Paramters:
        @T : text
        @P : pattern 
        **********************************************************
            Time-Complexity:    O(M + N)
            Space-Complexity:   O(M + N)
        **********************************************************
        */
        const int M = T.size();
        const int N = P.size();
        if (M < N) {
            return -1;
        } else if (M == N and N == 0) {
            return 0;
        }
        const int Q = M+N+1;
        /**********************************************************/
        auto S = P + "$" + T;
        int left = 0;
        int right = 0;
        int Z[Q];
        // index 1 is NULL
        Z[index(1)] = 0;
        // compute Z[2] directly as initial case:
        int i = 2;
	    Z[index(2)] = 0;
        while (i <= Q and S[index(i)] == S[index(i-1)]) {
            Z[index(2)]++;
            i++;
        }
        // check if we can update (left, right)
        if (Z[index(2)] > 0) {
            left = 2;
            right = 2 + Z[index(2)] - 1;
        }
        /**********************************************************/
        for (i = 3; i <= Q; ++i) {
            Z[index(i)] = 0;
            if (right < i) {
                // Compute Z[i] by Direct comparison
                // because we are not within a Z-Box 
                // i.e., right-most Z-box is to left
                // of `i`
                int k = i;
                while (j <= Q and S[index(k)] == S[index(m-i)]) {
                    Z[index(i)]++;
                    k++;
                }
            } else {
		        // beta = len(S[i : right])
                int beta = right - i + 1;
                int j = i - left + 1;
                if (Z[index(j)] < beta) {
                    Z[index(i)] = Z[index(j)];
                } else if (Z[index(j)] > beta) {
                    Z[index(i)] = beta;
                } else {
                    // Compute Z_i(S) by direct character 
                    // comparison from r + 1 
                    // (Z_i(S) is at least β)
                    Z[index(i)] = beta;
                    int k = 1;
                    while (std::max(right+k, beta+k) <= Q and 
                           S[index(right+k)] == S[index(beta+k)]) {
                        Z[index(i)]++;
                        k++;
                    }
                }
            }
            /**************************************************/
            if (Z[index(i)] > 0 and (i + Z[index(i)] - 1) > right) {
                // update (left, right)
                left = i;
                right = i + Z[index(i)] - 1;
            }
            /**************************************************/
        }
        /**********************************************************/
        //std::cout << "Z-Values:" << std::endl << "[";
        for (i = 0; i < M; ++i) {
            //std::cout << Z[i] << ((i < M-1) ? ", " : "");
            if (Z[i+N+1] == N) {
                return i;
            }
        }
        //std::cout << "]" << std::endl;
        /**********************************************************/
        std::cout << "Z-Values for \"" << S << "\" are:" << std::endl;
        std::cout << "[";
        for (int i = 0; i < Q; ++i) {
            std::cout << Z[i] << ((i < M-1) ? ", " : "");
        }
        std::cout << "]" << std::endl;
        return -1;	
    }   
    
public:
    int strStr(string haystack, string needle) {
        return solution2(haystack, needle);
    }
};
