/*
Given a string S, count the number of distinct, non-empty subsequences of S .
Since the result may be large, return the answer modulo 10^9 + 7.

Example 1:

Input: "abc"
Output: 7
Explanation: The 7 distinct subsequences are "a", "b", "c", "ab", "ac", "bc", and "abc".
Example 2:

Input: "aba"
Output: 6
Explanation: The 6 distinct subsequences are "a", "b", "ab", "ba", "aa" and "aba".
Example 3:

Input: "aaa"
Output: 3
Explanation: The 3 distinct subsequences are "a", "aa" and "aaa".

Note:
S contains only lowercase letters.
1 <= S.length <= 2000
*/

class Solution {
private:
    static const int ALPH_SZ = 26;
    static const int MOD_VAL = 1e9 + 7;
    int index(const char c) {
        return int(c - 'a');
    }
    /******************************************************************************************************************************/
	int solution1(const std::string& S) {
		/*
            EXPLANATION (Intuition and Algorithm):
            Even though the final code for this problem is very short, it is not very intuitive to find the answer. 
            In the solution below, we'll focus on finding all subsequences (including empty ones), and subtract the empty subsequence at the end.

            Let's try for a dynamic programming solution. 
            In order to not repeat work, our goal is to phrase the current problem in terms of the answer to previous problems. 
            A typical idea will be to try to count the number of states dp[k] (distinct subsequences) that use letters S[0], S[1], ..., S[k].

            Naively, for say, S = "abcx", we have dp[k] = dp[k-1] * 2. 
            This is because for dp[2] which counts ("", "a", "b", "c", "ab", "ac", "bc", "abc"), dp[3] counts all of those, plus all of those with the x ending, like ("x", "ax", "bx", "cx", "abx", "acx", "bcx", "abcx").

            However, for something like S = "abab", let's play around with it. We have:

            dp[0] = 2, as it counts ("", "a")
            dp[1] = 4, as it counts ("", "a", "b", "ab");
            dp[2] = 7 as it counts ("", "a", "b", "aa", "ab", "ba", "aba");
            dp[3] = 12, as it counts ("", "a", "b", "aa", "ab", "ba", "bb", "aab", "aba", "abb", "bab", "abab").
            
            We have that dp[3] counts dp[2], plus ("b", "aa", "ab", "ba", "aba") with "b" added to it. 
            Notice that("", "a")are missing from this list, as they get double counted. 
            In general, the sequences that resulted from putting "b" the last time (ie."b", "ab"`) will get double counted.

            This insight leads to the recurrence:

            dp[k] = 2 * dp[k-1] - dp[last[S[k]] - 1]

            The number of distinct subsequences ending at S[k], is twice the distinct subsequences counted by dp[k-1] (all of them, plus all of them with S[k] appended), minus the amount we double counted, which is dp[last[S[k]] - 1].
		*/
        const int N = S.size();
        // DP[k] = # of distinct subsequences in S[0:k] (including the empty string)
        auto DP = std::vector<int>(N+1);
        // last[x] = index i € [0, N] where character x LAST appeared while we were populating DP[]
        // initially last[x] = -1 since we have yet to see x
        auto last = std::vector<int>(ALPH_SZ, -1);
        DP[0] = 1; // DP[0] accounts for {""} 
        for (int k = 0; k < N; ++k) {
            const int x = index(S[k]);
            DP[k+1] = (2*DP[k] - (last[x] >= 0 ? DP[last[x]] : 0)) % MOD_VAL;
            last[x] = k;
        }
        if (DP[N] < 0) {
            DP[N] += MOD_VAL;
        }
        return DP[N] - 1;
	}
    /******************************************************************************************************************************/
    int solution2(const std::string& S) {
		/*
			Explanation

			Init an array endswith[26]
			endswith[i] to count how many sub sequence that ends with ith character.

			Now we have N = sum(endswith) different sub sequence,
			add a new character c to each of them,
			then we have N different sub sequence that ends with c.

			With this idea, we loop on the whole string S,
			and we update end[c] = sum(end) + 1 for each character.

			We need to plus one here, because "c" itself is also a sub sequence.

			Example

			Input: "aba"
			Current parsed: "ab"

			endswith 'a': ["a"]
			endswith 'b': ["ab","b"]

			"a" -> "aa"
			"ab" -> "aba"
			"b" -> "ba"
			"" -> "a"

			endswith 'a': ["aa","aba","ba","a"]
			endswith 'b': ["ab","b"]
			result: 6

			Complexity

			Time O(26N), Space O(1).
		*/
        long endsWith[26] = {}, mod = 1e9 + 7;
        for (char c : S)
            endsWith[c - 'a'] = accumulate(begin(endsWith), end(endsWith), 1L) % mod;
        return accumulate(begin(endsWith), end(endsWith), 0L) % mod;
    }
    /******************************************************************************************************************************/
public:
    int distinctSubseqII(string S) {
  		return solution1(S);      
    }
};
