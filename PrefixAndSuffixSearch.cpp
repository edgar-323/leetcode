/*
Given many words, words[i] has weight i.
Design a class WordFilter that supports one function, WordFilter.f(String prefix, String suffix). 
It will return the word with given prefix and suffix with maximum weight. 
If no word exists, return -1.

Examples:
Input:
WordFilter(["apple"])
WordFilter.f("a", "e") // returns 0
WordFilter.f("b", "") // returns -1

Note:
words has length in range [1, 15000].
For each test case, up to words.length queries WordFilter.f may be made.
words[i] has length in range [1, 10].
prefix, suffix have lengths in range [0, 10].
words[i] and prefix, suffix queries consist of lowercase letters only.
*/
class Trie {
private:
    static const int ALPH_SZ = 26;
    Trie* child[ALPH_SZ+1];
    int weight;

    int index(const char c) {
        return c == '$' ? ALPH_SZ : c - 'a';
    }

    void add(const std::string& word, const int pos, const int weight) {
        if (pos == word.size()) {
            this->weight = weight;
            return;
        }
        const int i = index(word[pos]);
        if (not child[i]) {
            child[i] = new Trie();
        }
        child[i]->add(word, pos+1, weight);
    }

    int search(const std::string& word, const int pos) {
        if (pos == word.size()) {
            int max_weight = weight;
            for (int i = 0; i <= ALPH_SZ; ++i) {
                if (child[i]) {
                    max_weight = std::max(max_weight, child[i]->search(word, pos));    
                }
            }
            return max_weight;
        }
        const int i = index(word[pos]);
        return child[i] ? child[i]->search(word, pos+1) : -1;
    }
public:
    Trie() {
        weight = -1;
        for (int i = 0; i <= ALPH_SZ; ++i) {
            child[i] = NULL;
        }
    }

    ~Trie() {
        clear();
    }
	
	void clear() {
		weight = -1; 
        for (int i = 0; i <= ALPH_SZ; ++i) {
            if (child[i]) {
                delete child[i];
                child[i] = NULL;
            }
        }
	}

    void add(const std::string& word, const int weight) {
        add(word, 0, weight);
    }

    int search(const std::string& word) {
        return search(word, 0);
    }
};
class WordFilter {
private:
    Trie trie;
public:
    WordFilter(vector<string>& words) {
        trie.clear();
        const int W = words.size();
        for (int weight = 0; weight < W; ++weight) {
            const auto& word = words[weight];
            auto suffix = std::string(""); suffix.reserve(word.size());
            trie.add(suffix + "$" + word, weight);
            for (int i = word.size()-1; i >= 0; --i) {
                suffix = std::string(1, word[i]) + suffix;
                trie.add(suffix + "$" + word, weight);
            }
        }
    }
    
    int f(string prefix, string suffix) {
        return trie.search(suffix + "$" + prefix); 
    }
};

/**
 * Your WordFilter object will be instantiated and called as such:
 * WordFilter* obj = new WordFilter(words);
 * int param_1 = obj->f(prefix,suffix);
 */
