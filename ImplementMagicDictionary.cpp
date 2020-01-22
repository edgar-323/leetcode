/*
Implement a magic directory with buildDict, and search methods.
For the method buildDict, you'll be given a list of non-repetitive words to build a dictionary.
For the method search, you'll be given a word, and judge whether if you modify exactly one character into another character in this word, the modified word is in the dictionary you just built.

Example 1:
Input: buildDict(["hello", "leetcode"]), Output: Null
Input: search("hello"), Output: False
Input: search("hhllo"), Output: True
Input: search("hell"), Output: False
Input: search("leetcoded"), Output: False

Note:
You may assume that all the inputs are consist of lowercase letters a-z.
For contest purpose, the test data is rather small by now. You could think about highly efficient algorithm after the contest.
Please remember to RESET your class variables declared in class MagicDictionary, as static/class variables are persisted across multiple test cases. Please see here for more details.
*/

class Trie {
private:
    static const int ALPH_SZ = 26;
    Trie* child[ALPH_SZ];
    bool is_word;

    int index(const char c) {
        return c - 'a';
    }

    void add_word(const std::string& word, const int pos) {
        if (pos == word.size()) {
            is_word = true;
            return;
        }
        const int i = index(word[pos]);
        if (not child[i]) {
            child[i] = new Trie();
        }
        child[i]->add_word(word, pos+1);
    }

    bool search(const std::string& word, const int pos, const bool has_inverted_char) {
        if (pos == word.size()) {
            return is_word and has_inverted_char;
        } else if (has_inverted_char) {
            const int i = index(word[pos]);
            return child[i] ? child[i]->search(word, pos+1, true) : false;  
        } else {
            const int i = index(word[pos]);
            for (int j = 0; j < ALPH_SZ; ++j) {
                if (child[j]) {
                    if (child[j]->search(word, pos+1, i != j)) {
                        return true;
                    }
                }
            }
            return false;
        }
    }
public:
    Trie() {
        is_word = false;
        for (int i = 0; i < ALPH_SZ; ++i) {
            child[i] = NULL;
        }
    }

    ~Trie() {
        clear();
    }

    void clear() {
        for (int i = 0; i < ALPH_SZ; ++i) {
            if (child[i]) {
                delete child[i];
            }
            child[i] = NULL;
        }
        is_word = false;
    }

    void add_word(const std::string& word) {
        add_word(word, 0);
    }

    bool search(const std::string& word) {
        return search(word, 0, false);
    }

};

class MagicDictionary {
public:
    Trie trie;
    /** Initialize your data structure here. */
    MagicDictionary() {
        
    }
    
    /** Build a dictionary through a list of words */
    void buildDict(vector<string> dict) {
        trie.clear();
        for (const auto& word : dict) {
            trie.add_word(word);
        } 
    }
    
    /** Returns if there is any word in the trie that equals to the given word after modifying exactly one character */
    bool search(string word) {
        return trie.search(word); 
    }
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dict);
 * bool param_2 = obj->search(word);
 */
