/*
Implement a trie with insert, search, and startsWith methods.

Example:
Trie trie = new Trie();
trie.insert("apple");
trie.search("apple");   // returns true
trie.search("app");     // returns false
trie.startsWith("app"); // returns true
trie.insert("app");   
trie.search("app");     // returns true

Note:
You may assume that all inputs are consist of lowercase letters a-z.
All inputs are guaranteed to be non-empty strings.

*/
class SparseNode {
private:
    const int ALPH_SZ = 26;
    bool isWord;
    SparseNode** chars;
    
    int getIndex(char c) {
        return c-'a';
    }
    
public:
    SparseNode() {
        chars = new SparseNode*[ALPH_SZ];
        for (int i = 0; i < ALPH_SZ; ++i) {
            chars[i] = NULL;
        }
        isWord = false;
    }
    
    void insert(std::string& word, int pos) {
        if (pos >= word.size()) {
            isWord = true;
            return;
        }
        int index = getIndex(word[pos]);
        if (chars[index] == NULL) {
            chars[index] = new SparseNode();
        }
        chars[index]->insert(word, pos+1);
    }
    
    bool search(std::string& word, int pos) {
        if (pos >= word.size()) {
            return isWord;
        } 
        int index = getIndex(word[pos]);
        return (chars[index] == NULL) ? false : 
                chars[index]->search(word, pos+1);
    }
    
    bool startsWith(std::string& word, int pos) {
        if (pos >= word.size()) {
            return true;
        }
        int index = getIndex(word[pos]);
        return (chars[index] == NULL) ? false :
                chars[index]->startsWith(word, pos+1);
    }
};

class PackedNode {
private: 
    bool isWord;
    std::unordered_map<int, PackedNode*> chars;
    
    int getIndex(char c) {
        return c - 'a';
    }
    
    bool contains(int x) {
        return chars.count(x) > 0;
    }
public: 
    PackedNode() {
        isWord = false;
    }
    
    void insert(std::string& word, int pos) {
        if (pos >= word.size()) {
            isWord = true;
            return;
        }
        int index = getIndex(word[pos]);
        if (!contains(index)) {
            chars.emplace(index, new PackedNode());
        }
        chars[index]->insert(word, pos+1);
    }
    
    bool search(std::string& word, int pos) {
        if (pos >= word.size()) {
            return isWord;
        } 
        int index = getIndex(word[pos]);
        return !contains(index) ? false : 
                chars[index]->search(word, pos+1);
    }
    
    bool startsWith(std::string& word, int pos) {
        if (pos >= word.size()) {
            return true;
        }
        int index = getIndex(word[pos]);
        return !contains(index) ? false : 
                chars[index]->startsWith(word, pos+1);
    }
            
};

class Trie {
private: 
    SparseNode* root;
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new SparseNode();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        root->insert(word, 0);
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        return root->search(word, 0);
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        return root->startsWith(prefix, 0);
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie obj = new Trie();
 * obj.insert(word);
 * bool param_2 = obj.search(word);
 * bool param_3 = obj.startsWith(prefix);
 */
