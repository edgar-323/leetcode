/*
Equations are given in the format A / B = k, where A and B are variables represented as strings, and k is a real number (floating point number). Given some queries, return the answers. If the answer does not exist, return -1.0.

Example:
Given a / b = 2.0, b / c = 3.0.
queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? .
return [6.0, 0.5, -1.0, 1.0, -1.0 ].

The input is: vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries , where equations.size() == values.size(), and the values are positive. This represents the equations. Return vector<double>.

According to the example above:

equations = [ ["a", "b"], ["b", "c"] ],
values = [2.0, 3.0],
queries = [ ["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"] ]. 
 

The input is always valid. You may assume that evaluating the queries will result in no division by zero and there is no contradiction.

*/
class Solution {
private:
    std::unordered_map<std::string, std::unordered_set<std::string>> adj_list;
    std::unordered_map<std::string, std::unordered_map<std::string, double>> values;
    
    double dfs(const std::string& u, const std::string& target, std::unordered_set<std::string>& seen) { 
        if (u == target) {
            return 1.0;
        } else if (seen.count(u)) {
            return -1.0;
        }
        seen.insert(u);
        for (const auto& v : adj_list[u]) {
            const auto v1 = values[u][v]; 
            const double v2 = dfs(v, target, seen);
            if (v2 != -1.0) {
                return v1 * v2;
            }
        }

        return -1.0;
    }

	std::vector<double> solution1(
						    const std::vector<std::vector<std::string>>& equations,
					    	const std::vector<double>& vals,
                            const std::vector<std::vector<std::string>>& queries) {
        /* Time-Complexity:     O((V+E) * Q)
         * Space-Complexity:    O(V+E)
         *      Where:
         *          V = # of symbols
         *          E = # of equations
         *          Q = # of queries
         */
        // EXPLANATION (Depth-First-Search):
        // Every symbol that appears in the equations is a node.
        // Every equation  "u / v = c" defines the edge (u,v).

        adj_list.clear();
        values.clear();

        const int N = equations.size();
        for (int i = 0; i < N; ++i) {
            adj_list[equations[i][0]].insert(equations[i][1]);
            values[equations[i][0]][equations[i][1]] = vals[i];
            if (vals[i] != 0.0) {
                adj_list[equations[i][1]].insert(equations[i][0]);
                values[equations[i][1]][equations[i][0]] = 1.0 / vals[i];
            }
        }
        

        auto results = std::vector<double>();
        for (const auto& query : queries) {
            const auto& u = query[0];
            const auto& v = query[1];
            if (adj_list.count(u) and adj_list.count(v)) {
                auto seen = std::unordered_set<std::string>();
                results.push_back(dfs(u, v, seen);
            } else {
                results.push_back(-1.0);
            }
        }
        
        return results;
    }
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
		return solution1(equations, values, queries);        
    }
};
