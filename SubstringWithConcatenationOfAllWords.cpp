/*
You are given a string, s, and a list of words, words, that are all of the same length. 
Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.

Example 1:
Input:
  s = "barfoothefoobarman",
  words = ["foo","bar"]
Output: [0,9]
Explanation: Substrings starting at index 0 and 9 are "barfoo" and "foobar" respectively.
The output order does not matter, returning [9,0] is fine too.

Example 2:
Input:
  s = "wordgoodgoodgoodbestword",
  words = ["word","good","best","word"]
Output: []
*/

class Solution {
private:
    static const int ALPH_SZ = 26;

    int index(const char c) {
        return c - 'a';
    }

    std::vector<int> solution1(const std::string& S, std::vector<std::string>& words) {
        /* Time-Complexity:     O(N*K*W)
         * Space-Complexity:    O(K*W)
         *      Where:
         *          N = len(S)
         *          W = len(words)
         *          K = len(words[0]) // length of each word
         */
        if (S.empty() or words.empty()) {
            return {};
        }
        const int N = S.size();
        const int W = words.size();
        const int K = words[0].size();
        if (N < K*W) {
            return {};
        }
        auto freq = std::unordered_map<std::string, int>();
        for (const auto& word : words) {
            freq[word]++;
        }
        auto words_gram = std::vector<int>(ALPH_SZ, 0);
        for (const auto& word : words) {
            for (const auto c : word) {
                words_gram[index(c)]++;
            }
        }
        auto window_gram = std::vector<int>(ALPH_SZ, 0);
        for (int i = 0; i < K*W; ++i) {
            window_gram[index(S[i])]++;
        } 

        auto indices = std::vector<int>();
        
        for (int right = K*W; right <= N; ++right) {
            if (window_gram == words_gram) {
                auto seen = std::unordered_map<std::string, int>();
                auto words_seen = 0;
                for (int left = right - K*W; left < right; left += K, ++words_seen) {
                    auto word = S.substr(left, K);
                    if (not freq.count(word) or seen[word] == freq[word]) {
                        break;
                    }
                    seen[word]++; 
                }
                if (words_seen == W) {
                    indices.push_back(right - K*W);
                }
            }
            --window_gram[index(S[right-K*W])];
            if (right < N) {
                ++window_gram[index(S[right])];
            }
        }
        
        return indices;
    }
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        return solution1(s, words);        
    }
};
