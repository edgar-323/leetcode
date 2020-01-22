/*
Consider the string s to be the infinite wraparound string of "abcdefghijklmnopqrstuvwxyz", so s will look like this: "...zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd....".
Now we have another string p. 
Your job is to find out how many unique non-empty substrings of p are present in s. 
In particular, your input is the string p and you need to output the number of different non-empty substrings of p in the string s.

Note: p consists of only lowercase English letters and the size of p might be over 10000.

Example 1:
Input: "a"
Output: 1
Explanation: Only the substring "a" of string "a" is in the string strings.

Example 2:
Input: "cac"
Output: 2
Explanation: There are two substrings "a", "c" of string "cac" in the string s.

Example 3:
Input: "zab"
Output: 6
Explanation: There are six substrings "z", "a", "b", "za", "ab", "zab" of string "zab" in the string s.
*/

class Solution {
private:
    static const int ALPH_SZ = 26;
	int solution1(const std::string& p) {
        auto DP = std::vector<int>(ALPH_SZ, 0); // DP[letter] = length of longest substring of `p` where `letter` is the last character of the substring
        const int N = p.size();
        int len = 0; // Keep track of current sequence length
        for (int i = 0; i < N; ++i) {
            // if the current letter does not come after the preceding letter
            // then our length goes back to zero
            if (i and not (p[i-1] == 'z' and p[i] == 'a' or p[i] == p[i-1] + 1)) {
                len = 0;
            }
            // can letter at p[i] be end of sequence of greater length? 
            const int index = p[i] - 'a';
            DP[index] = std::max(DP[index], ++len);
        }
        // Why do we return the sum of all letter counts ?
        // Because suppose DP[letter] = k, and suppose letter is the final
        // letter in the given sequence (i.e. DP[letter+1] < k+1).
        // Then, there will be other letter lower than letter who will have counts
        // {k-1, k-2, k-3,...,1} and the length of total substr is k.
        // So this substr contributes to (k choose 2) substrings in `s`.
        // But (k choose 2) is equal ∑ i for i € [1, k] and this is exactly what
        // already exists in DP[] array.
        // So at the end of the day we return sum of this array to achieve the above
        // task for all independent substrings.
        return std::accumulate(DP.begin(), DP.end(), 0);
	}
public:
    int findSubstringInWraproundString(string p) {
  		return solution1(p);      
    }
};
