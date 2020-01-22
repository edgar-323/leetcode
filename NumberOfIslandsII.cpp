/*
A 2d grid map of m rows and n columns is initially filled with water. 
We may perform an addLand operation which turns the water at position (row, col) into a land. 
Given a list of positions to operate, count the number of islands after each addLand operation. 
An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. 
You may assume all four edges of the grid are all surrounded by water.

Example:
Input: m = 3, n = 3, positions = [[0,0], [0,1], [1,2], [2,1]]
Output: [1,1,2,3]
Explanation:

0 0 0
0 0 0
0 0 0
Operation #1: addLand(0, 0) turns the water at grid[0][0] into a land.
1 0 0
0 0 0   Number of islands = 1
0 0 0
Operation #2: addLand(0, 1) turns the water at grid[0][1] into a land.
1 1 0
0 0 0   Number of islands = 1
0 0 0
Operation #3: addLand(1, 2) turns the water at grid[1][2] into a land.
1 1 0
0 0 1   Number of islands = 2
0 0 0
Operation #4: addLand(2, 1) turns the water at grid[2][1] into a land.
1 1 0
0 0 1   Number of islands = 3
0 1 0

Follow up:
Can you do it in time complexity O(k log mn), where k is the length of the positions?

*/

typedef std::pair<int,int> Node;

class DSU {
private:
    int count;
    std::vector<std::vector<Node>> parent;
    std::vector<std::vector<int>> rank;

    Node find(const Node& node) {
        if (parent[node.first][node.second] != node) {
            parent[node.first][node.second] = find(parent[node.first][node.second]);
        }
        return parent[node.first][node.second];
    }

    int get_rank(const Node& node) {
        return rank[node.first][node.second];   
    }

    void increment_rank(const Node& node) {
        rank[node.first][node.second]++;
    }
public:
    DSU(const int M, const int N) {
        count = 0;
        parent = std::vector<std::vector<Node>>(M, std::vector<Node>(N));
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                parent[i][j] = std::make_pair(-1, -1);
            }
        }
        rank = std::vector<std::vector<int>>(M, std::vector<int>(N, 0)); 
    }
    
    Node find(const int i, const int j) {
        return find(std::make_pair(i, j));
    }

    void join(const int x1, const int y1, const int x2, const int y2) {
        const auto p1 = find(x1, y1);
        const auto p2 = find(x2, y2);

        if (p1 == p2) {
            return;
        }
        const auto r1 = get_rank(p1);
        const auto r2 = get_rank(p2);
        
        if (r1 < r2) {
            parent[p1.first][p1.second] = p2;
        } else if (r1 > r2) {
            parent[p2.first][p2.second] = p1;
        } else {
            parent[p1.first][p1.second] = p2;
            increment_rank(p2);
        }
        --count;
    }

    void add_node(const Node& node) {
        if (parent[node.first][node.second].first == -1) {
            parent[node.first][node.second] = std::make_pair(node.first, node.second);
            ++count;
        }
    }        

    int connected_components() {
        return count;
    }

    void join(const Node& x, const Node& y) {
        join(x.first, x.second, y.first, y.second);
    }

    bool are_connected(const Node& node1, const Node& node2) {
        return find(node1) == find(node2);
    }

    bool are_connected(const int x1, const int y1, const int x2, const int y2) {
        return find(x1, y1) == find(x2, y2);
    }
};

class Solution {
private:
    int M,N;
    std::vector<std::vector<bool>> land;

    bool is_valid(const int i, const int j) {
        return 0 <= i and i < M and 0 <= j and j < N;
    }

    void add_land(const int i, const int j) {
        land[i][j] = true;
    }

    bool is_land(const Node& node) {
        return is_valid(node.first, node.second) and land[node.first][node.second];
    }
    
    std::vector<int> solution1(
                        const int m,
                        const int n,
                        const std::vector<std::vector<int>>& positions) {
        M = m;
        N = n;
        auto dsu = DSU(M, N);
        land = std::vector<std::vector<bool>>(M, std::vector<bool>(N, false));

        auto results = std::vector<int>(); 

        for (const auto& pos : positions) {
            const auto i = pos[0];
            const auto j = pos[1];
            const auto node = std::make_pair(i, j);
            const auto top = std::make_pair(i-1, j);
            const auto bot = std::make_pair(i+1, j);
            const auto left = std::make_pair(i, j-1);
            const auto right = std::make_pair(i, j+1);
            dsu.add_node(node);
            if (is_land(top)) {
                dsu.join(node, top);
            }
            if (is_land(bot)) {
                dsu.join(node, bot);
            }
            if (is_land(left)) {
                dsu.join(node, left);
            }
            if (is_land(right)) {
                dsu.join(node, right);
            }
            results.push_back(dsu.connected_components());
            add_land(i, j);
        }
        
        return results;
    }
public:
    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
        return solution1(m, n, positions);       
    }
};
