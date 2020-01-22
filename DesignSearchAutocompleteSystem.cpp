/*
Design a search autocomplete system for a search engine. 
Users may input a sentence (at least one word and end with a special character '#'). 
For each character they type except '#', you need to return the top 3 historical hot sentences 
that have prefix the same as the part of sentence already typed. 

Here are the specific rules:
    1)  The hot degree for a sentence is defined as the number of times a user typed the exactly same sentence before.
    2)  The returned top 3 hot sentences should be sorted by hot degree (The first is the hottest one). 
        If several sentences have the same degree of hot, 
        you need to use ASCII-code order (smaller one appears first).
    3)  If less than 3 hot sentences exist, then just return as many as you can.
    4)  When the input is a special character, it means the sentence ends, and in this case, you need to return an empty list.

Your job is to implement the following functions:

The constructor function:
AutocompleteSystem(String[] sentences, int[] times): This is the constructor. 
The input is historical data. 
Sentences is a string array consists of previously typed sentences. 
Times is the corresponding times a sentence has been typed. 
Your system should record these historical data.

Now, the user wants to input a new sentence. 
The following function will provide the next character the user types:
List<String> input(char c): 
The input c is the next character typed by the user. 
The character will only be lower-case letters ('a' to 'z'), blank space (' ') or a special character ('#'). 
Also, the previously typed sentence should be recorded in your system. 
The output will be the top 3 historical hot sentences that have prefix the same as the part of sentence already typed.
 
Example:
Operation: AutocompleteSystem(["i love you", "island","ironman", "i love leetcode"], [5,3,2,2])
The system have already tracked down the following sentences and their corresponding times:
"i love you" : 5 times
"island" : 3 times
"ironman" : 2 times
"i love leetcode" : 2 times
Now, the user begins another search:

Operation: input('i')
Output: ["i love you", "island","i love leetcode"]
Explanation:
There are four sentences that have prefix "i". Among them, "ironman" and "i love leetcode" have same hot degree. Since ' ' has ASCII code 32 and 'r' has ASCII code 114, "i love leetcode" should be in front of "ironman". Also we only need to output top 3 hot sentences, so "ironman" will be ignored.

Operation: input(' ')
Output: ["i love you","i love leetcode"]
Explanation:
There are only two sentences that have prefix "i ".

Operation: input('a')
Output: []
Explanation:
There are no sentences that have prefix "i a".

Operation: input('#')
Output: []
Explanation:
The user finished the input, the sentence "i a" should be saved as a historical sentence in system. And the following input will be counted as a new search.

 
Note:
The input sentence will always start with a letter and end with '#', and only one blank space will exist between two words.
The number of complete sentences that to be searched won't exceed 100. The length of each sentence including those in the historical data won't exceed 100.
Please use double-quote instead of single-quote when you write test cases even for a character input.
Please remember to RESET your class variables declared in class AutocompleteSystem, as static/class variables are persisted across multiple test cases. Please see here for more details.
*/

class Trie {
public:
    static const int ALPH_SZ = 26 + 1; // {a,...,z,' '}
    Trie* parent;
    std::vector<Trie*> word_nodes;
    std::array<Trie*, ALPH_SZ> child;
    int score;
    std::string word;

    int index(const char c) {
        return  c == ' ' ? ALPH_SZ - 1:
                c - 'a';
    }
    
    char letter(const int i) {
        return  i == ALPH_SZ - 1 ?
                ' ':
                i + 'a';
    }

    void init_params() {
        parent = nullptr;
        word = "";
        score = 0;
        for (int i = 0; i < ALPH_SZ; ++i) {
            child[i] = nullptr;
        }
    }

    Trie(Trie* parent) {
        init_params();
        this->parent = parent;
    }

    Trie* add(const std::string& word, const int pos, const int score) {
        if (pos == word.size()) {
            this->word = word;
            this->score = score;
            word_nodes.push_back(this);
            return this;
        }
        const auto i = index(word[pos]);
        if (not child[i]) {
            child[i] = new Trie(this);
        }
        auto descendant = child[i]->add(word, pos+1, score);
        word_nodes.push_back(descendant);
        return descendant; 
    }
    
    void update_node() {
        if (score++) {
            //This node's ancestor already have it marked
            return;
        }
        auto node = this;
        auto trace = std::string("");
        while (node->parent) {
            auto prev = node;
            node = node->parent;
            for (int i = 0; i < ALPH_SZ; ++i) {
                if (node->child[i] == prev) {
                    trace += letter(i);
                    break;
                }
            }
        }
        word = std::string(trace.rbegin(), trace.rend());
        node = this;
        while (node) {
            node->word_nodes.push_back(this);
            node = node->parent;
        }
    }
public:
    Trie(const std::vector<std::string>& words, const std::vector<int>& times) {
        init_params();
        const int N = words.size();
        for (int i = 0; i < N; ++i) {
            add(words[i], 0, times[i]);
        }
    }

    ~Trie() {
        for (int i = 0; i < ALPH_SZ; ++i) {
            if (child[i]) {
                delete child[i];
            }
        }
    }

    Trie* insert(const char c) {
        if (c == '#') {
            update_node();
            return nullptr;
        }
        const auto i = index(c);
        if (not child[i]) {
            child[i] = new Trie(this);
        }
        return child[i];
    }

    std::vector<std::string> get_top_three() {
        const auto cmp =    [] (Trie* u, Trie* v) -> bool {
                                return u->score == v->score ? u->word < v->word : u->score > v->score;
        };
        auto& results = word_nodes;
        std::sort(results.begin(), results.end(), cmp);
        if (results.empty()) {
            return {};
        } else if (results.size() == 1) {
            return {results[0]->word};
        } else if (results.size() == 2) {
            return {results[0]->word, results[1]->word};
        }
        return {results[0]->word, results[1]->word, results[2]->word};
    }
};

class AutocompleteSystem {
private:
    Trie* root;
    Trie* current_node;
public:
    AutocompleteSystem(vector<string>& sentences, vector<int>& times) {
        root = new Trie(sentences, times);
        current_node = root;
    }
    
    ~AutocompleteSystem() {
        delete root;
    }

    vector<string> input(char c) {
        current_node = current_node->insert(c);
        if (not current_node) {
            current_node = root;
            return {};
        }
        return current_node->get_top_three(); 
    }
};

/**
 * Your AutocompleteSystem object will be instantiated and called as such:
 * AutocompleteSystem* obj = new AutocompleteSystem(sentences, times);
 * vector<string> param_1 = obj->input(c);
 */
