/*
There are N courses, labelled from 1 to N.
We are given relations[i] = [X, Y], representing a prerequisite relationship between course X and course Y: 
course X has to be studied before course Y.
In one semester you can study any number of courses as long as you have studied all the prerequisites for the course you are studying.
Return the minimum number of semesters needed to study all courses.  
If there is no way to study all the courses, return -1.

Example 1:
Input: N = 3, relations = [[1,3],[2,3]]
Output: 2
Explanation: 
In the first semester, courses 1 and 2 are studied. In the second semester, course 3 is studied.

Example 2:
Input: N = 3, relations = [[1,2],[2,3],[3,1]]
Output: -1
Explanation: 
No course can be studied because they depend on each other.

Note:
1 <= N <= 5000
1 <= relations.length <= 5000
relations[i][0] != relations[i][1]
There are no repeated relations in the input.
*/
class Solution {
private:
    int N;
    std::vector<std::vector<int>> adj_list;
    std::vector<int> num_prereqs;

    void build_graph(const int N, const std::vector<std::vector<int>>& relations) {
        this->N = N;
        adj_list = std::vector<std::vector<int>>(N+1);
        num_prereqs = std::vector<int>(N+1, 0);
        for (const auto& relation : relations) {
            adj_list[relation[0]].push_back(relation[1]);
            ++num_prereqs[relation[1]];
        }
    }
    
    int BFS() {
      	auto seen = std::vector<int>(N+1, false);
        auto Q = std::queue<int>();
        for (int u = 1; u <= N; ++u) {
            if (num_prereqs[u] == 0) {
                Q.push(u);
                seen[u] = true;
            }
        }
        int semesters = 0;
        int courses_taken = 0;
        while (not Q.empty()) {
            for (int sz = Q.size(); sz; --sz, ++courses_taken, Q.pop()) {
                const auto u = Q.front();
                for (const auto& v : adj_list[u]) {
                    if (not seen[v] and --num_prereqs[v] == 0) {
                        Q.push(v);
                        seen[v] = true;
                    }
                }
            }
            ++semesters;
        }

        return courses_taken == N ? semesters : -1;
    }

    int solution1(const int N, std::vector<std::vector<int>>& relations) {
        build_graph(N, relations);
        return BFS();
    }
public:
    int minimumSemesters(int N, vector<vector<int>>& relations) {
        return solution1(N, relations);        
    }
};
