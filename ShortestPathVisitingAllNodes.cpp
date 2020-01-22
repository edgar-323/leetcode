/*
An undirected, connected graph of N nodes (labeled 0, 1, 2, ..., N-1) is given as graph.
graph.length = N, and j != i is in the list graph[i] exactly once, if and only if nodes i and j are connected.
Return the length of the shortest path that visits every node. 
You may start and stop at any node, you may revisit nodes multiple times, and you may reuse edges.

Example 1:
Input: [[1,2,3],[0],[0],[0]]
Output: 4
Explanation: One possible path is [1,0,2,0,3]

Example 2:
Input: [[1],[0,2,4],[1,3,4],[2],[1,2]]
Output: 4
Explanation: One possible path is [0,1,4,2,3]
 
Note:
1 <= graph.length <= 12
0 <= graph[i].length < graph.length
*/

struct Node {
    int bitMask;
    int vertex;
    int cost;

    Node(int bit, int n, int c) {
        bitMask = bit;
        vertex = n;
        cost = c;
    }

    bool equals(const Node& p) const {
        return bitMask == p.bitMask && vertex == p.vertex && cost == p.cost;
    }

    int hashCode() const {
        return 1331 * bitMask + 7193 * vertex + 727 * cost;
    }
};

struct Hash {
    size_t operator() (const Node &p) const {
        return p.hashCode();
    }
};

static bool operator==(const Node& lhs, const Node& rhs) {
    return lhs.equals(rhs);
}

