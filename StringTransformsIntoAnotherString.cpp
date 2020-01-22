/*
Given two strings str1 and str2 of the same length, determine whether you can transform str1 into str2 by doing zero or more conversions.
In one conversion you can convert all occurrences of one character in str1 to any other lowercase English character.
Return true if and only if you can transform str1 into str2.

Example 1:
Input: str1 = "aabcc", str2 = "ccdee"
Output: true
Explanation: Convert 'c' to 'e' then 'b' to 'd' then 'a' to 'c'. Note that the order of conversions matter.

Example 2:
Input: str1 = "leetcode", str2 = "codeleet"
Output: false
Explanation: There is no way to transform str1 to str2.

Note:
1 <= str1.length == str2.length <= 10^4
Both str1 and str2 contain only lowercase English letters.
*/
class Solution {
private:
    static const int ALPH_SZ = 26;

    int index(const char c) {
        return c - 'a';
    }

	bool solution1(const std::string& S, const std::string& T) {
        if (S == T) {
            return true;
        }
        const int N = S.size();
        auto assignment = std::vector<int>(ALPH_SZ, -1);
        for (int i = 0; i < N; ++i) {
            const auto c1 = index(S[i]);
            const auto c2 = index(T[i]);
            if (assignment[c1] != -1 and assignment[c1] != c2) {
                return false;
            }
            assignment[c1] = c2;
        }
        auto seen = std::vector<bool>(ALPH_SZ, false);
        auto cnt = 0;
        for (const auto& c : T) {
            const auto i = index(c);
            if (not seen[i]) {
                ++cnt;
            }
            seen[i] = true;
        }

        return cnt < ALPH_SZ;
	}
public:
    bool canConvert(string str1, string str2) {
 		return solution1(str1, str2);
    }
};
