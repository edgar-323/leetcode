/*
Consider a directed graph, with nodes labelled 0, 1, ..., n-1.  In this graph, each edge is either red or blue, and there could be self-edges or parallel edges.

Each [i, j] in red_edges denotes a red directed edge from node i to node j.  Similarly, each [i, j] in blue_edges denotes a blue directed edge from node i to node j.

Return an array answer of length n, where each answer[X] is the length of the shortest path from node 0 to node X such that the edge colors alternate along the path (or -1 if such a path doesn't exist).

 

Example 1:

Input: n = 3, red_edges = [[0,1],[1,2]], blue_edges = []
Output: [0,1,-1]
Example 2:

Input: n = 3, red_edges = [[0,1]], blue_edges = [[2,1]]
Output: [0,1,-1]
Example 3:

Input: n = 3, red_edges = [[1,0]], blue_edges = [[2,1]]
Output: [0,-1,-1]
Example 4:

Input: n = 3, red_edges = [[0,1]], blue_edges = [[1,2]]
Output: [0,1,2]
Example 5:

Input: n = 3, red_edges = [[0,1],[0,2]], blue_edges = [[1,0]]
Output: [0,1,1]
 

Constraints:

1 <= n <= 100
red_edges.length <= 400
blue_edges.length <= 400
red_edges[i].length == blue_edges[i].length == 2
0 <= red_edges[i][j], blue_edges[i][j] < n
*/
class Solution {
private:
    std::vector<int> solution1(
                        const int N,
                        const std::vector<std::vector<int>>& red_edges,
                        const std::vector<std::vector<int>>& blue_edges) {
        // PLAN:
        // Use BFS as follows:
        // Every path requires the use of alternating edge colors.
        // Thus a node... 
        auto red_adj_list = std::vector<std::vector<int>>(N);
        for (const auto& red_edge : red_edges) {
            red_adj_list[red_edge[0]].push_back(red_edge[1]);
        }
        auto blue_adj_list = std::vector<std::vector<int>>(N);
        for (const auto& blue_edge : blue_edges) {
            blue_adj_list[blue_edge[0]].push_back(blue_edge[1]);
        }
        // Red => False
        // Blue => True
        auto seen = std::vector<std::vector<bool>>(N, std::vector<bool>(2, false)); 
        seen[0][0] = true;
        seen[0][1] = true;
        auto answer = std::vector<int>(N, INT_MAX);
        // Queue<Node, Color> where Node is the vertex label, and Color means that the next outgoing
        // edge color must be Color (Red if false and Blue if true)
        auto Q = std::queue<std::pair<int, bool>>();
        Q.push({0, false});
        Q.push({0, true});

        int dist = 0;
        while (not Q.empty()) {
            for (int i = Q.size(); i; --i, Q.pop()) {
                const auto u = Q.front().first;
                const auto blue = Q.front().second;
                for (const auto v : (blue ? blue_adj_list[u] : red_adj_list[u])) {
                    if (not seen[v][not blue]) {
                        Q.push({v, not blue});
                        seen[v][not blue] = true;
                    }
                }
                // Do I need to minimize ?
                // Yes because there may be more than one way to get to node u due to the alternating edge color requirement.
                answer[u] = std::min(answer[u], dist);
            }
            ++dist;
        }

        for (int node = 0; node < N; ++node) {
            if (answer[node] == INT_MAX) {
                answer[node] = -1;
            }
        }

        return answer;
    }

public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& red_edges, vector<vector<int>>& blue_edges) {
 		return solution1(n, red_edges, blue_edges);        
    }
};
