/*
Given a list of unique words, find all pairs of distinct indices (i, j) in the given list, so that the concatenation of the two words.
I.e. words[i] + words[j] is a palindrome.

Example 1:
Input: ["abcd","dcba","lls","s","sssll"]
Output: [[0,1],[1,0],[3,2],[2,4]] 
Explanation: The palindromes are ["dcbaabcd","abcddcba","slls","llssssll"]

Example 2:
Input: ["bat","tab","cat"]
Output: [[0,1],[1,0]] 
Explanation: The palindromes are ["battab","tabbat"]
*/
class Trie {
private: 
    static const int ALPH_SZ = 26;
    Trie* child[ALPH_SZ];
    std::vector<int> palindromic_prefixes;
    int word_index;

    bool is_palindrome(const std::string& word, int begin, int end) {
        while (begin < end) {
            if (word[begin++] != word[end--]) {
                return false;
            }
        }
        return true;
    }

    int index(const char c) {
        return c - 'a';
    }

    void add(const std::string& word, const int pos, const int word_index) {
        if (pos == -1) {
            this->word_index = word_index;
            palindromic_prefixes.push_back(word_index);
            return;
        }
        int i = index(word[pos]);
        if (not child[i]) {
            child[i] = new Trie();
        }
        child[i]->add(word, pos-1, word_index);
		if (is_palindrome(word, 0, pos)) {
            palindromic_prefixes.push_back(word_index);      
        }
    }

    void search(const std::string& word, const int pos, const int word_index, std::vector<std::vector<int>>& results) {
        if (pos == word.size()) {
            for (const auto index : palindromic_prefixes) {
                if (index != word_index) {
                    results.push_back(std::vector<int>{word_index, index});
                }
            }
            return;
        }
        const int i = index(word[pos]);
        if (child[i]) {
            child[i]->search(word, pos+1, word_index, results);    
        }
        if (this->word_index >= 0 and is_palindrome(word, pos, word.size()-1)) {
            results.push_back(std::vector<int>({word_index, this->word_index}));
        }
    }
public:
    Trie() {
        word_index = -1;
        for (int i = 0; i < ALPH_SZ; ++i) {
            child[i] = NULL;
        }
    }

    ~Trie() {
        word_index = -1;
        for (int i = 0; i < ALPH_SZ; ++i) {
            if (child[i]) {
                delete child[i];
                child[i] = NULL;
            }
        }
    }

    void add(const std::string& word, const int i) {
        add(word, word.size() - 1, i);
    }
    
    void search(const std::string& word, const int i, std::vector<std::vector<int>>& results) {
        search(word, 0, i, results);
    }
};

class Solution {
private:
    std::vector<std::vector<int>> solution1(const std::vector<std::string>& words) {
        const int W = words.size();
        auto trie = Trie();
        for (int i = 0; i < W; ++i) {
            trie.add(words[i], i);
        }
        auto results = std::vector<std::vector<int>>();
        for (int i = 0; i < W; ++i) {
            trie.search(words[i], i, results);
        }
        return results;
    }
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        return solution1(words);       
    }
};
