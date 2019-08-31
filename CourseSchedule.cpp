/*
There are a total of n courses you have to take, labeled from 0 to n-1.
Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]
Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?

Example 1:
Input: 2, [[1,0]] 
Output: true
Explanation: There are a total of 2 courses to take. 
             To take course 1 you should have finished course 0. So it is possible.

Example 2:
Input: 2, [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take. 
             To take course 1 you should have finished course 0, and to take course 0 you should
             also have finished course 1. So it is impossible.

Note:
The input prerequisites is a graph represented by a list of edges, not adjacency matrices. 
Read more about how a graph is represented.
You may assume that there are no duplicate edges in the input prerequisites.
*/

class List {
public:
    int node;
    List* next;
    List(int node, List* next) {
        this->node = node;
        this->next = next;
    }
};

class Solution {
private: 
    /*********************************************************************/
    List** adjList;
    bool* globallyMarked;
    bool* locallyMarked;
    int V;
    /*********************************************************************/
    bool hasCycle(int node) {
        if (locallyMarked[node]) {
            return true;
        } else if (globallyMarked[node]) {
            return false;
        }
        
        globallyMarked[node] = true;
        locallyMarked[node] = true;
        
        for (List* neighbor = adjList[node]; 
             neighbor != NULL; 
             neighbor = neighbor->next) {
            if (hasCycle(neighbor->node)) {
                return true;
            }
        }
        
        locallyMarked[node] = false;
        
        return false;
    }
    bool isDAG() {
        for (int node = 0; node < V; ++node) {
            if (hasCycle(node)) {
                return false;
            }
        }
        
        return true;
    }
    void generateGraph(int numCourses, 
                        std::vector<std::pair<int,int>>& prerequisites) {
        V = numCourses;
        globallyMarked = new bool[V];
        locallyMarked = new bool[V];
        adjList = new List*[V]; 
        
        for (int i = 0; i < V; ++i) {
            globallyMarked[i] = false;
            locallyMarked[i] = false;
            adjList[i] = NULL;
        }
        for (const auto& p : prerequisites) {
            adjList[p.first] = new List(p.second, adjList[p.first]);
        }
    }
    void destroyGraph() {
        delete[] globallyMarked;
        delete[] locallyMarked;
        
        for (int i = 0; i < V; ++i) {
            List* list;
            List* next;
            for (list = adjList[i]; list != NULL; list = next) {
                next = list->next;
                delete list;
            }
        }
        
        delete[] adjList;
        V = 0;
    }
    bool solution1(int numCourses, 
                    std::vector<std::pair<int,int>>& prerequisites) {
        /*
        Time-Complexity:    O(V+E)
        Space-Complexity:   O(V+E)
            Where: 
                V = #courses  
                E = #prerequisites
        */
        if (numCourses <= 0) {
            return true;
        }
        
        generateGraph(numCourses, prerequisites);
        bool can_finish = isDAG();
        destroyGraph();
        
        return can_finish;
    }
    /*********************************************************************/
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        return solution1(numCourses, prerequisites);
    }
};
