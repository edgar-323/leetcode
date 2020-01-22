/*
Given an array equations of strings that represent relationships between variables, 
each string equations[i] has length 4 and takes one of two different forms: "a==b" or "a!=b".  
Here, a and b are lowercase letters (not necessarily different) that represent one-letter variable names.

Return true if and only if it is possible to assign integers to variable names so as to satisfy all the given equations.

Example 1:
Input: ["a==b","b!=a"]
Output: false
Explanation: If we assign say, a = 1 and b = 1, then the first equation is satisfied, but not the second.  There is no way to assign the variables to satisfy both equations.

Example 2:
Input: ["b==a","a==b"]
Output: true
Explanation: We could assign a = 1 and b = 1 to satisfy both equations.

Example 3:
Input: ["a==b","b==c","a==c"]
Output: true

Example 4:
Input: ["a==b","b!=c","c==a"]
Output: false

Example 5:
Input: ["c==c","b==d","x!=z"]
Output: true

Note:
1 <= equations.length <= 500
equations[i].length == 4
equations[i][0] and equations[i][3] are lowercase letters
equations[i][1] is either '=' or '!'
equations[i][2] is '='
*/
class DSU {
    // Connected Components Union Find DataStructure
public:
    std::vector<int> parent;
    std::vector<int> rank;

    DSU(const int N) {
        parent = std::vector<int>(N);
        for (int i = 0; i < N; ++i) {
            parent[i] = i;
        }
        rank = std::vector<int>(N, 0);
    }
    
    int find(const int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void join(const int x, const int y) {
        const int xr = find(x);
        const int yr = find(y);
        if (xr == yr) {
            // already part of same set
            return;
        }
        if (rank[xr] < rank[yr]) {
            // tree of x is shorter so we make it point to tree of y
            parent[xr] = yr;
        } else if (rank[xr] > rank[yr]) {
            // tree of y is shorter so we make it point to tree of x
            parent[yr] = xr;
        } else {
            // trees are same height so we arbritarily make tree of y
            // point to tree of x and we increase rank of leader of x.
            parent[yr] = xr;
            ++rank[xr];
        }
    }
};
             
class Solution {
private:
    static const int ALPH_SZ = 26;

    int index(const char c) {
        return c - 'a';
    }

    bool solution1(const std::vector<std::string>& eqns) {
        auto dsu = DSU(ALPH_SZ); 
        for (const auto& eqn : eqns) {
            if (eqn[1] == '=') {
                const auto x = index(eqn[0]);
                const auto y = index(eqn[3]);
                dsu.join(x, y);
            }
        }
        for (const auto& eqn : eqns) {
            if (eqn[1] == '!') {
                const auto x = index(eqn[0]);
                const auto y = index(eqn[3]);
                if (dsu.find(x) == dsu.find(y)) {
                    return false;
                }
            }
        }

        return true;
    }

public:
    bool equationsPossible(vector<string>& equations) {
        return solution1(equations);       
    }
};
