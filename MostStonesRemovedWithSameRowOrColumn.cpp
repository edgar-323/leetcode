/*
On a 2D plane, we place stones at some integer coordinate points.  Each coordinate point may have at most one stone.
Now, a move consists of removing a stone that shares a column or row with another stone on the grid.
What is the largest possible number of moves we can make?

Example 1:
Input: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
Output: 5

Example 2:
Input: stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]
Output: 3

Example 3:
Input: stones = [[0,0]]
Output: 0

Note:
1 <= stones.length <= 1000
0 <= stones[i][j] < 10000
*/
class DSU {
public:
    std::vector<int> parent;
    std::vector<int> rank;

    DSU(const int N) {
        parent = std::vector<int>(N);
        for (int node = 0; node < N; ++node) {
            parent[node] = node;
        }
        rank = std::vector<int>(N, 0);
    }

    int find(const int node) {
        if (parent[node] != node) {
            parent[node] = find(parent[node]);
        }
        return parent[node];
    }

    void join(const int x, const int y) {
        const int xr = find(x);
        const int yr = find(y);
        if (xr == yr) {
            return;
        }
        if (rank[xr] < rank[yr]) {
            parent[xr] = yr;
        } else if (rank[xr] > rank[yr]) {
            parent[yr] = xr;
        } else {
            parent[xr] = yr;
            ++rank[yr];
        }
    }
};

class Solution {
private:
    static const int MAX_COORDINATE = 1e4;

    int solution1(const std::vector<std::vector<int>>& stones) {
        auto dsu = DSU(2 * MAX_COORDINATE); 

        for (const auto& stone : stones) {
            dsu.join(stone[0], stone[1] + MAX_COORDINATE);
        }

        auto seen = std::unordered_set<int>();
        for (const auto& stone : stones) {
            const auto id = dsu.find(stone[0]);
            if (not seen.count(id)) {
                seen.insert(id);
            }
        }

        return stones.size() - seen.size();
    }
public:
    int removeStones(vector<vector<int>>& stones) {
        return solution1(stones);       
    }
};
