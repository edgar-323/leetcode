/*
There are n items each belonging to zero or one of m groups where group[i] is the group that the i-th item belongs to and it's equal to -1 if the i-th item belongs to no group. The items and the groups are zero indexed. A group can have no item belonging to it.
Return a sorted list of the items such that:
The items that belong to the same group are next to each other in the sorted list.
There are some relations between these items where beforeItems[i] is a list containing all the items that should come before the i-th item in the sorted array (to the left of the i-th item).
Return any solution if there is more than one solution and return an empty list if there is no solution.

Example 1:
Input: n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems = [[],[6],[5],[6],[3,6],[],[],[]]
Output: [6,3,4,1,5,2,0,7]

Example 2:
Input: n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems = [[],[6],[5],[6],[3],[],[4],[]]
Output: []
Explanation: This is the same as example 1 except that 4 needs to be before 6 in the sorted list.

Constraints:
1 <= m <= n <= 3*10^4
group.length == beforeItems.length == n
-1 <= group[i] <= m-1
0 <= beforeItems[i].length <= n-1
0 <= beforeItems[i][j] <= n-1
i != beforeItems[i][j]
beforeItems[i] does not contain duplicates elements.
*/

class Solution {
private:
    int M,N;
    std::vector<int> group;
    std::vector<std::vector<int>> group_adj_list; 
    std::vector<std::vector<int>> item_adj_list;

    void build_graphs(const std::vector<std::vector<int>>& before) {
        group_adj_list = std::vector<std::vector<int>>(M);
        item_adj_list = std::vector<std::vector<int>>(N);
        for (int i = 0; i < N; ++i) {
            const int u = group[i];
            for (const auto j : before[i]) {
                const int v = group[j];
                if (u != v) {
                    group_adj_list[u].push_back(v);
                } else if (i != j) {
                    item_adj_list[i].push_back(j);
                }
            }
        }
    }

    bool has_cycle(const int u, std::vector<bool>& globally_marked, std::vector<bool>& locally_marked, const std::vector<std::vector<int>>& adj_list) {
        if (locally_marked[u]) {
            return true;
        } else if (globally_marked[u]) {
            return false;
        }
        globally_marked[u] = true;
        locally_marked[u] = true;
        for (const auto v : adj_list[u]) {
            if (has_cycle(v, globally_marked, locally_marked, adj_list)) {
                return true;
            }
        }
        locally_marked[u] = false;
        return false;
    }
    bool is_DAG(const std::vector<std::vector<int>>& adj_list) {
        const int K = adj_list.size();  
        auto globally_marked = std::vector<bool>(K, false);
        auto locally_marked = std::vector<bool>(K, false);
        for (int node = 0; node < K; ++node) {
            if (has_cycle(node, globally_marked, locally_marked, adj_list)) {
                return false;
            }
        }
        return true;
    }

    void visit_group(const int u, std::vector<bool>& visited, std::vector<int>& ordering) {
        if (visited[u]) {
            return;
        }
        visited[u] = true;
        for (const auto v : group_adj_list[u]) {
            visit_group(v, visited, ordering);
        }
        ordering.push_back(u);
    }

    std::vector<int> get_group_ordering() {
        auto ordering = std::vector<int>();
        ordering.reserve(M);
        auto visited = std::vector<bool>(M, false);
        for (int node = 0; node < M; ++node) {
            visit_group(node, visited, ordering);
        }
        return ordering; 
    }
    
    void get_item_order(
            const int u, 
            std::vector<bool>& visited, 
            std::vector<std::vector<int>>& groups) {
        if (visited[u]) {
            return;
        }
        visited[u] = true;
        for (const auto v : item_adj_list[u]) {
            get_item_order(v, visited, groups);
        }
        groups[group[u]].push_back(u);
    }

    std::vector<int> get_final_ordering() {
        auto groups = std::vector<std::vector<int>>(M);
        auto visited = std::vector<bool>(N, false);
        for (int item = 0; item < N; ++item) {
            get_item_order(item, visited, groups);
        }
        const auto group_ordering = get_group_ordering();
        auto final_ordering = std::vector<int>();
        final_ordering.reserve(N);
        for (const int group_num : group_ordering) {
            for (const int item : groups[group_num]) {
                final_ordering.push_back(item);
            }
        }

        return final_ordering;
    }

    std::vector<int> solution1(
                        const int _N, const int _M,
                        const std::vector<int>& _group,
                        const std::vector<std::vector<int>>& before) {
        N = _N;
        M = _M;
        group = std::vector<int>(N);
        for (int i = 0; i < _group.size(); ++i) {
            group[i] =  _group[i] >= 0 ?_group[i] : M++;
        }
        build_graphs(before);
        if (not is_DAG(group_adj_list) or not is_DAG(item_adj_list)) {
            return {};
        }
        return get_final_ordering(); 
    }
public:
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
        return solution1(n, m, group, beforeItems);        
    }
};
