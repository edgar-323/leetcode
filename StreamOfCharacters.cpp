/*
Implement the StreamChecker class as follows:
    1)  StreamChecker(words):    
        Constructor, init the data structure with the given words.
    2)  query(letter):   
        returns true if and only if for some k >= 1, 
        the last k characters queried 
        (in order from oldest to newest, including this letter just queried) 
        spell one of the words in the given list.
 
Example:
StreamChecker streamChecker = new StreamChecker(["cd","f","kl"]); // init the dictionary.
streamChecker.query('a');          // return false
streamChecker.query('b');          // return false
streamChecker.query('c');          // return false
streamChecker.query('d');          // return true, because 'cd' is in the wordlist
streamChecker.query('e');          // return false
streamChecker.query('f');          // return true, because 'f' is in the wordlist
streamChecker.query('g');          // return false
streamChecker.query('h');          // return false
streamChecker.query('i');          // return false
streamChecker.query('j');          // return false
streamChecker.query('k');          // return false
streamChecker.query('l');          // return true, because 'kl' is in the wordlist
 
Note:
1 <= words.length <= 2000
1 <= words[i].length <= 2000
Words will only consist of lowercase English letters.
Queries will only consist of lowercase English letters.
The number of queries is at most 40000.
*/

class Trie {
private:
    static const int ALPH_SZ = 26;
    std::array<Trie*, ALPH_SZ> child;
    bool _is_word;

    int index(const char c) {
        return c - 'a';
    }

    void add(const std::string& word, const int pos) {
        if (pos == word.size()) {
            _is_word = true;
            return;
        }
        const auto i = index(word[pos]);
        if (not child[i]) {
            child[i] = new Trie();
        }
        child[i]->add(word, pos+1);
    }
public:
    Trie() {
        _is_word = false;
        for (int i = 0; i < ALPH_SZ; ++i) {
            child[i] = nullptr;
        }
    }

    ~Trie() {
        _is_word = false;
        for (int i = 0; i < ALPH_SZ; ++i) {
            if (child[i]) {
                delete child[i];
                child[i] = nullptr;
            }
        }
    }

    void add(const std::string& word) {
        add(word, 0);
    }

    Trie* get_child(const char c) {
        return child[index(c)];
    }

    bool is_word() {
        return _is_word;
    }
};

class StreamChecker {
private:
    Trie root;
    std::queue<Trie*> Q;
public:
    StreamChecker(vector<string>& words) {
        for (const auto& word : words) {
            root.add(word);
        }
    }
    
    bool query(char letter) {
        bool answer = false;
        Q.push(&root);
        for (int sz = Q.size(); sz; --sz, Q.pop()) {
            auto node = Q.front();
            node = node->get_child(letter);
            if (node) {
                answer = answer or node->is_word();
                Q.push(node);
            }
        }
        return answer;
    }
};

/**
 * Your StreamChecker object will be instantiated and called as such:
 * StreamChecker* obj = new StreamChecker(words);
 * bool param_1 = obj->query(letter);
 */
