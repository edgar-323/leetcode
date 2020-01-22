/*
Write a program to solve a Sudoku puzzle by filling the empty cells.

A sudoku solution must satisfy all of the following rules:
    1)  Each of the digits 1-9 must occur exactly once in each row.
    2)  Each of the digits 1-9 must occur exactly once in each column.
    3)  Each of the the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.

Empty cells are indicated by the character '.'.

Note:
    1)  The given board contain only digits 1-9 and the character '.'.
    2)  You may assume that the given Sudoku puzzle will have a single unique solution.
    3)  The given board size is always 9x9.
*/
class Solution {
private:
    static const int n = 3;
    static const int N = n*n;

    std::array<std::array<bool, N+1>, N> rows;
    std::array<std::array<bool, N+1>, N> cols;
    std::array<std::array<bool, N+1>, N> boxes;

    int digit(const char c) {
        return c - '0';
    }

    char to_char(const int d) {
        return d + '0';
    }

    bool cell_is_empty(const int row, const int col, std::vector<std::vector<char>>& board) {
        return board[row][col] == '.';
    }

    void init_params(std::vector<std::vector<char>>& board) {
        for (int i = 0; i < N; ++i) {
            std::fill(rows[i].begin(), rows[i].end(), false);
            std::fill(cols[i].begin(), cols[i].end(), false);
            std::fill(boxes[i].begin(), boxes[i].end(), false);
        }
        
        for (int row = 0; row < N; ++row) {
            for (int col = 0; col < N; ++col) {
                if (not cell_is_empty(row, col, board)) {
                    place_digit(digit(board[row][col]), row, col, board);
                }
            }
        }
    }

    bool can_place_digit(const int d, const int row, const int col) {
        const auto box = (row / n) * n + col / n;
        return not (rows[row][d] or cols[col][d] or boxes[box][d]);
    }

    void place_digit(const int d, const int row, const int col, std::vector<std::vector<char>>& board) {
        const auto box = (row / n) * n + col / n;
        rows[row][d] = true;
        cols[col][d] = true;
        boxes[box][d] = true;
        board[row][col] = to_char(d);
    }

    void remove_digit(const int d, const int row, const int col, std::vector<std::vector<char>>& board) {
        const auto box = (row / n) * n + col / n;
        rows[row][d] = false;
        cols[col][d] = false;
        boxes[box][d] = false;
        board[row][col] = '.';
    }

    bool recurse1(const int row, const int col, std::vector<std::vector<char>>& board) {
        if (row == N) {
            return true;
        } else if (not cell_is_empty(row, col, board)) {
            return  col + 1 == N ?
                    recurse1(row+1, 0, board):
                    recurse1(row, col+1, board);
        }
       
        for (int d = 1; d <= N; ++d) {
            if (can_place_digit(d, row, col)) {
                place_digit(d, row, col, board);
                const auto solved = col + 1 == N ?
                                    recurse1(row+1, 0, board):
                                    recurse1(row, col+1, board);
                if (solved) {
                    return true;
                }
                remove_digit(d, row, col, board);
            }
        }

        return false;
    }

    void solution1(std::vector<std::vector<char>>& board) {
        init_params(board);
        recurse1(0, 0, board);
    }
public:
    void solveSudoku(vector<vector<char>>& board) {
        solution1(board); 
    }
};
