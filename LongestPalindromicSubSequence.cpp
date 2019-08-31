/*
Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

Example 1:

Input: "babad"
Output: "bab"
Note: "aba" is also a valid answer.
Example 2:

Input: "cbbd"
Output: "bb"
*/

class Solution {
private:
    std::string S;
    int N;
    
    void transform(std::string& str) {
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
        transform(str);
        int* P = new int[N];
        int center = 0;
        int right = 0;
        int i_mirror;
        P[0] = 0;
        for (int i = 1; i < N-1; ++i) {
            i_mirror = 2*center - i;
            P[i] = (right > i) ? 
                    std::min(right - i, P[i_mirror]) : 0;
            while (S[i + 1 + P[i]] == S[i - 1 - P[i]]) {
                P[i]++;
            }
            if (i+P[i] > right) {
                center = i;
                right = i + P[i];
            }
        }
        P[N-1] = 0;
        return P;
    }
    
    int palindromeCount(int left, int right) {
        int count = right;
        while (left >= 0 && right < N && S[left] == S[right]) {
            --left;
            ++right;
        }
        return right - count;
    }
    
    std::string solution1(std::string& str) {
        /*
        Time-Complexity:    O(N^2)
        Space-Complexity:   O(1)
        */
        
        S = str;
        N = S.size();
        
        int len = 0;
        int start = 0;
        int local;
        for (int i = 0; i < N; ++i) {
            local = palindromeCount(i-1, i+1);
            if (2*local+1 > len) {
                len = 2*local+1;
                start = i - local;
            }
            local = palindromeCount(i, i+1);  
            if (2*local > len) {
                len = 2*local;
                start = i+1 - local;
            }
        }
        
        return str.substr(start, len);
    } 
    
    std::string solution2(std::string& str) {
        /*
        Time-Complexity:    O(N)
        Space-Complexity:   O(N)
        */
        
        int* P = manacher_algorithm(str);
        int len = 0;
        int start = 0;
        for (int i = 1; i < N-1; ++i) {
            if (P[i] > len) {
                len = P[i];
                start = (i - P[i] - 1) / 2;
            }
        }
        delete[] P;
        
        return str.substr(start, len);
    }
public:
    string longestPalindrome(string s) {
        return solution2(s);
    }
};
