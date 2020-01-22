/*
There are a total of n courses you have to take, labeled from 0 to n-1.
Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]
Given the total number of courses and a list of prerequisite pairs, return the ordering of courses you should take to finish all courses.
There may be multiple correct orders, you just need to return one of them. If it is impossible to finish all courses, return an empty array.

Example 1:
Input: 2, [[1,0]] 
Output: [0,1]
Explanation: There are a total of 2 courses to take. To take course 1 you should have finished   
             course 0. So the correct course order is [0,1] .

Example 2:
Input: 4, [[1,0],[2,0],[3,1],[3,2]]
Output: [0,1,2,3] or [0,2,1,3]
Explanation: There are a total of 4 courses to take. To take course 3 you should have finished both     
             courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0. 
             So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3] .

Note:
The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.
You may assume that there are no duplicate edges in the input prerequisites.
*/
class Solution {
private:
    std::vector<int> courses;
    std::vector<int> num_prereqs;
    std::vector<bool> visited;
    std::vector<bool> marked;
    std::vector<std::vector<int>> adj_list;
    int N;
    
    bool has_cycle(const int u) {
        if (marked[u]) {
            return true; 
        }
        if (visited[u]) {
            return false;
        }
        
        visited[u] = true;
        marked[u] = true;
        for (const auto v : adj_list[u]) {
            if (has_cycle(v)) {
                return true;
            }
            ++num_prereqs[v];   
        }
        marked[u] = false;

        return false;
    }

    bool is_DAG() {
        // computes num_prereqs[u] but will also return true if the graph is a DAG. 
        num_prereqs = std::vector<int>(N, 0);
        marked = std::vector<bool>(N, false);
        visited = std::vector<bool>(N, false);
        for (auto node = 0; node < N; ++node) {
            if (has_cycle(node)) {
                return false;
            }
        }
    
        return true;     
    }
    
    void take_course(const int u) {
        // At this point we can take course u
        visited[u] = true;  
        courses.push_back(u);

        for (const auto v : adj_list[u]) {
            --num_prereqs[v];
            if (num_prereqs[v] == 0) {
                take_course(v);
            }
        }
    }

    void compute_course_ordering() {
        courses.clear();
        visited = std::vector<bool>(N, false);
        for (auto node = 0; node < N; ++node) {
            if (not visited[node] and num_prereqs[node] == 0) {
                take_course(node); 
            }
        }
    }

    std::vector<int> solution1(const int num_courses, const std::vector<std::vector<int>>& prereqs) {
        /* Time-Complexity:     O(V+E)
         * Space-Complexity:    O(V+E)
         */
        // EXPLANATION (Depth-First-Search)
        // We transform prereqs[] into adj_list[] so we can represent the course graph.
        // We ensure that the underlying graph is a DAG. (If not then the task is impossible).
        // While ensuring that the graph is a DAG, we simultaneously compute num_prereqs[u]
        // which denotes the number of prereqs that course u requires.
        // Finally, if we have a DAG, then we compute a valid course ordering.
        // This is done by taking a course when it hasnt before been taken and when num_prereqs[u] == 0.
        // 
        // Both of the above procedures are accomplished via DFS walks.
        N = num_courses;
        adj_list = std::vector<std::vector<int>>(N); 
        for (const auto& prereq : prereqs) {
            adj_list[prereq[1]].push_back(prereq[0]);
        }  
        if (not is_DAG()) {
            return {};
        }
        
        compute_course_ordering();
        return courses;
    }
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        return solution1(numCourses, prerequisites);
    }
};
