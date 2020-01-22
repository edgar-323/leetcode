/*
A query word matches a given pattern if we can insert lowercase letters to the pattern word so that it equals the query. (We may insert each character at any position, and may insert 0 characters.)
Given a list of queries, and a pattern, return an answer list of booleans, where answer[i] is true if and only if queries[i] matches the pattern.

Example 1:
Input: queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FB"
Output: [true,false,true,true,false]
Explanation: 
"FooBar" can be generated like this "F" + "oo" + "B" + "ar".
"FootBall" can be generated like this "F" + "oot" + "B" + "all".
"FrameBuffer" can be generated like this "F" + "rame" + "B" + "uffer".

Example 2:
Input: queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FoBa"
Output: [true,false,true,false,false]
Explanation: 
"FooBar" can be generated like this "Fo" + "o" + "Ba" + "r".
"FootBall" can be generated like this "Fo" + "ot" + "Ba" + "ll".

Example 3:
Input: queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FoBaT"
Output: [false,true,false,false,false]
Explanation: 
"FooBarTest" can be generated like this "Fo" + "o" + "Ba" + "r" + "T" + "est".

Note:
1 <= queries.length <= 100
1 <= queries[i].length <= 100
1 <= pattern.length <= 100
All strings consists only of lower and upper case English letters.
*/
class Trie {
private:
    static const int ALPH_SZ = 2 * 26; 
    Trie* child[ALPH_SZ];
    int query_index; // if this node is the end of some query (ie, if is_word is true), then this will be the corresponding index


    int index(const char c) {
        return  'A' <= c and c <= 'Z' ?
                c - 'A' :
                (c - 'a') + ('Z' - 'A') + 1; 
    }

    void add_word(const std::string& word, const int pos, const int query_index) {
        if (pos == word.size()) {
            this->query_index = query_index;
            return;
        }
        
        const int i = index(word[pos]);
        if (not child[i]) {
            child[i] = new Trie();
        } 
        
        child[i]->add_word(word, pos+1, query_index);       
    }

    void pattern_search(const std::string& pattern, const int pos, std::vector<bool>& can_camel_match) {
        if (pos == pattern.size()) {
            if (query_index >= 0) {
                can_camel_match[query_index] = true;
            }
        } else if (child[index(pattern[pos])]) {
            child[index(pattern[pos])]->pattern_search(pattern, pos+1, can_camel_match);
        }
        for (char c = 'a'; c <= 'z'; ++c) {
            const int i = index(c);
            if (child[i]) {
                child[i]->pattern_search(pattern, pos, can_camel_match);
            }
        }
    }
     
public:
    Trie() {
        query_index = -1;
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

    void add_word(const std::string& word, const int query_index) {
        add_word(word, 0, query_index);
    }

    void pattern_search(const std::string& pattern, std::vector<bool>& can_camel_match) {
        pattern_search(pattern, 0, can_camel_match);
    }

};

class Solution {
private:

    std::vector<bool> solution1(const std::vector<std::string>& queries, const std::string& pattern) {
        auto trie = Trie();

        const int N = queries.size();
        for (int i = 0; i < N; ++i) {
            trie.add_word(queries[i], i);
        } 
        
        auto can_camel_match = std::vector<bool>(N, false);
        trie.pattern_search(pattern, can_camel_match);

        return can_camel_match;
    }

public:
    vector<bool> camelMatch(vector<string>& queries, string pattern) {
        return solution1(queries, pattern);        
    }
};
