/*
Given a 2D board containing 'X' and 'O' (the letter O), capture all regions surrounded by 'X'.
A region is captured by flipping all 'O's into 'X's in that surrounded region.

Example:
X X X X
X O O X
X X O X
X O X X

After running your function, the board should be:
X X X X
X X X X
X X X X
X O X X

Explanation:
Surrounded regions shouldn’t be on the border, which means that any 'O' on the border of the board are not flipped to 'X'. 
Any 'O' that is not on the border and it is not connected to an 'O' on the border will be flipped to 'X'. 
Two cells are connected if they are adjacent cells connected horizontally or vertically.

*/

class Solution {
private:
    int M, N;
    static const char X = 'X';
    static const char O = 'O';
    static const char P = 'P'; // In-Progress
    static const char I = 'I'; // Invalid
    bool valid(int i, int j) {
        return i >= 0 and i < M and j >= 0 and j < N;
    }
    bool explore(std::vector<std::vector<char> >& board, int i, int j) {
        if (not valid(i, j) or board[i][j] == I) {
            return false;
        } else if (board[i][j] == X or board[i][j] == P) {
            return true;
        }
        
        board[i][j] = P;
        if (not explore(board, i-1, j) or
            not explore(board, i+1, j) or 
            not explore(board, i, j+1) or 
            not explore(board, i, j-1)) {
            board[i][j] = I;
            return false;
        } else {
            return true;
        }
    }
    void revert(std::vector<std::vector<char> >& board, int i, int j) {
        if (not valid(i, j) or board[i][j] == X or board[i][j] == O) {
            return;
        }
        board[i][j] = O;
        revert(board, i-1, j);
        revert(board, i+1, j);
        revert(board, i, j-1);
        revert(board, i, j+1);
    }
	void solution1(std::vector<std::vector<char> >& board) {
        /* 
         * Time-Complexity:     O(M*N)
         * Space-Complexity:    O(M*N)  // Implicit Stack Space
         *
         * */
        M = board.size();
        if (M == 0) {
            return;
        }
        N = board[0].size();
        int i, j;
        for (i = 0; i < M; ++i) {
            for (j = 0; j < N; ++j) {
                if (board[i][j] == O) {
                    explore(board, i, j);
                }
            }
        }
        for (i = 0; i < M; ++i) {
            for (j = 0; j < N; ++j) {
                if (board[i][j] == I) {
                    revert(board, i, j);
                }
            }
        }
        for (i = 0; i < M; ++i) {
            for (j = 0; j < N; ++j) {
                if (board[i][j] == P) {
                    board[i][j] = X;
                }
            }
        }
    }
public:
    void solve(std::vector<std::vector<char> >& board) {
 		solution1(board);       
    }
};

