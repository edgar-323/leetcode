/*
Given a string, find the length of the longest substring T that contains at most k distinct characters.

Example 1:
Input: s = "eceba", k = 2
Output: 3
Explanation: T is "ece" which its length is 3.

Example 2:
Input: s = "aa", k = 1
Output: 2
Explanation: T is "aa" which its length is 2.
*/

class Solution {
private:
    static const int ALPH_SZ = 256; 

    int solution1(const std::string& S, const int K) {
        const int N = S.size();
        auto count = std::vector<int>(ALPH_SZ, 0);
        int results = 0;
        int distinct = 0;
        int left, right;
        for (left = 0, right = 0; right < N; ++right) {
            if (not count[S[right]]++) {
                ++distinct;
            }
            if (distinct > K) {
                results = std::max(right - left, results);
            }
            while (distinct > K) {
                if (not --count[S[left++]]) {
                    --distinct;
                }
            }
        }
        results = std::max(results, right - left);

        return results;
    }
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        return solution1(s, k);        
    }
};
