/*
Given a string, find the length of the longest substring without repeating characters.

Example 1:
Input: "abcabcbb"
Output: 3 
Explanation: The answer is "abc", with the length of 3. 

Example 2:
Input: "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Example 3:
Input: "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3. 
             Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
*/

class Solution {
private:
    static const int ALPH_SZ = 128;

    int solution1(const std::string& s) {
        /*
        Time-Complexity:    O(N)
        Space-Complexity:   O(1)
        */
        const int N = s.size();
        if ( !N ) {
            return 0;
        }
        
        int seen[ALPH_SZ]; 
        for (int i = 0; i < ALPH_SZ; ++i) {
            seen[i] = -1;
        }
        
        int globalMax = 0;
        int left = 0; 
        int right = 0;
        for (; right < N; seen[c] = right++) {
            const char& c = s[right];
            if (left <= seen[c]) {
                globalMax = std::max(globalMax, right-left);
                left = seen[c] + 1;
            } 
        }
        return std::max(globalMax, right-left);
    }
public:
    int lengthOfLongestSubstring(string s) {
        return solution1(s);
    }
};
