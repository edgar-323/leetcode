/*
There are N network nodes, labelled 1 to N.
Given times, a list of travel times as directed edges times[i] = (u, v, w), where u is the source node, v is the target node, and w is the time it takes for a signal to travel from source to target.
Now, we send a signal from a certain node K. How long will it take for all nodes to receive the signal? If it is impossible, return -1.

Example 1:
Input: times = [[2,1,1],[2,3,1],[3,4,1]], N = 4, K = 2
Output: 2

Note:
N will be in the range [1, 100].
K will be in the range [1, N].
The length of times will be in the range [1, 6000].
All edges times[i] = (u, v, w) will have 1 <= u, v <= N and 0 <= w <= 100.
*/

class Node {
public:
    int vertex, weight;
    Node(const int _to, const int _length):
        vertex(_to), weight(_length) 
    {}
};

class Solution {
private:
      
    int solution1(const std::vector<std::vector<int>>& times, const int N, const int K) {
        /* Time-Complexity:     O((V + E) * log(V))
         * Space-Complexity:    O(V + E)
         */
        // Dijkstra's Algorithm
        auto adj_list = std::vector<std::vector<Node>>(N+1);      
        for (const auto& time : times) {
            const int u = time[0];
            const int v = time[1];
            const int w = time[2];
            adj_list[u].push_back(Node(v, w));
        }
        auto dist = std::vector<int>(N+1, INT_MAX);
        dist[K] = 0;
        auto active_vertices = std::set<std::pair<int,int>>();
        active_vertices.insert( {0, K} ); 

        while (not active_vertices.empty()) {
            const auto u = active_vertices.begin()->second;
            active_vertices.erase( active_vertices.begin() );
            for (const auto& node : adj_list[u]) {
                const auto v = node.vertex;
                const auto w = node.weight;
                if (dist[v] > dist[u] + w) {
                    active_vertices.erase( { dist[v], v } );
                    dist[v] = dist[u] + w;
                    active_vertices.insert( { dist[v], v } );
                }
            }
        }

        int time_to_reach_all_nodes = 0; 
        for (int node = 1; node <= N; ++node) {
            if (dist[node] == INT_MAX) {
                return -1;
            }
            time_to_reach_all_nodes = std::max(time_to_reach_all_nodes, dist[node]);
        }

        return time_to_reach_all_nodes;
    }
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        return solution1(times, N, K);    
    }
};
