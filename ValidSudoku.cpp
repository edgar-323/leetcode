/*
Determine if a 9x9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:

Each row must contain the digits 1-9 without repetition.
Each column must contain the digits 1-9 without repetition.
Each of the 9 3x3 sub-boxes of the grid must contain the digits 1-9 without repetition.


The Sudoku board could be partially filled, where empty cells are filled with the character '.'.

Example 1:
Input:
[
  ["5","3",".",".","7",".",".",".","."],
  ["6",".",".","1","9","5",".",".","."],
  [".","9","8",".",".",".",".","6","."],
  ["8",".",".",".","6",".",".",".","3"],
  ["4",".",".","8",".","3",".",".","1"],
  ["7",".",".",".","2",".",".",".","6"],
  [".","6",".",".",".",".","2","8","."],
  [".",".",".","4","1","9",".",".","5"],
  [".",".",".",".","8",".",".","7","9"]
]
Output: true

Example 2:
Input:
[
  ["8","3",".",".","7",".",".",".","."],
  ["6",".",".","1","9","5",".",".","."],
  [".","9","8",".",".",".",".","6","."],
  ["8",".",".",".","6",".",".",".","3"],
  ["4",".",".","8",".","3",".",".","1"],
  ["7",".",".",".","2",".",".",".","6"],
  [".","6",".",".",".",".","2","8","."],
  [".",".",".","4","1","9",".",".","5"],
  [".",".",".",".","8",".",".","7","9"]
]
Output: false
Explanation: 
Same as Example 1, except with the 5 in the top left corner being 
modified to 8. Since there are two 8's in the top left 3x3 sub-box, it is invalid.

Note:
A Sudoku board (partially filled) could be valid but is not necessarily solvable.
Only the filled cells need to be validated according to the mentioned rules.
The given board contain only digits 1-9 and the character '.'.
The given board size is always 9x9.
*/

class Solution {
private:
    std::vector<std::vector<bool>> columns;
    std::vector<std::vector<bool>> rows;
    std::vector<std::vector<bool>> quads;
    
    void resetMaps() {
        columns = std::vector<std::vector<bool>>(9, std::vector<bool>(9, false));
        rows = std::vector<std::vector<bool>>(9, std::vector<bool>(9, false));
        quads = std::vector<std::vector<bool>>(9, std::vector<bool>(9, false));
    }

    bool is_number(char c) {
        return c != '.';
    }

    int get_value(char c) {
        return int(c) - int('1');
    }

    int get_quad(int i, int j) {
        /* We define the quadrants of the board 
         * as going left to rigth, top to bottom 
         * from 0 to 8*/
        if (i < 3) {
            if (j < 3) {
                return 0;
            } else if (j < 6) {
                return 1;
            } else {
                return 2;
            }
        } else if (i < 6) {
            if (j < 3) {
                return 3;
            } else if (j < 6) {
                return 4;
            } else {
                return 5;
            }
        } else {
            if (j < 3) {
                return 6;
            } else if (j < 6) {
                return 7;
            } else {
                return 8;
            }
        }
    }

    bool process_column(int index, int c) {
        std::vector<bool>& column = columns[c];
        if (column[index]) {
            return false;
        }
        column[index] = true;
        return true;
    }

    bool process_row(int index, int r) {
        std::vector<bool>& row = rows[r];
        if (row[index]) {
            return false;
        }
        row[index] = true;
        return true;
    }

    bool process_quad(int index, int row, int column) {
        int q = get_quad(row, column);
        std::vector<bool>& quad = quads[q];
        if (quad[index]) {
            return false;
        }
        quad[index] = true;
        return true;
    }

    bool process_board_value(char c, int row, int column) {
        int value = get_value(c);
        return process_column(value, column) and 
                process_row(value, row) and 
                process_quad(value, row, column);
    }

    bool solution1(std::vector<std::vector<char>>& board) {
        resetMaps();
        
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (is_number(board[i][j])) {
                    if (!process_board_value(board[i][j], i, j)) {
                        return false;
                    }
                }
            }
        }

        return true;
    }
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        return solution1(board);        
    }
};
