/*
In a directed graph, we start at some node and every turn, walk along a directed edge of the graph.  
If we reach a node that is terminal (that is, it has no outgoing directed edges), we stop.

We say our starting node is eventually safe if and only if we must eventually walk to a terminal node.  
More specifically, there exists a natural number K so that for any choice of where to walk, we must have stopped at a terminal node in less than K steps.

Which nodes are eventually safe?  
Return them as an array in sorted order.

The directed graph has N nodes with labels 0, 1, ..., N-1, where N is the length of graph.  
The graph is given in the following form: graph[i] is a list of labels j such that (i, j) is a directed edge of the graph.

Example:
Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
Output: [2,4,5,6]

Note:
graph will have length at most 10000.
The number of edges in the graph will not exceed 32000.
Each graph[i] will be a sorted list of different integers, chosen within the range [0, graph.length - 1].
*/
class Solution {
private:
    std::vector<bool> visited;
    std::vector<bool> eventually_safe;
    int N;

    bool is_eventually_safe(const int u, const std::vector<std::vector<int>>& adj_list) {
        if (visited[u]) {
            // Already computed.
            // Return Answer cached in eventually_safe[]
            return eventually_safe[u];
        }
        
        visited[u] = true;

        for (const auto v : adj_list[u]) {
            if (not is_eventually_safe(v, adj_list)) {
                return eventually_safe[u] = false;
            }
        }

        return eventually_safe[u] = true;
    }

    void DFS(const std::vector<std::vector<int>>& adj_list) {
        for (int node = 0; node < N; ++node) {
            is_eventually_safe(node, adj_list);
        }
    }

    std::vector<int> solution1(const std::vector<std::vector<int>>& adj_list) {
        if (adj_list.empty()) {
            return {};
        }
        // number of vertices.
        N = adj_list.size();
        // visited[] will be used to avoid loops and avoid recomputations.
        visited = std::vector<bool>(N, false);
        // Note: It is necessary for eventually_safe[u] to be initially false for all u.
        eventually_safe = std::vector<bool>(N, false);
        // Depth-First-Search
        DFS(adj_list);
        
        auto results = std::vector<int>();
        for (int node = 0; node < N; ++node) {
            if (eventually_safe[node]) {
                results.push_back(node);
            }
        }

        return results;
    }
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        return solution1(graph); 
    }
};
