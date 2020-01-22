/*
An undirected, connected tree with N nodes labelled 0...N-1 and N-1 edges are given.

The ith edge connects nodes edges[i][0] and edges[i][1] together.

Return a list ans, where ans[i] is the sum of the distances between node i and all other nodes.

Example 1:

Input: N = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
Output: [8,12,6,10,10,10]
Explanation: 
Here is a diagram of the given tree:
  0
 / \
1   2
   /|\
  3 4 5
We can see that dist(0,1) + dist(0,2) + dist(0,3) + dist(0,4) + dist(0,5)
equals 1 + 1 + 2 + 2 + 2 = 8.  Hence, answer[0] = 8, and so on.
Note: 1 <= N <= 10000
*/
class Solution {
private:
    std::vector<int> ans;
    std::vector<int> size;
    std::vector<std::vector<int>> adj_list;
    int N;

    void recurse1(const int node, const int parent) {
        for (const int child : adj_list[node]) {
            if (child != parent) {
                recurse1(child, node);
                size[node] += size[child];
                ans[node] += (ans[child] + size[child]);
            }
        }
    }

    void recurse2(const int node, const int parent) {
        for (const int child : adj_list[node]) {
            if (child != parent) {
                ans[child] = ans[node] - size[child] + N - size[child];
                recurse2(child, node);
            }
        }
    }

    std::vector<int> solution1(const int N, std::vector<std::vector<int>>& edges) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         */
        // EXPLANATION (Subtree Sum and Count):
        // See LeetCode Official Solution Wrriten By @awice 
        
        this->N = N;
        adj_list = std::vector<std::vector<int>>(N);      
        for (const auto& edge : edges) {
            adj_list[edge[0]].push_back(edge[1]);
            adj_list[edge[1]].push_back(edge[0]);
        }
        ans = std::vector<int>(N, 0);
        size = std::vector<int>(N, 1);
        
        recurse1(0, -1);
        recurse2(0, -1);

        return ans;
    }
public:
    vector<int> sumOfDistancesInTree(int N, vector<vector<int>>& edges) {
        return solution1(N, edges);       
    }
};
