/*
Design a data structure that supports the following two operations:

void addWord(word)
bool search(word)
search(word) can search a literal word or a regular expression string containing only letters a-z or .. A . means it can represent any one letter.

Example:

addWord("bad")
addWord("dad")
addWord("mad")
search("pad") -> false
search("bad") -> true
search(".ad") -> true
search("b..") -> true
Note:
You may assume that all words are consist of lowercase letters a-z.
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

    bool search(const std::string& word, const int pos) {
        if (pos == word.size()) {
            return is_word;
        } else if (word[pos] != '.') {
            const int i = index(word[pos]);
            return child[i] and child[i]->search(word, pos+1);
        }
        
        for (int i = 0; i < ALPH_SZ; ++i) {
            if (child[i] and child[i]->search(word, pos+1)) {
                return true;
            }
        }

        return false;
    }
        
public:
    Trie() {
        for (int i = 0; i < ALPH_SZ; ++i) {
            child[i] = NULL;
        }
        is_word = false;
    }

    ~Trie() {
        for (int i = 0; i < ALPH_SZ; ++i) {
            if (child[i]) {
                delete child[i];
            }
        }
    }

    void add_word(const std::string& word) {
        add_word(word, 0);
    }

    bool search(const std::string& word) {
        return search(word, 0); 
    }
};

class WordDictionary {
public:
    Trie root;
    /** Initialize your data structure here. */
    WordDictionary() {}
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        root.add_word(word);
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        return root.search(word);
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
