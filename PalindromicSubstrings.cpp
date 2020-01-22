/*
Given a string, your task is to count how many palindromic substrings in this string.

The substrings with different start indexes or end indexes are counted as different substrings even they consist of same characters.

Example 1:

Input: "abc"
Output: 3
Explanation: Three palindromic strings: "a", "b", "c".
 

Example 2:

Input: "aaa"
Output: 6
Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".
 

Note:

The input string length won't exceed 1000.
*/

class Solution {
private:
    std::string S;
    int N;
    
    int palindromeCount(int left, int right) {
        int count = right;
        while (left >= 0 && right < N && S[left] == S[right]) {
            --left;
            ++right;
        }
        return right - count;
    }
    
    int solution1(std::string& str) {
        /*
        Time-Complexity:    O(N^2)
        Space-Complexity:   O(1)
        */
        
        S = str;
        N = S.size();
        
        int count = 0;
        for (int i = 0; i < N; ++i) {
            count += (1 + 
                      palindromeCount(i-1, i+1) + 
                      palindromeCount(i, i+1));
        }
        
        return count;
    } 
    
    void preprocess(std::string& str) {
        int M = str.size();
        N = 2*M + 3;
        S = std::string(N, '#');
        S[0] = '^';
        for (int i = 0; i < M; ++i) {
            S[2*i + 2] = str[i];
        }
        S[N-1] = '$';
    }
    
    int* manacher_algorithm(std::string& str) {
        /*
        Time-Complexity:    O(M)
        Space-Complexity:   O(M)
            Where: 
                M = size(str)
        */
        preprocess(str);
        int* P = new int[N];
        int center = 0;
        int right = 0;
        int i_mirror;
        P[0] = 0;
        for (int i = 1; i < N-1; ++i) {
            i_mirror = center - (i - center); 
            
            P[i] = (right > i) ? 
                    std::min(right - i, P[i_mirror]) : 
                    0;
            
            // expand around center i
            while (S[i + 1 + P[i]] == S[i - 1 - P[i]]) {
                P[i]++;
            }

            // Update c,r in case if the palindrome centered at i expands past r
            if ( i + P[i] > right ) {
                center = i;
                right = i + P[i];
            }
        }
        P[N-1] = 0;
        return P;
    }
        
    int solution2(std::string& str) {
        /*
        Time-Complexity:    O(N)
        Space-Complexity:   O(N)
        */
        int* P = manacher_algorithm(str);
        int count = 0;
        for (int i = 1; i < N-1; ++i) {
            count += P[i] / 2 + (S[i] != '#');
        }
        delete[] P;
        return count;
    }
    
public:
    int countSubstrings(string s) {
        return solution2(s);
    }
};
