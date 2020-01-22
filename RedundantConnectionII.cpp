/*
In this problem, a rooted tree is a directed graph such that, there is exactly one node (the root) for which all other nodes are descendants of this node, plus every node has exactly one parent, except for the root node which has no parents.

The given input is a directed graph that started as a rooted tree with N nodes (with distinct values 1, 2, ..., N), with one additional directed edge added. The added edge has two different vertices chosen from 1 to N, and was not an edge that already existed.

The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [u, v] that represents a directed edge connecting nodes u and v, where u is a parent of child v.

Return an edge that can be removed so that the resulting graph is a rooted tree of N nodes. If there are multiple answers, return the answer that occurs last in the given 2D-array.

Example 1:
Input: [[1,2], [1,3], [2,3]]
Output: [2,3]
Explanation: The given directed graph will be like this:
  1
 / \
v   v
2-->3
Example 2:
Input: [[1,2], [2,3], [3,4], [4,1], [1,5]]
Output: [4,1]
Explanation: The given directed graph will be like this:
5 <- 1 -> 2
     ^    |
     |    v
     4 <- 3
Note:
The size of the input 2D-array will be between 3 and 1000.
Every integer represented in the 2D-array will be between 1 and N, where N is the size of the input array.
*/

class Solution {
private:
    std::unordered_map<int, std::vector<int>> adj_list;
    std::unordered_map<std::string, int> index_map;
    int N;
    int sink;
    int root;
    std::vector<int> cyclic_edge;
    int cyclic_node; 

    std::string key(const int u, const int v) {
        return std::to_string(u) + "$" + std::to_string(v);
    }
    
    void compute_post_number(const int u, std::vector<bool>& visited, std::vector<int>& post, int& clock) {
        if (visited[u]) {
            return;
        }
        visited[u] = true;
        for (const auto& v : adj_list[u]) {
            compute_post_number(v, visited, post, clock);
        }
        post[u] = clock++;
    }
    void compute_root() {
        auto visited = std::vector<bool>(N, false);
        auto post = std::vector<int>(N);    
        int clock = 0;
        int max_post = 0;
        root = 0;
        for (int node = 1; node < N; ++node) {
            compute_post_number(node, visited, post, clock);
            if (post[node] > max_post) {
                max_post = post[node];
                root = node;
            }
        }
    }

    void build_graph(const std::vector<std::vector<int>>& edges) {
     	N = 0;
        const int E = edges.size(); 
        for (int i = 0; i < E; ++i) {
            const auto u = edges[i][0];
            const auto v = edges[i][1];
            adj_list[u].push_back(v);
            index_map[key(u,v)] = i;
            N = std::max<int>({ N, u, v });
        }
        ++N; 
        cyclic_node = 0;
        cyclic_edge = std::vector<int>(2, 0);
        index_map[key(0,0)] = 0;
    }

    bool graph_has_two_parent_sink() {
        auto num_parents = std::vector<int>(N, 0);
        for (int u = 1; u < N; ++u) {
            for (const auto& v : adj_list[u]) {
                num_parents[v]++;
                if (num_parents[v] == 2) {
                    sink = v;
                    return true;
                }
            }
        }
        return false;
    }
    
    bool sink_is_cyclic(const int u, const int parent, std::vector<bool>& visited) {
        if (visited[u]) {
            cyclic_edge[0] = parent;
            cyclic_edge[1] = u;
            return true;
        }
        visited[u] = true;
        for (const auto& v : adj_list[u]) {
            if (sink_is_cyclic(v, u, visited)) {
                return true;
            }
        }

        return false;
    }

    std::vector<int> remove_an_edge_from_sink() {
        auto visited = std::vector<bool>(N, false);
        if (sink_is_cyclic(sink, 0, visited)) {
            return cyclic_edge;
        }
        int parent1 = 0;
        int parent2 = 0;
        for (int u = 1; u < N; ++u) {
            for (const auto& v : adj_list[u]) {
                if (v == sink) {
                    if (not parent1) {
                        parent1 = u;
                    } else {
                        parent2 = u;
                    }
                }
            }
        }

        return  index_map[key(parent1, sink)] > index_map[key(parent2, sink)] ?
                std::vector<int>{ parent1, sink }:
                std::vector<int>{ parent2, sink };
    }
    
    bool visit(const int u, std::vector<bool>& visited) {
        if (visited[u]) {
            cyclic_node = u;
            return true;
        }

        visited[u] = true;
        for (const auto& v : adj_list[u]) {
            if (visit(v, visited)) {
                if (index_map[key(u,v)] > index_map[key(cyclic_edge[0], cyclic_edge[1])]) {
                    cyclic_edge[0] = u;
                    cyclic_edge[1] = v;
                }
                return u != cyclic_node;
            }
        }

        return false;
    }

    void compute_cyclic_edge() {
        compute_root();
        auto visited = std::vector<bool>(N, false);
        visit(root, visited);
    }

    std::vector<int> solution1(const std::vector<std::vector<int>>& edges) {
        /* Time-Complexity:     O(V+E)
         * Space-Complexity:    O(V+E)
         */
        // EXPLANATION:
        // This is my solution.
        // I am not particularly proud of this solution since it has 3 different special cases
        // in order to solve it, which makes it lengthy.
        // Keep in mind that I used DFS to accomplish everything.
        // The final graph must be a tree which has one root node from which all other nodes are discoverable,
        // and every node must have exactly one parent.
        // First, this problem is similar to RedundantConnectionI in the case where we have a cycle in the current graph.
        // We already know how to solve this problem (use DFS and keep rewinding on the edges once you encounter a cyclic node).
        // However, we can also have the case where one node in the current graph has two parents.
        // In this case, one of the parent edges must be removed.
        // We can simply remove the edge that appears later in the input edges, however, if this two node child is part of a cycle,
        // then we must remove the edge that is part of the cycle.
        // I wish I knew how to unify these 3 different cases into one general case in order to shorten the code.
        build_graph(edges);
        if (graph_has_two_parent_sink()) {
            return remove_an_edge_from_sink();
        }
        compute_cyclic_edge();

        return cyclic_edge;
    }
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
  		return solution1(edges);
    }
};
