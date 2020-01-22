/*
We have a list of bus routes. Each routes[i] is a bus route that the i-th bus repeats forever. For example if routes[0] = [1, 5, 7], this means that the first bus (0-th indexed) travels in the sequence 1->5->7->1->5->7->1->... forever.

We start at bus stop S (initially not on a bus), and we want to go to bus stop T. Travelling by buses only, what is the least number of buses we must take to reach our destination_buses? Return -1 if it is not possible.

Example:
Input: 
routes = [[1, 2, 7], [3, 6, 7]]
S = 1
T = 6
Output: 2
Explanation: 
The best strategy is take the first bus to the bus stop 7, then take the second bus to the bus stop 6.
Note:

1 <= routes.length <= 500.
1 <= routes[i].length <= 500.
0 <= routes[i][j] < 10 ^ 6.
*/
class Solution {
private:
    int solution1(const std::vector<std::vector<int>>& routes, const int S, const int T) {
        /* Breadth-First-Search */
        /* Treat Stations As Vertices */
        /* TIME-LIMIT-EXCEEDED (TOO SLOW) */

        auto adj_list = std::unordered_map<int, std::unordered_set<int>>();
        for (const auto& route : routes) {
            const int K = route.size();
            for (int i = 0; i < K; ++i) {
                for (int j = i+1; j < K; ++j) {
                    const auto& u = route[i];
                    const auto& v = route[j];
                    if (u == v) {
                        continue;
                    }
                    if (not adj_list[u].count(v)) {
                        adj_list[u].insert(v);
                    }
                    if (not adj_list[v].count(u)) {
                        adj_list[v].insert(u);
                    }
                }
            }
        }
        auto seen = std::unordered_set<int>();
        seen.insert(S);
        auto Q = std::queue<int>();
        Q.push(S);

        int buses = 0;
        
        while (not Q.empty()) {
            for (auto sz = Q.size(); sz; --sz, Q.pop()) {
                const auto u = Q.front();
                if (u == T) {
                    return buses;
                }
                for (const auto& v : adj_list[u]) {
                    if (not seen.count(v)) {
                        Q.push(v);
                        seen.insert(v);
                    }
                }
            }
            ++buses;
        }

        return -1;
    }

    int solution2(const std::vector<std::vector<int>>& routes, const int S, const int T) {
        /* Breadth-First-Search */
        /* Treat Buses As Vertices */
        /* ACCEPTED SOLUTION */

        if (S == T) {
            return 0;
        }

        const int N = routes.size();
        
        auto station_buses = std::unordered_map<int, std::unordered_set<int>>();
        for (int i = 0; i < N; ++i) {
            for (const auto& u : routes[i]) {
                if (not station_buses[u].count(i)) {
                    station_buses[u].insert(i);
                }
            }
        }
        
        auto adj_list = std::vector<std::vector<int>>(N);
        for (const auto& station : station_buses) {
            const auto buses = std::vector<int>(station.second.begin(), station.second.end());
            const int K = buses.size();
            for (int i = 0; i < K; ++i) {
                for (int j = i+1; j < K; ++j) {
                    adj_list[buses[i]].push_back(buses[j]);
                    adj_list[buses[j]].push_back(buses[i]);
                }
            }
        }
        
        auto Q = std::queue<int>();
        auto seen = std::vector<int>(N, false);
        for (const auto& source_bus : station_buses[S]) {
            Q.push(source_bus);
            seen[source_bus] = true;
        }

        int dist = 1;
        while (not Q.empty()) {
            for (auto sz = Q.size(); sz; --sz, Q.pop()) {
                const auto& bus = Q.front();
                if (station_buses[T].count(bus)) {
                    return dist;
                }
                for (const auto& next_bus : adj_list[bus]) {
                    if (not seen[next_bus]) {
                        Q.push(next_bus);
                        seen[next_bus] = true;
                    }
                }
            }
            ++dist;
        }

        return -1;     
    }
public:
    int numBusesToDestination(vector<vector<int>>& routes, int S, int T) {
        return solution2(routes, S, T);        
    }
};
