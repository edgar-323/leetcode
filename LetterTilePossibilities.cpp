/*
You have a set of tiles, where each tile has one letter tiles[i] printed on it.  Return the number of possible non-empty sequences of letters you can make.

Example 1:
Input: "AAB"
Output: 8
Explanation: The possible sequences are "A", "B", "AA", "AB", "BA", "AAB", "ABA", "BAA".

Example 2:
Input: "AAABBC"
Output: 188

Note:
1 <= tiles.length <= 7
tiles consists of uppercase English letters.
*/
class Solution {
private:
    static const int ALPH_SZ = 26;
    
    int to_index(const char c) {
        return c - 'A';
    }
    
    char to_char(const int i) {
        return i + 'A';
    }

    void backtrack(const std::string curr, std::vector<int>& anagram, std::unordered_set<std::string>& seen) {
        if (not curr.empty() and not seen.count(curr)) {
            seen.insert(curr);
        }
        for (int i = 0; i < ALPH_SZ; ++i) {
            if (anagram[i]) {
                --anagram[i];
                backtrack(curr + std::string(1, to_char(i)), anagram, seen);
                ++anagram[i];
            }
        }
    }

    int solution1(const std::string& tiles) {
        auto seen = std::unordered_set<std::string>();
        auto anagram = std::vector<int>(ALPH_SZ, 0);
        for (const auto tile : tiles) {
            anagram[to_index(tile)]++;
        }
        backtrack("", anagram, seen);

        return seen.size(); 
    }

public:
    int numTilePossibilities(string tiles) {
        return solution1(tiles);   
    }
};
