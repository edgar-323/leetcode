/*
There are n cities connected by m flights. Each fight starts from city u and arrives at v with a price w.
Now given all the cities and flights, together with starting city src and the destination dst, your task is to find the cheapest price from src to dst with up to k stops. 
If there is no such route, output -1.

Example 1:
Input: 
n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
src = 0, dst = 2, k = 1
Output: 200
Explanation: 
The cheapest price from city 0 to city 2 with at most 1 stop costs 200, as marked red in the picture.

Example 2:
Input: 
n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
src = 0, dst = 2, k = 0
Output: 500
Explanation: 
The cheapest price from city 0 to city 2 with at most 0 stop costs 500, as marked blue in the picture.

Note:
The number of nodes n will be in range [1, 100], with nodes labeled from 0 to n - 1.
The size of flights will be in range [0, n * (n - 1) / 2].
The format of each flight will be (src, dst, price).
The price of each flight will be in the range [1, 10000].
k is in the range of [0, n - 1].
There will not be any duplicated flights or self cycles.
*/

class Solution {
private:
    const int INF = -1;
    bool is_infinite(const int d) {
        return d == INF;
    }
    /************************************************************************************************/
	int solution1(
            const int V, 
            const std::vector<std::vector<int>>& flights, 
            const int src, 
            const int dst, 
            const int K) {
		/* Time-Complexity:     O( V*E*K )
         * Space-Complexity:    O(V*K + E)
         * */

        // Explanation:
        // We will implement classic Algorithms textbook solution.
        // On a more general sense, it goes as follows:
        // Given a graph G(V, E), and two nodes src,dst € V,
        // we want to find length of shortest path from src to dst that
        // uses at most K edges.
        // For each node v € V and integer i <= K, we define:
        //  DP(v, i) =  length of shortest path from src to v that uses
        //              exactly i edges.
        // 
        // The starting values DP(v, 0) will be infinity for all v € V except src,
        // for which it will be 0.
        //
        // Then, the general update equation is
        //  DP(v, i) = min { dist(u, i-1) + d(u, v) | (u, v) € E }
        // 
        // where d(u, v) is the length of the edge (u, v), given that (u, v) € E.
        
        
        if (not K) {
           return src == dst ? 0 : INF;
        } 
             
        const int E = flights.size();
        
        auto incomingEdges = std::vector<std::vector<std::pair<int, int>>>(V);
        for (const auto& flight : flights) {
            const int u = flight[0];
            const int v = flight[1];
            const int d = flight[2];
            incomingEdges[v].push_back(std::make_pair(u, d));
        }

        auto DP = std::vector<std::vector<int>>(V, std::vector<int>(K+1, INF));
        DP[src][0] = 0;
        for (int i = 1; i <= K; ++i) {
            for (int v = 0; v < V; ++v) {
                for (const auto& edge : incomingEdges[v]) {
                    const int u = edge.first;
                    const int d = edge.second;
                    if (not is_infinite(DP[u][i-1])) {
                        DP[v][i] =  is_infinite(DP[v][i]) ?
                                    DP[u][i-1] + d :
                                    std::min(DP[v][i], DP[u][i-1] + d);
                    }
                }
            }
        }
        
        int shortest_path = INF;
        for (int i = 0; i <= K; ++i) {
            if (not is_infinite(DP[dst][i])) {
                shortest_path = is_infinite(shortest_path) ?
                                DP[dst][i] :
                                std::min(DP[dst][i], shortest_path);
            }
        }
        
        return shortest_path;
	}
    /************************************************************************************************/
    typedef struct { int to, length; } Edge;

    int solution2(
            const int V,
            const std::vector<std::vector<int>>& flights,
            const int src,
            const int dst,
            const int K) {
        /* Time-Complexity:     O()
         * Space-Complexity:    O()
         * */
        // DIJKSTRA'S ALGORITHM
        
        // Adjacency List
        auto graph = std::vector<std::vector<Edge>>(V);
        for (const auto& flight : flights) {
            const int u = flight[0];
            const int v = flight[1];
            const int d = flight[2];
            Edge edge;
            edge.to = v;
            edge.length = d;
            graph[u].push_back(edge);
        }
        
        auto dist = std::vector<int>(V, INT_MAX);
        auto hops = std::vector<int>(V, 0); 
        dist[src] = 0;
        
        std::set<std::pair<int,int>> active_nodes;
        active_nodes.insert( {0, src} );
        
        while (not active_nodes.empty()) {
            const int u = active_nodes.begin()->second;
            if (u == dst) {
                return dist[u];
            }
            active_nodes.erase(active_nodes.begin());
            if (hops[u] >= K) {
                continue;
            }
            for (const auto& edge : graph[u]) {
                const int v = edge.to;
                const int d = edge.length;
                if (dist[v] > dist[u] + d) {
                    active_nodes.erase({dist[v], v});
                    dist[v] = dist[u] + d;
                    hops[v] = hops[u] + 1;
                    active_nodes.insert({dist[v], v});
                } else if (dist[v] < INT_MAX and dist[v] == dist[u] + d) {
                    hops[v] = std::min(hops[v], hops[u] + 1);
                }
            }
        }

        return INF;
    }
    /************************************************************************************************/
public:
    int findCheapestPrice(int n, std::vector<std::vector<int>>& flights, int src, int dst, int K) {
  		return solution2(n, flights, src, dst, K+1);      
    }
};
