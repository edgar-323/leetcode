/*
Given an undirected graph, return true if and only if it is bipartite.

Recall that a graph is bipartite if we can split it's set of nodes into two independent subsets A and B such that every edge in the graph has one node in A and another node in B.

The graph is given in the following form: graph[i] is a list of indexes j for which the edge between nodes i and j exists.  Each node is an integer between 0 and graph.length - 1.  There are no self edges or parallel edges: graph[i] does not contain i, and it doesn't contain any element twice.

Example 1:
Input: [[1,3], [0,2], [1,3], [0,2]]
Output: true
Explanation: 
The graph looks like this:
0----1
|    |
|    |
3----2
We can divide the vertices into two groups: {0, 2} and {1, 3}.
Example 2:
Input: [[1,2,3], [0,2], [0,1,3], [0,2]]
Output: false
Explanation: 
The graph looks like this:
0----1
| \  |
|  \ |
3----2
We cannot find a way to divide the set of nodes into two independent subsets.
 

Note:

graph will have length in range [1, 100].
graph[i] will contain integers in range [0, graph.length - 1].
graph[i] will not contain i or duplicate values.
The graph is undirected: if any element j is in graph[i], then i will be in graph[j].
*/

class Solution {
private:
    std::vector<bool> visited;
    std::vector<bool> A, B;
    int N;
    bool is_bipartite(const int u, const bool in_A, const std::vector<std::vector<int>>& adj_list) {
        if (visited[u]) {
            return in_A ? A[u] : B[u]; 
        }
        visited[u] = true;
        if (in_A) {
            A[u] = true;
        } else {
            B[u] = true;
        }
        for (const auto v : adj_list[u]) {
            if (not is_bipartite(v, not in_A, adj_list)) {
                return false;
            }
        }

        return true;
    }

    bool DFS(const std::vector<std::vector<int>>& adj_list) {
        for (int node = 0; node < N; ++node) {
            if (not visited[node]) {
                A = std::vector<bool>(N, false);
                B = std::vector<bool>(N, false);
                if (not is_bipartite(node, true, adj_list)) {
                    return false;
                }
            }
        }

        return true;
    }

	bool solution1(const std::vector<std::vector<int>>& graph) {
        /* Time-Complexity:     O((V + E) * C)
         * Space-Complexity:    O(V + E)
         *      Where:
         *          V = # of nodes
         *          E = # of edges
         *          C = # of connected components
         */
        N = graph.size();
        visited = std::vector<bool>(N, false);

        return DFS(graph); 
	}
public:
    bool isBipartite(vector<vector<int>>& graph) {
  		return solution1(graph);      
    }
};
