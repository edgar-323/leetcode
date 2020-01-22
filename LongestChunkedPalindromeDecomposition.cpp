/*
Return the largest possible k such that there exists a_1, a_2, ..., a_k such that:
Each a_i is a non-empty string;
Their concatenation a_1 + a_2 + ... + a_k is equal to text;
For all 1 <= i <= k,  a_i = a_{k+1 - i}.

Example 1:
Input: text = "ghiabcdefhelloadamhelloabcdefghi"
Output: 7
Explanation: We can split the string on "(ghi)(abcdef)(hello)(adam)(hello)(abcdef)(ghi)".

Example 2:
Input: text = "merchant"
Output: 1
Explanation: We can split the string on "(merchant)".

Example 3:
Input: text = "antaprezatepzapreanta"
Output: 11
Explanation: We can split the string on "(a)(nt)(a)(pre)(za)(tpe)(za)(pre)(a)(nt)(a)".

Example 4:
Input: text = "aaa"
Output: 3
Explanation: We can split the string on "(a)(a)(a)".

Constraints:
text consists only of lowercase English characters.
1 <= text.length <= 1000
*/

class Solution {
private:
    static const int ALPH_SZ = 26;
    int index(const char c) {
        return int(c - 'a');
    }

    void reset_hash(std::vector<int>& hash) {
        std::fill(std::begin(hash), std::end(hash), 0);
    }

	int solution1(const std::string& text) {
        /* Time-Complexity:     O(ALPH_SZ * N)
         * Space-Complexity:    O(ALPH_SZ)
         *
         * Since, in our case, ALPH_SZ is constant, our time-complexity reduces to O(N)
         * while our space-complexity reduces to O(1).
         */
        const int N = text.size();
        if (N == 1) {
            return 1;
        }
        int longest_decomp = 0;
        auto left_hash  = std::vector<int>(ALPH_SZ, 0);
        auto right_hash = std::vector<int>(ALPH_SZ, 0); 
        int L = 0;
        int R = N;
        for (int left = 0, right = N-1; left < right; ++left, --right) {
            ++left_hash[index(text[left])];
            ++right_hash[index(text[right])];
            if (left_hash == right_hash) {
                ++longest_decomp;
                reset_hash(left_hash);
                reset_hash(right_hash);
                L = left;
                R = right;
            }
        }
        
        return 2 * longest_decomp + (R - L > 1);
	}
public:
    int longestDecomposition(string text) {
  		return solution1(text);      
    }
};
