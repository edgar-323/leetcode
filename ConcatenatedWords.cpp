/*
Given a list of words (without duplicates), please write a program that returns all concatenated words in the given list of words.
A concatenated word is defined as a string that is comprised entirely of at least two shorter words in the given array.

Example:
Input: ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]
Explanation: "catsdogcats" can be concatenated by "cats", "dog" and "cats"; 
 "dogcatsdog" can be concatenated by "dog", "cats" and "dog"; 
"ratcatdogcat" can be concatenated by "rat", "cat", "dog" and "cat".

Note:
The number of elements of the given array will not exceed 10,000
The length sum of elements in the given array will not exceed 600,000.
All the input string will only include lower case letters.
The returned elements order does not matter.
*/

class Trie {
private:
    static const int ALPH_SZ = 26;
    Trie* child[ALPH_SZ];
    bool is_word;

    int index(const char c) {
        return int(c - 'a');
    }

    void add(const std::string& word, const int pos) {
        if (pos == word.size()) {
            is_word = true;
            return;
        }
        const int i = index(word[pos]);
        if (not child[i]) {
            child[i] = new Trie();
        }
        child[i]->add(word, pos+1);
    }

    bool has_word(const std::string& word, const int pos, const bool matched_prefix, Trie* root) {
        if (pos == word.size()) {
            return is_word and matched_prefix;
        } else if (is_word and root->has_word(word, pos, true, root)) {
            return true;
        }

        const int i = index(word[pos]);
        if (not child[i]) {
            return false;
        }
        
        return child[i]->has_word(word, pos+1, matched_prefix, root);
    }

public:
    Trie() {
        is_word = false;
        for (int i = 0; i < ALPH_SZ; ++i) {
            child[i] = NULL;
        }
    }

    ~Trie() {
        for (int i = 0; i < ALPH_SZ; ++i) {
            if (child[i]) {
                delete child[i];
            }
        }
    }

    void add(const std::string& word) {
        this->add(word, 0);
    }

    bool has_word(const std::string& word) {
        return this->has_word(word, 0, false, this);
    }
};

class Solution {
private:
    /******************************************************************************************************************************/
    bool is_prefix(const std::string& s, const std::string& t, const int k) {
        // return true if `t` is a prefix of `s[k:]`
        const int N = t.size();
        for (int i = 0; i < N; ++i) {
            if (s[i+k] != t[i]) {
                return false;
            }
        }
        return true;
    }
    void populate(const int i, std::vector<std::vector<std::vector<int>>>& DP1, const std::vector<std::string>& words) {
        const int L = words.size();
        const int M = words[i].size();
        for (int j = 0; j < L; ++j) {
            if (j == i) {
                continue;
            }
            const int N = words[j].size();
            if (not N) {
                continue;
            }
            for (int k = 0; k <= M - N; ++k) {
                if (is_prefix(words[i], words[j], k)) {
                    DP1[i][k].push_back(j);
                }
            }
        }
    }
    std::vector<std::string> solution1(const std::vector<std::string>& words) {
        /* Time-Complexity:     O(∑∑(si*sj))
         * Space-Complexity:    O(∑∑(si*sj))
         *      where si = words[i].size()
         *
         * TIME-LIMIT-EXCEEDED
         */
        // O(∑∑(si*sj))
        const int L = words.size();
        auto DP1 = std::vector<std::vector<std::vector<int>>>(L);
        for (int i = 0; i < L; ++i) {
            const int M = words[i].size();
            if (not M) {
                continue;
            }
            DP1[i] = std::vector<std::vector<int>>(M);
            populate(i, DP1, words);
        }
        auto output = std::vector<std::string>();
        // O(∑(si))
        auto DP2 = std::vector<std::vector<bool>>(L);
        for (int i = 0; i < L; ++i) {
            const int M = words[i].size();
            if (not M) {
                continue;
            }
            DP2[i] = std::vector<bool>(M+1, false);
            DP2[i][M] = true;
            for (int k = M-1; k >= 0; --k) {
                for (const auto j : DP1[i][k]) {
                    DP2[i][k] = DP2[i][k] or DP2[i][k + words[j].size()]; 
                }
            }
            if (DP2[i][0]) {
                output.push_back(words[i]);
            }
        }
         
        return output;
    }
    /******************************************************************************************************************************/
    std::vector<std::string> solution2(const std::vector<std::string>& words) {
        // TRIE SOLUTION
        // It is hard for me to calculate the runtime of Trie.has_word() due to how it works.
        // If we are searching for `word` in the trie, and if we find a prefix match the kth position,
        // then we restart the search with `word[k:]`
        auto trie = Trie(); 
        for (const auto& word : words) {
            if (not word.empty()) {
                trie.add(word);
            }
        }
        auto output = std::vector<std::string>();
        for (const auto& word : words) {
            if (trie.has_word(word)) {
                output.push_back(word);
            }
        }

        return output;
    }
    /******************************************************************************************************************************/
    std::vector<int> get_Z_array(const std::string& str) {
        const int N = str.size();
        auto Z = std::vector<int>(N, 0);

        int L, R, k;
        L = R = 0;
        for (int i = 1; i < N; ++i) {
            if (i > R) {
                L = R = i;
                while (R < N and str[R-L] == str[R]) {
                    ++R;
                }
                Z[i] = R-L;
                --R;
            } else {
                k = i-L;
                if (Z[k] < R-i+1) {
                    Z[i] = Z[k];
                } else {
                    L = i;
                    while (R < N and str[R-L] == str[R]) {
                        ++R;
                    }
                    Z[i] = R-L;
                    --R;
                }
            }
        }
        
        return Z;  
    }
    std::vector<std::string> solution3(const std::vector<std::string>& words) {
        // O(∑∑(si + sj))
        const int W = words.size();
        auto DP1 = std::vector<std::vector<std::vector<int>>>(W);
        for (int i = 0; i < W; ++i) {
            const auto& text = words[i];
            if (text.empty()) {
                continue;
            }
            const int M = text.size();
            DP1[i] = std::vector<std::vector<int>>(M);
            for (int j = 0; j < W; ++j) {
                if (i == j or words[j].empty()) {
                    continue;
                }
                const auto& pattern = words[j];
                const int N = pattern.size(); 
                const auto Z = get_Z_array(pattern + "$" + text);
                const int K = Z.size();
                for (int k = 0; k < K; ++k) {
                    if (Z[k] == N) {
                        DP1[i][k - N - 1].push_back(j);
                    }
                }
            }
        }

		auto output = std::vector<std::string>();
        // O(∑(si))
        auto DP2 = std::vector<std::vector<bool>>(W);
        for (int i = 0; i < W; ++i) {
            if (words[i].empty()) {
                continue;
            }
            const int M = words[i].size();
            DP2[i] = std::vector<bool>(M+1, false);
            DP2[i][M] = true; 
            for (int k = M-1; k >= 0; --k) {
                for (const auto j : DP1[i][k]) {
                    DP2[i][k] = DP2[i][k] or DP2[i][k + words[j].size()];
                }
            }
            if (DP2[i][0]) {
                output.push_back(words[i]);
            }
        }

        return output;
    }
    /******************************************************************************************************************************/
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
  		return solution3(words);      
    }
};
