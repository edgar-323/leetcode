/*
Given a 2D board and a word, find if the word exists in the grid.
The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.

Example:
board =
[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]
Given word = "ABCCED", return true.
Given word = "SEE", return true.
Given word = "ABCB", return false.
*/

class Solution {
private:
    int M,N,K;

    bool is_valid(int i, int j) {
        return i >= 0 and i < M and j >= 0 and j < N;
    }
   
    const char mark(char& grid_point) {
        const char c = grid_point;
        grid_point = '*';
        return c;
    }
    
    void unmark(char& grid_point, const char val) {
        grid_point = val;
    }
   
    bool is_marked(const char& grid_point) {
        return grid_point == '*';
    }

    bool found(vector<vector<char>>& board, const int i, const int j, const string& word, const int pos) {
        if (pos >= K) {
            return true;
        }
        if (!is_valid(i, j) || is_marked( board[i][j] ) || board[i][j] != word[pos]) {
            return false;
        }
        const char c = mark( board[i][j] );
        bool ansr = found(board, i-1, j, word, pos+1) ||
                    found(board, i+1, j, word, pos+1) ||
                    found(board, i, j-1, word, pos+1) || 
                    found(board, i, j+1, word, pos+1);
        unmark( board[i][j], c );
        return ansr;
    }
    
    bool solution1(vector<vector<char>>& board, string& word) {
        M = board.size();
        if ( !M ) {
            return false;
        }
        N = board[0].size();
        if ( !N ) {
            return false;
        }
        K = word.size();

        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (found(board, i, j, word, 0)) {
                    return true;
                }
            }
        }

        return false;
    }
public:
    bool exist(vector<vector<char>>& board, string word) {
        return solution1(board, word);
    }
};
