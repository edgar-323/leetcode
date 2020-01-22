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
    typedef std::tuple<int,int,int> Node;

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
        // Some explanation.
        // The key difference with the classic Dijkstra algo is, we don't maintain the global optimal distance to each node, i.e. ignore below optimization:
        // alt ← dist[u] + length(u, v)
        // if alt < dist[v]:
        // Because there could be routes which their length is shorter but pass more stops, and those routes don't necessarily constitute the best route in the end. 
        // To deal with this, rather than maintain the optimal routes with 0..K stops for each node, the solution simply put all possible routes into the priority queue, 
        // so that all of them has a chance to be processed. IMO, this is the most brilliant part.
        // And the solution simply returns the first qualified route, it's easy to prove this must be the best route.
        //
        //
        
        // Adjacency List
        auto graph = std::vector<std::vector<std::pair<int,int>>>(V);
        for (const auto& flight : flights) {
            const int u = flight[0];
            const int v = flight[1];
            const int d = flight[2];
            graph[u].push_back({ v, d });
        }

        auto PQ = std::priority_queue<Node, std::vector<Node>, std::greater<Node>>();
        PQ.push(std::make_tuple(0, src, K));

        while (not PQ.empty()) {
            const auto [cost, u, k] = PQ.top();
            PQ.pop();
            
            if (u == dst) {
                return cost;
            }
            if (not k) {
                continue;
            }
            for (const auto& to : graph[u]) {
                const auto [v, w] = to;
                PQ.push(std::make_tuple(cost + w, v, k-1));
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
