/*
Given a 2D board and a list of words from the dictionary, find all words in the board.
Each word must be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

Example:
Input: 
board = [
  ['o','a','a','n'],
  ['e','t','a','e'],
  ['i','h','k','r'],
  ['i','f','l','v']
]
words = ["oath","pea","eat","rain"]
Output: ["eat","oath"]
*/

#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

class Trie {
private:
    static const size_t ALPH_SZ = 26;
    std::string* word;
    Trie** child;

    const size_t index(char c) {
        return c - 'a';
    }

    void insert(const std::string& word, const size_t pos) {
        if (pos >= word.size()) {
            this->word = new std::string(word);
            return;
        }
        const int i = index(word[pos]);
        if (child[i] == NULL) {
            child[i] = new Trie();
        }
        child[i]->insert(word, pos+1);    
    }

    bool isLower(char c) {
        return 'a' <= c and c <= 'z';
    }
public:
    Trie():
        word(NULL)
    {
        child = new Trie*[ALPH_SZ];
        for (size_t i =0; i < ALPH_SZ; ++i) {
            child[i] = NULL;
        }
    }

    ~Trie() {
        clear();        
        delete [] child;
    }
        
    void clear() {
        for (size_t i = 0; i < ALPH_SZ; ++i) {
            if (child[i] != NULL) {
                child[i]->clear();
                delete child[i];
                child[i] = NULL;
            }
        }
        
        if (word != NULL) {
            delete word;
            word = NULL;
        }
    }
    
    void insert(const std::string& word) {
        insert(word, 0);
    }
    
    bool isWord() {
        return word != NULL;
    }

    std::string getWord() {
        return *word;
    }

    bool hasChild(char c) {
        return isLower(c) and child[index(c)] != NULL;
    }

    Trie& getChild(char c) {
        return *child[index(c)];
    }
};

class Solution {
private:
    int M, N;
    Trie root;
    std::unordered_set<std::string> results;
    
    bool valid(int i, int j) {
        return i >= 0 and i < M and j >= 0 and j < N;
    }

    void explore1(std::vector<std::vector<char>>& board, 
                    int i , int j, Trie& trie) {
        if (trie.isWord() and 
            results.count(trie.getWord()) == 0) {
            results.insert(trie.getWord());
        }

        char c = board[i][j];
        board[i][j] = '*';

        // top
        if (valid(i-1, j)) {
            char top = board[i-1][j];
            if (trie.hasChild(top)) {
                explore1(board, i-1, j, trie.getChild(top));
            }
        }
        // bottom 
        if (valid(i+1, j)) {
            char bot = board[i+1][j];
            if (trie.hasChild(bot)) {
                explore1(board, i+1, j, trie.getChild(bot));
            }
        }
        // left 
        if (valid(i, j-1)) {
            char left = board[i][j-1];
            if (trie.hasChild(left)) {
                explore1(board, i, j-1, trie.getChild(left));
            }
        }
        // right  
        if (valid(i, j+1)) {
            char right = board[i][j+1];
            if (trie.hasChild(right)) {
                explore1(board, i, j+1, trie.getChild(right));
            }
        }

        board[i][j] = c;
    }

    std::vector<std::string> solution1(std::vector<std::vector<char>>& board, 
                                        std::vector<std::string>& words) {
        M = board.size();
        if (M == 0) {
          return std::vector<std::string>();
        }
        N = board[0].size();

        root.clear();            
        for (const std::string& word : words) {
            root.insert(word);
        }
        results.clear();
        if (root.isWord()) {
            results.insert("");    
        } 
        for(int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                char c = board[i][j];
                if (root.hasChild(c)) {
                    explore1(board, i, j, root.getChild(c));
                }
            }
        }
             
        return std::vector<std::string>(results.begin(), results.end());
    }
public:
    std::vector<std::string> findWords(std::vector<std::vector<char>>& board, 
                                        std::vector<std::string>& words) {
       return solution1(board, words); 
    }
};

int main(int _, char** __) {
    std::cout << "HELLO WORLD" << std::endl; 
    
    std::vector<std::string> words { "oath","pea","eat","rain" };
    std::vector<std::vector<char>> board { { 'o','a','a','n' },
                                           { 'e','t','a','e' },
                                           { 'i','h','k','r' },
                                           { 'i','f','l','v' } };
    
    Solution solution;
    auto ans = solution.findWords(board, words);

    for (auto& w : ans) {
        std::cout << w << std::endl;
    } 

    return 0;
}
