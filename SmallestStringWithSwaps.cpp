/*
You are given a string s, and an array of pairs of indices in the string pairs where pairs[i] = [a, b] indicates 2 indices(0-indexed) of the string.

You can swap the characters at any pair of indices in the given pairs any number of times.

Return the lexicographically smallest string that s can be changed to after using the swaps.

 

Example 1:

Input: s = "dcab", pairs = [[0,3],[1,2]]
Output: "bacd"
Explaination: 
Swap s[0] and s[3], s = "bcad"
Swap s[1] and s[2], s = "bacd"
Example 2:

Input: s = "dcab", pairs = [[0,3],[1,2],[0,2]]
Output: "abcd"
Explaination: 
Swap s[0] and s[3], s = "bcad"
Swap s[0] and s[2], s = "acbd"
Swap s[1] and s[2], s = "abcd"
Example 3:

Input: s = "cba", pairs = [[0,1],[1,2]]
Output: "abc"
Explaination: 
Swap s[0] and s[1], s = "bca"
Swap s[1] and s[2], s = "bac"
Swap s[0] and s[1], s = "abc"
 

Constraints:

1 <= s.length <= 10^5
0 <= pairs.length <= 10^5
0 <= pairs[i][0], pairs[i][1] < s.length
s only contains lower case English letters.
*/
class DSU {
public:
    std::vector<int> parent;
    std::vector<int> rank;

    DSU(const int N) {
        parent = std::vector<int>(N);
        for (int node = 0; node < N; ++node) {
            parent[node] = node;
        }
        rank = std::vector<int>(N, 0);
    }

    int find(const int node) {
        if (parent[node] != node) {
            parent[node] = find(parent[node]);
        }
        return parent[node];
    }

    void join(const int x, const int y) {
        const int xr = find(x);
        const int yr = find(y);
        if (xr == yr) {
            return;
        }
        if (rank[xr] < rank[yr]) {
            parent[xr] = yr;
        } else if (rank[xr] > rank[yr]) {
            parent[yr] = xr;
        } else {
            parent[xr] = yr;
            ++rank[yr];
        }
    }
};

class Solution {
private:
    static const int ALPH_SZ = 26;
    
    int to_index(const char c) {
        return c - 'a';
    }

    std::string solution1(std::string& S, const std::vector<std::vector<int>>& pairs) {
        const int N = S.size();  
        auto dsu = DSU(N);
        for (const auto& pair : pairs) {
            dsu.join(pair[0], pair[1]);
        }

        auto swappable_indices = std::unordered_map<int,std::vector<int>>(); 
        for (int i = 0; i < N; ++i) {
            swappable_indices[dsu.find(i)].push_back(i);
        }

        for (auto& it : swappable_indices) {
            auto& indices = it.second;
            std::sort(indices.begin(), indices.end());
            std::string sorted_str = "";   
            sorted_str.reserve(indices.size());
            for (const auto i : indices) {
                sorted_str += S[i];
            }
            std::sort(sorted_str.begin(), sorted_str.end());
            int index = 0;
            for (const auto i : indices) {
                S[i] = sorted_str[index++];
            }
        }
        
        return S;
    }
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        return solution1(s, pairs);
    }
};
