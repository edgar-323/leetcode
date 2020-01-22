/*
Implement a MapSum class with insert, and sum methods.

For the method insert, you'll be given a pair of (string, integer). The string represents the key and the integer represents the value. If the key already existed, then the original key-value pair will be overridden to the new one.

For the method sum, you'll be given a string representing the prefix, and you need to return the sum of all the pairs' value whose key starts with the prefix.

Example 1:
Input: insert("apple", 3), Output: Null
Input: sum("ap"), Output: 3
Input: insert("app", 2), Output: Null
Input: sum("ap"), Output: 5
*/

class Trie {
private:
    static const int ALPH_SZ = 26;
    Trie* child[ALPH_SZ];
    bool is_word;
    int val;

    int index(const char c) {
        return c - 'a';
    }

    void add_word(const std::string& key, const int pos, const int val) {
        if (pos == key.size()) {
            is_word = true;
            this->val = val;
            return;
        }
        const int i = index(key[pos]);
        if (not child[i]) {
            child[i] = new Trie();
        }
        child[i]->add_word(key, pos+1, val);
    }

    int get_prefix_sum(const std::string& key, const int pos) {
        if (pos < key.size()) {
            const int i = index(key[pos]);
            return child[i] ? child[i]->get_prefix_sum(key, pos+1) : 0;
        }
        int sum = is_word ? val : 0;
        for (int i = 0; i < ALPH_SZ; ++i) {
            if (child[i]) {
                sum += child[i]->get_prefix_sum(key, pos);
            }
        }
        return sum;
    }
public:
    Trie() {
        is_word = false;
        for (int i = 0; i < ALPH_SZ; ++i) {
            child[i] = NULL;
        }
    }

    ~Trie() {
        // Note For Self:
        // It is always good practice to clean up resources (especially in C++),
        // however, be aware that leetcode submission will be substantially 
        // slower due to the following clean up sequence.
        for (int i = 0; i < ALPH_SZ; ++i) {
            if (child[i]) {
                delete child[i];
            }
        }
    }

    void add_word(const std::string& key, const int val) {
        add_word(key, 0, val);
    }

    int get_prefix_sum(const std::string& key) {
        return get_prefix_sum(key, 0);
    }
};

class MapSum {
public:
    Trie trie;
    /** Initialize your data structure here. */
    MapSum() {
        // do nothing 
    }
    
    void insert(string key, int val) {
        trie.add_word(key, val);
    }
    
    int sum(string prefix) {
        return trie.get_prefix_sum(prefix);    
    }
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */
