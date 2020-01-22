/*
Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

Example:
Input: S = "ADOBECODEBANC", T = "ABC"
Output: "BANC"

Note:
    1)  If there is no such window in S that covers all characters in T, return the empty string "".
    2)  If there is such window, you are guaranteed that there will always be only one unique minimum window in S.
*/

class Solution {
private:
    bool validWindow(vector<bool>& exists, vector<int>& counter, const int ALPH_SZ) {
        for (int i = 0; i < ALPH_SZ; ++i) {
            if (exists[i] && counter[i] > 0) {
                return false;
            }
        }
        return true;
    }
    
    string mySolution(string& s, string& t) {
        /*
        Time-Complexity:
            (2*ALPH_SZ + 2*ALPH_SZ*S + T)
                ==> O(S + T)
        Space-Complexity:
            (2*ALPH_SZ)
                ==> O(1)
        */
        const int S = s.size();
        const int T = t.size();
        if (S == 0 || T == 0) {
            return "";
        } 
        const int ALPH_SZ = 128;
        vector<int> counter(ALPH_SZ, 0);
        vector<bool> exists(ALPH_SZ, false);
        for (int i = 0; i < T; ++i) {
            ++counter[t[i]];
            exists[t[i]] = true;
        }
        int L = -1;
        int R = -1;
        int left = 0;
        int right = 0;
        int minWin = S+1;
        int len;
        while (left < S) {
            if (validWindow(exists, counter, ALPH_SZ)) {
                len = right - left;
                if (len < minWin) {
                    L = left;
                    R = right;
                    minWin = len;
                }
                ++counter[s[left++]];
                while (left < right && !exists[s[left]]) {
                    ++left;
                }
            } else if (right < S) {
                --counter[s[right++]];
            } else {
                ++counter[s[left++]];
            }
        }
        return (L < 0) ? "" : s.substr(L, R-L);
    }
    
public:
    string minWindow(string s, string t) {
        return mySolution(s, t);
    }
};
