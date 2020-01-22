/*
The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.
Given an integer n, return all distinct solutions to the n-queens puzzle.
Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.

Example:
Input: 4
Output: [
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]
Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above.
*/
class Solution {
private:
    typedef std::vector<std::string> Puzzle;
    
    int N;
    std::vector<bool> rows;
    std::vector<bool> hills;
    std::vector<bool> dales;
    std::vector<int> queens;
    std::vector<Puzzle> puzzles;

    void init_params(const int N) {
        this->N = N;
        rows = std::vector<bool>(N, false);
        hills = std::vector<bool>(2*N, false);
        dales = std::vector<bool>(2*N, false);
        queens = std::vector<int>(N);
    }

    void add_puzzle() {
        auto puzzle = Puzzle(N, std::string(N, ' '));
        for (int row = 0; row < N; ++row) {
            const auto col = queens[row];
            for (int j = 0; j < col; ++j) {
                puzzle[row][j] = '.';
            }
            puzzle[row][col] = 'Q';
            for (int j = col+1; j < N; ++j) {
                puzzle[row][j] = '.';
            }
        }
        puzzles.push_back(puzzle);
    }
    
    bool is_under_attack(const int row, const int col) {
        return  rows[col] or 
                hills[row - col + N] or 
                dales[row + col];
    }

    void place_queen(const int row, const int col) {
        rows[col] = true;
        hills[row - col + N] = true;
        dales[row + col] = true;
        queens[row] = col;
    }

    void remove_queen(const int row, const int col) {
        rows[col] = false;
        hills[row - col + N] = false;
        dales[row + col] = false;
    }

    void recurse1(const int row) {
        if (row == N) {
            add_puzzle();
            return;
        }
        for (int col = 0; col < N; ++col) {
            if (not is_under_attack(row, col)) {
                place_queen(row, col);
                recurse1(row+1);
                remove_queen(row, col);
            }
        }    
    }

    std::vector<Puzzle> solution1(const int N) {
        init_params(N);
        recurse1(0);
        return puzzles;
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        return solution1(n);
    }
};
