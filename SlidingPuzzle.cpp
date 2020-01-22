/*
On a 2x3 board, there are 5 tiles represented by the integers 1 through 5, and an empty square represented by 0.
A move consists of choosing 0 and a 4-directionally adjacent number and swapping it.
The state of the board is solved if and only if the board is [[1,2,3],[4,5,0]].
Given a puzzle board, return the least number of moves required so that the state of the board is solved. If it is impossible for the state of the board to be solved, return -1.

Examples:
Input: board = [[1,2,3],[4,0,5]]
Output: 1
Explanation: Swap the 0 and the 5 in one move.
Input: board = [[1,2,3],[5,4,0]]
Output: -1
Explanation: No number of moves will make the board solved.
Input: board = [[4,1,2],[5,0,3]]
Output: 5
Explanation: 5 is the smallest number of moves that solves the board.
An example path:
After move 0: [[4,1,2],[5,0,3]]
After move 1: [[4,1,2],[0,5,3]]
After move 2: [[0,1,2],[4,5,3]]
After move 3: [[1,0,2],[4,5,3]]
After move 4: [[1,2,0],[4,5,3]]
After move 5: [[1,2,3],[4,5,0]]
Input: board = [[3,2,4],[1,5,0]]
Output: 14

Note:
board will be a 2 x 3 array as described above.
board[i][j] will be a permutation of [0, 1, 2, 3, 4, 5].
*/
class Solution {
private:
    static const int M = 2;
    static const int N = 3;
    
    const std::vector<std::vector<int>> offsets = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    bool valid(const int i, const int j) {
        return 0 <= i and i < M and 0 <= j and j < N;
    }

    void swap_digits(const int x1, const int y1, const int x2, const int y2, std::string& board) {
        std::swap(board[x1*N + y1], board[x2*N + y2]);
    }

    char to_char(const int d) {
        return d + '0';
    }

    bool solved(const std::string& board) {
        for (int i = 0; i < M*N-1; ++i) {
            if (board[i] != to_char(i+1)) {
                return false;
            }
        }
        return board[M*N-1] == '0';
    }
    
    std::string to_str(const std::vector<std::vector<int>>& initial_board) {
        auto board = std::string(M*N, ' ');
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                board[i*N + j] = to_char(initial_board[i][j]);
            }
        }
        return board;
    }

    int solution1(const std::vector<std::vector<int>>& initial_board) {
        /* Explanation (BFS):
         * Every node will be a state of the board.
         * Will convert board to string in order to easily, hash it and alter its values.
         */
        auto seen = std::set<std::string>();
        auto Q = std::queue<std::string>();
        const auto src = to_str(initial_board);
        Q.push(src);
        seen.insert(src);

        int moves = 0;

        while (not Q.empty()) {
            for (auto sz = Q.size(); sz; --sz, Q.pop()) {
                auto board = Q.front();
                if (solved(board)) {
                    return moves;
                }
                int x,y;
                bool found_zero = false;
                for (int i = 0; i < M and not found_zero; ++i) {
                    for (int j = 0; j < N and not found_zero; ++j) {
                        if (board[i*N + j] == '0') {
                            x = i;
                            y = j;
                            found_zero = true;
                        }
                    }
                }
                if (found_zero) {
                    for (const auto& offset : offsets) {
                        const auto i = x + offset[0];
                        const auto j = y + offset[1];
                        if (valid(i, j)) {
                            swap_digits(x, y, i, j, board);
                            if (not seen.count(board)) {
                                Q.push(board);
                                seen.insert(board);
                            }
                            swap_digits(x, y, i, j, board);
                        }
                    }    
                }
            }
            ++moves;
        }

        return -1;
    }
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        return solution1(board);        
    }
};
