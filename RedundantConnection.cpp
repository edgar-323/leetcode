/*
this problem, a tree is an undirected graph that is connected and has no cycles.
The given input is a graph that started as a tree with N nodes (with distinct values 1, 2, ..., N), with one additional edge added. The added edge has two different vertices chosen from 1 to N, and was not an edge that already existed.
The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [u, v] with u < v, that represents an undirected edge connecting nodes u and v.
Return an edge that can be removed so that the resulting graph is a tree of N nodes. If there are multiple answers, return the answer that occurs last in the given 2D-array. The answer edge [u, v] should be in the same format, with u < v.

Example 1:
Input: [[1,2], [1,3], [2,3]]
Output: [2,3]
Explanation: The given undirected graph will be like this:
  1
 / \
2 - 3

Example 2:
Input: [[1,2], [2,3], [3,4], [1,4], [1,5]]
Output: [1,4]
Explanation: The given undirected graph will be like this:
5 - 1 - 2
    |   |
    4 - 3

Note:
The size of the input 2D-array will be between 3 and 1000.
Every integer represented in the 2D-array will be between 1 and N, where N is the size of the input array.

Update (2017-09-26):
We have overhauled the problem description + test cases and specified clearly the graph is an undirected graph. For the directed graph follow up please see Redundant Connection II). We apologize for any inconvenience caused.
*/
class Solution {
private:
    std::unordered_map<std::string, int> index_map;
    std::unordered_map<int, std::vector<int>> adj_list;
    std::vector<bool> visited;
    std::vector<int> edge;
    int cyclic_node;

    std::string key(const int u, const int v) {
        return std::to_string(std::min(u,v)) + "$" + std::to_string(std::max(u,v));
    }
    
    bool visit(const int u, const int parent) {
        if (visited[u]) {
            cyclic_node = u;
            return true;
        }

        visited[u] = true;

        for (const auto v : adj_list[u]) {
            if (v != parent and visit(v, u)) {
                if (index_map[key(u,v)] > index_map[key(edge[0], edge[1])]) {
                    edge[0] = u;
                    edge[1] = v;
                }
                return u != cyclic_node; 
            }
        }

        return false;
    }

    std::vector<int> solution1(const std::vector<std::vector<int>>& edges) {
        /* Time-Complexity:     O(V+E)
         * Space-Complexity:    O(V+E)
         *      Where:
         *          V = # of vertices
         *          E = # of edges
         */
        const int E = edges.size();
        int V = 0;
        for (int i = 0; i < E; ++i) {
            const int u = edges[i][0];
            const int v = edges[i][1];
            index_map[key(u,v)] = i;
            adj_list[u].push_back(v);
            adj_list[v].push_back(u);
            V = std::max<int>({V, u, v});
        }
        visited = std::vector<bool>(V+1, false);
        index_map[key(0,0)] = 0;
        edge = std::vector<int>(2, 0);
        cyclic_node = 0;

        visit(edges[0][0], 0);  
        
        return {std::min(edge[0], edge[1]), std::max(edge[0], edge[1])}; 
    }
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        return solution1(edges);       
    }
};
