/*
Given a string s and a string t, check if s is subsequence of t.
You may assume that there is only lower case English letters in both s and t. 
t is potentially a very long (length ~= 500,000) string, and s is a short string (<=100).

A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. 
(ie, "ace" is a subsequence of "abcde" while "aec" is not).

Example 1:
s = "abc", t = "ahbgdc"
Return true.

Example 2:
s = "axc", t = "ahbgdc"
Return false.

Follow up:
If there are lots of incoming S, say S1, S2, ... , Sk where k >= 1B, and you want to check one by one to see if T has its subsequence. In this scenario, how would you change your code?
*/

class Solution {
private:
    /*******************************************************************/
	bool solution1(const std::string& s, const std::string& t) {
        /* Time-Complexity:     O(max{M,N})
         * Space-Complexity:    O(   1    )
         * */
        const int M = s.size();
        const int N = t.size();
        
        int i = 0;
        int j = 0;
         
        while (i < M and j < N and (N-i) <= (M-j)) {
            if (s[i] == t[j++]) {
                ++i;
            }
        }

        return i >= M;
	}
    /*******************************************************************/
public:
    bool isSubsequence(string s, string t) {
		return solution1(s, t);        
    }
};
