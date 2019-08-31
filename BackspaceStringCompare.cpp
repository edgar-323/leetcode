/*
Given two strings S and T, return if they are equal when both are typed into empty text editors. # means a backspace character.

Example 1:

Input: S = "ab#c", T = "ad#c"
Output: true
Explanation: Both S and T become "ac".
Example 2:

Input: S = "ab##", T = "c#d#"
Output: true
Explanation: Both S and T become "".
Example 3:

Input: S = "a##c", T = "#a#c"
Output: true
Explanation: Both S and T become "c".
Example 4:

Input: S = "a#c", T = "b"
Output: false
Explanation: S becomes "c" while T becomes "b".
Note:

1 <= S.length <= 200
1 <= T.length <= 200
S and T only contain lowercase letters and '#' characters.
Follow up:

Can you solve it in O(N) time and O(1) space?
*/

class Solution {
private:
    bool solution1(const std::string& s, const std::string& t) {
        /* Time-Complexity:     O( S + T )
         * Space-Complexity:    O(   1   )
         * */
        const int S = s.size();
        const int T = t.size();

        int i = S-1;
        int j = T-1;
        int deleted;

        while (i >= 0 and j >= 0) {
            deleted = 0; 
            while (i >= 0 and (s[i] == '#' or deleted)) {
                deleted = s[i--] == '#' ? deleted + 1 : deleted - 1;
            }
            deleted = 0;
            while (j >= 0 and (t[j] == '#' or deleted)) {
                deleted = t[j--] == '#' ? deleted + 1 : deleted - 1;
            }
            if (i >= 0 and j >= 0) {
                // At this point we are certain characters s[i] and t[j]
                // have not been deleted and can be compared.
                if (s[i--] != t[j--]) {
                    return false;
                }
            }
        }
        // At this point at least one of the strings is empty.
        // We still have to check that the non-empty string (if it exists) is entirely deleted.
        deleted = 0; 
        while (i >= 0 and (s[i] == '#' or deleted)) {
            deleted = s[i--] == '#' ? deleted + 1 : deleted - 1;
        }
        deleted = 0;
        while (j >= 0 and (t[j] == '#' or deleted)) {
            deleted = t[j--] == '#' ? deleted + 1 : deleted - 1;
        }

        // By this point, both string should be empty.
        return i < 0 and j < 0;
    }	
public:
    bool backspaceCompare(string S, string T) {
        return solution1( S, T ); 
    }
};