class Solution {
private:
    int N;
    /********************************************************************************************************************************/
    int solution1(const std::vector<std::vector<int>>& graph) {
        /* Breadth First Search */
		/*
        Explanation:
		Idea is to use BFS to traverse the graph. 
		Since all edges are weighted 1, we can use a Queue (instead of a PriorityQueue sorted by cost). 
        Since all edges are weighted 1, then closer nodes will always be evaluated before farther ones.

		In order to represent a path, I used a combination of 3 variables:

		int bitMask: mask of all the nodes we visited so far: 0 -> not visited, 1 -> visited 
                     (Originally this was Set<Integer> of all nodes we visited so far, but since the Solution TLE and N <= 12, 
                      it turns out we can use a bitMask and 32 bits total in an Integer can cover all the possibilities. 
                      This is a small speed up optimization.)
		int curr: current node we are on
		int cost: the total cost in the path.

		Each path taken will have a unique combination of these 3 variables.

		We initialize our queue to contain N possible paths each starting from [0,N-1]. 
        This is because we can start at any of N possible Nodes.

		At each step, we remove element from the queue and see if we have covered all 12 nodes in our bitMask. 
        If we cover all nodes, we return the cost of the path immediately. 
        Since we are using BFS, this is guranteed to be path with the lowest cost.

		Otherwise, we get all the neighbors of current node, and for each neighbor, set the Node to visited in bitMask, 
        and then add it back into the queue.

		In order to prevent duplicate paths from being visited, we use a Set<Node> to store the Set<Path> that we have visited before. 
        Since we don't really need the cost here, I set cost to 0 for elements stored in Set. 
        You could also set the actual cost value here, it wouldn't make a difference
		*/ 
        N = graph.size();
        std::queue<Node> Q;
        std::unordered_set<Node, Hash> visited;

        for (int vertex = 0; vertex < N; vertex++) {
            const int mask = 1 << vertex;
            const auto node = Node(mask, vertex, 1);
            Q.push(node);
            visited.insert(node);
        }

        while (not Q.empty()) {
            const Node node = Q.front(); Q.pop();
            if (node.bitMask == (1 << N) - 1) {
                return node.cost - 1;
            }
            for (const int& neighbor : graph[node.vertex]) {
                const int mask = node.bitMask | (1 << neighbor);
                const auto neighbor_node = Node(mask, neighbor, node.cost + 1);
                if (not visited.count(neighbor_node)) {
                    Q.push(neighbor_node);
                    visited.insert(neighbor_node);
                }
            }
        }

        return -1;
    }
    /********************************************************************************************************************************/
    bool visited(const int node, const int& mask) {
        return (1 << node) & mask;
    }
    void mark(const int node, int& mask) {
        mask |= (1 << node);
    }
    void unmark(const int node, int& mask) {
        mask &= ~(1 << node);
    }
	int dfs2(const int node, const int depth, const std::vector<std::vector<int>>& graph, int& mask) {
        int max_depth = depth;
        mark(node, mask);
        
        for (const int neighbor : graph[node]) {
            if(not visited(neighbor, mask)) {
                max_depth = std::max(max_depth, dfs2(neighbor, depth + 1, graph, mask));
                // Can't be deeper
                if(max_depth == N-1) {
                    return max_depth;
                }
            }
        }
        
        unmark(node, mask);
        return max_depth;
    }
	int shortestPathLength(const std::vector<std::vector<int>>& graph, const int start_node) {
        int mask = 0;
        const int max_depth = dfs2(start_node, 0, graph, mask);
        return 2 * (N - 1) - max_depth;
    }
    int solution2(const std::vector<std::vector<int>>& graph) {
        /* Depth First Search */
		/*
        Explanation:

       	Two facts:
        1)  The length of the shortest path to visit all nodes is at least N-1, where N is the number of nodes. 
            => If you encounter a path of length N-1, you can return immediately.
        
        2)  For a tree (i.e. no cycle) rooted at i, 
            the length of the shortest path to visit all nodes starting from i is 2*(N-1) - maxDepth (think about it), 
            where maxDepth is the maximum distance of a node from the root i 
            => If we have a rooted tree, we can get the length of the shortest path starting from the root easily.
        
        Two problems and solutions:
        1)  We don't know which node should the shortest path start from 
            => Just try all nodes as the starting node.
        2)  The graph is not guaranteed to be acyclic 
            => For each node (as the root), use dfs2 to try all possible trees.
		*/  
        N = graph.size();
        if (N == 1) {
            return 0;
        } else if (N == 2) {
            return 1;
        }
        
        int min_length = INT_MAX;
        for(int start_node = 0; start_node < N; ++start_node) {
            min_length = std::min(min_length, shortestPathLength(graph, start_node));
            // Can't be shorter
            if(min_length == N-1) {
                return min_length;
            }
        }

        return min_length; 
    }
    /********************************************************************************************************************************/
   	int result;
    void dfs3(const std::vector<std::vector<int>>& graph, std::stack<int>& node_stack, vector<int>& visit_count, int count) {
        if (result == N) {
            // No we way we can do better than this (If this happens, the graph is a linked-list / tree)
            return;
        }
        if (count == N) {
            // We've seen all nodes, did we do a better job?
            result = std::min(result, int(node_stack.size()));
            return;
        }
        if (node_stack.size() >= result) {
            // We are on a worse path. No need to keep exploring.
            return;
        }
        // Last visited node 
        const int node = node_stack.top();
        // Visit neigbors of `node` with least # of visits
        // This will be the hueristic that drives this routine faster
        int least_visited_count = INT_MAX;
        for (const auto neighbor : graph[node]) { 
            least_visited_count = min(least_visited_count, visit_count[neighbor]);
        }
        for (const auto& neighbor : graph[node]) {
            if (visit_count[neighbor] == least_visited_count) {
                node_stack.push(neighbor);
                if (not visit_count[neighbor]) {
                    // We've never visited this node before so increment our count
                    count++;
                }
                visit_count[neighbor]++;
                dfs3(graph, node_stack, visit_count, count);
                visit_count[neighbor]--;
                if (not visit_count[neighbor]) {
                    count--;
                }
                node_stack.pop();                
            }
        }
    }
    int solution3(const std::vector<std::vector<int>>& graph) {
        N = graph.size();
        result = INT_MAX;
        auto node_stack = std::stack<int>();
        auto visit_count = std::vector<int>(N, 0);
        int count = 0;
        for (int start_node = 0; start_node < N; ++start_node) {
            node_stack.push(start_node);
            visit_count[start_node]++;
            count++;
            dfs3(graph, node_stack, visit_count, count);
            count--;
            visit_count[start_node]--;
            node_stack.pop();
        }
        return result - 1;
    }
    /********************************************************************************************************************************/
	int dist[15][15];
    void floyd_warshall_algorithm(const std::vector<std::vector<int>>& graph) {
        // Computes All-Pairs Shortest Path
       	memset(dist, 0x3f, sizeof(dist));
        for (int i = 0; i < N; i++) {
            const int M = graph[i].size();
            for (int j = 0; j < M; j++) {
                const int u = i; 
                const int v = graph[i][j];
                dist[u][v] = 1;
            }
        }
        for (int k = 0; k < N; k++) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    dist[i][j] = std::min(dist[i][j], dist[i][k]+dist[k][j]);
                }
            }
        }
    }
    int DP4() {
        // State-Compression DP[] Algorithm
        // Explanation:
        // Define group to represent a set of nodes of the graph (from 0 to N-1).
        // Since N <= 12, we can use an integer (call this integers `group`) to denote this set by stating that node i is in the group
        // if the ith bit of the group is set.
        // Then, we can now define
        //      DP[group][v] =  shortest path to traverse all nodes in the group while ending the path at node v 
        //                      (whom we assume is also in the group).
        // 
        // We see that, if v is currently not in some group, and we can to include it, we get:
        //      DP[group + v][v] =  min{ DP[group+v][v], DP[group+u][u] + dist[u][v] }
        //                              for all u € group
        // 
        // At the end, the answer we are seeking is:
        //      min{ DP[(1 << N) - 1][i] }
        //          for i € {0, .... N-1}
        // Since ((1 << N) - 1), denotes that all nodes will be in the group and the path will end at node i.
        // We take the minimum of all these paths lengths.
        //
        // The reason this is called "State-Compression" is becuase we have essentially been able to encode the concept of a set of nodes
        // in a group into a single integer.
        // This is possible when our number of nodes (or some other metric) is less then 31 bits.
        int DP[1<<13][13];
        memset(DP, 0x3f, sizeof(DP));
        for (int i = 0; i < N; i++) {
            DP[1<<i][i] = 0;
        }
        for (int group = 1; group < (1<<N); group++) {
            for (int u = 0; u < N; u++) {
                for (int v = 0; v < N; v++) {
                    const int src = 1 << u;
                    const int dst = 1 << v;
                    // if src is in the group and dst is not in the group
                    if ((group & src) and not (group & dst)) {
                        // DP[group + v][v]     = min{ DP[group + v][v], DP[group][u] + dist[u][v] }
                        //                          for all u € group 
                        DP[group|dst][v] = std::min(DP[group|dst][v], DP[group][u] + dist[u][v]);
                    }
                }
            }
        }
        int min_dis = 0x3f3f3f3f;
        for (int i=0; i < N; i++) {
            min_dis = min(DP[(1<<N)-1][i], min_dis);
        }
        return min_dis;
    }
    int solution4(const std::vector<std::vector<int>>& graph) {
        /* Floyd-Warshall All-Pairs Shortest Paths Algorithm In Conjuction With State-Compression Dynamic Programming Algorithm */
        // By far the most intersting solution I saw on LeetCode discussion forum.
        N = graph.size();
        floyd_warshall_algorithm(graph);
        return DP4(); 
    }
	/********************************************************************************************************************************/
public:
    int shortestPathLength(std::vector<std::vector<int>>& graph) {
        return solution4(graph);
    }
};

