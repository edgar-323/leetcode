/*
For an undirected graph with tree characteristics, we can choose any node as the root. The result graph is then a rooted tree. Among all possible rooted trees, those with minimum height are called minimum height trees (MHTs). Given such a graph, write a function to find all the MHTs and return a list of their root labels.

Format
The graph contains n nodes which are labeled from 0 to n - 1. You will be given the number n and a list of undirected edges (each edge is a pair of labels).

You can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.

Example 1 :

Input: n = 4, edges = [[1, 0], [1, 2], [1, 3]]

        0
        |
        1
       / \
      2   3 

Output: [1]
Example 2 :

Input: n = 6, edges = [[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]]

     0  1  2
      \ | /
        3
        |
        4
        |
        5 

Output: [3, 4]
Note:

According to the definition of tree on Wikipedia: “a tree is an undirected graph in which any two vertices are connected by exactly one path. In other words, any connected graph without simple cycles is a tree.”
The height of a rooted tree is the number of edges on the longest downward path between the root and a leaf.
*/

class Solution {
private:
    std::vector<int> solution1(int N, const std::vector<std::vector<int>>& edges) {
        // EXPLANATION:
        // See https://leetcode.com/problems/minimum-height-trees/discuss/76055/Share-some-thoughts
        if (N == 1) {
            return {0};
        }
        
        auto adj_list = std::vector<std::set<int>>(N);
        for (const auto& edge : edges) {
            adj_list[edge[0]].insert(edge[1]);
            adj_list[edge[1]].insert(edge[0]);
        }

        auto leaves = std::vector<int>();
        for (int node = 0; node < N; ++node) {
            if (adj_list[node].size() == 1) {
                leaves.push_back(node);
            }
        }

        while (N > 2) {
            N -= leaves.size();
            auto new_leaves = std::vector<int>();
            for (const auto leaf : leaves) {
                const auto neighbor = *adj_list[leaf].begin();
                adj_list[neighbor].erase(leaf);
                if (adj_list[neighbor].size() == 1) {
                    new_leaves.push_back(neighbor);
                }
            }
            leaves = new_leaves;
        }
        
        return leaves;
    }
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        return solution1(n, edges);        
    }
};
