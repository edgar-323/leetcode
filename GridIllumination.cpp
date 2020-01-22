/*
On a N x N grid of cells, each cell (x, y) with 0 <= x < N and 0 <= y < N has a lamp.
Initially, some number of lamps are on.  
lamps[i] tells us the location of the i-th lamp that is on.  
Each lamp that is on illuminates every square on its x-axis, y-axis, 
and both diagonals (similar to a Queen in chess).

For the i-th query queries[i] = (x, y), 
the answer to the query is 1 if the cell (x, y) is illuminated, else 0.
After each query (x, y) [in the order given by queries], 
we turn off any lamps that are at cell (x, y) or are adjacent 8-directionally 
(ie., share a corner or edge with cell (x, y).)

Return an array of answers.  
Each value answer[i] should be equal to the answer of the i-th query queries[i].

Example 1:
Input: N = 5, lamps = [[0,0],[4,4]], queries = [[1,1],[1,0]]
Output: [1,0]
Explanation: 
Before performing the first query we have both lamps [0,0] and [4,4] on.
The grid representing which cells are lit looks like this, where [0,0] is the top left corner, and [4,4] is the bottom right corner:
1 1 1 1 1
1 1 0 0 1
1 0 1 0 1
1 0 0 1 1
1 1 1 1 1
Then the query at [1, 1] returns 1 because the cell is lit.  After this query, the lamp at [0, 0] turns off, and the grid now looks like this:
1 0 0 0 1
0 1 0 0 1
0 0 1 0 1
0 0 0 1 1
1 1 1 1 1
Before performing the second query we have only the lamp [4,4] on.  Now the query at [1,0] returns 0, because the cell is no longer lit.

Note:
1 <= N <= 10^9
0 <= lamps.length <= 20000
0 <= queries.length <= 20000
lamps[i].length == queries[i].length == 2
*/
class Solution {
private:
    const std::vector<std::array<int,2>> offsets =   {{-1, -1}, {-1, 0,}, {-1, 1},
                                                     {0, -1}, {0, 0}, {0, 1},
                                                     {1, -1}, {1, 0}, {1, 1}};
    int N;
    std::unordered_map<int,int> rows;
    std::unordered_map<int,int> cols;
    std::unordered_map<int,int> hills;
    std::unordered_map<int,int> dales;
    std::unordered_set<std::string> lights;
    

    std::string key(const int i, const int j) {
        return std::to_string(i) + "#" + std::to_string(j);
    }

    bool is_lit(const int row, const int col) {
        return  (rows.count(row) and rows[row]) or
                (cols.count(col) and cols[col]) or
                (hills.count(row - col + N) and hills[row - col + N]) or
                (dales.count(row + col) and dales[row + col]);
    }

    void turn_off(const int row, const int col) {
        const auto cell = key(row, col);
        if (not lights.count(cell)) {
            return;
        }
        lights.erase(cell);
        --rows[row];
        --cols[col];
        --hills[row - col + N];
        --dales[row + col];
    }

    void turn_on(const int row, const int col) {
        const auto cell = key(row, col);
        if (lights.count(cell)) {
            return;
        }
        lights.insert(cell);
        ++rows[row];
        ++cols[col];
        ++hills[row - col + N];
        ++dales[row + col];
    }

    void turn_off_neighbors(const int row, const int col) {
        for (const auto& offset : offsets) {
            turn_off(row + offset[0], col + offset[1]);
        }
    }

    void init_params(const int N, const vector<vector<int>>& lamps) {
        this->N = N;
        rows.clear();
        cols.clear();
        hills.clear();
        dales.clear();
        lights.clear();
        for (const auto& lamp : lamps) {
            turn_on(lamp[0], lamp[1]);
        }
    }

    std::vector<int> solution1(
                        const int N,
                        const std::vector<std::vector<int>>& lamps,
                        const std::vector<std::vector<int>>& queries) {
        init_params(N, lamps);
        const int K = queries.size();
        auto results = std::vector<int>(K);
        for (int k = 0; k < K; ++k) {
            const auto row = queries[k][0];
            const auto col = queries[k][1];
            results[k] = is_lit(row, col); 
            turn_off_neighbors(row, col);
        }

        return results;
    }
public:
    vector<int> gridIllumination(int N, vector<vector<int>>& lamps, vector<vector<int>>& queries) {
        return solution1(N, lamps, queries);
    }
};
