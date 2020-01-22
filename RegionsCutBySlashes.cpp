/*
In a N x N grid composed of 1 x 1 squares, each 1 x 1 square consists of a /, \, or blank space.  These characters divide the square into contiguous regions.
(Note that backslash characters are escaped, so a \ is represented as "\\".)
Return the number of regions.

Example 1:
Input:
[
  " /",
  "/ "
]
Output: 2
Explanation: The 2x2 grid is as follows:

Example 2:
Input:
[
  " /",
  "  "
]
Output: 1
Explanation: The 2x2 grid is as follows:

Example 3:
Input:
[
  "\\/",
  "/\\"
]
Output: 4
Explanation: (Recall that because \ characters are escaped, "\\/" refers to \/, and "/\\" refers to /\.)
The 2x2 grid is as follows:

Example 4:
Input:
[
  "/\\",
  "\\/"
]
Output: 5
Explanation: (Recall that because \ characters are escaped, "/\\" refers to /\, and "\\/" refers to \/.)
The 2x2 grid is as follows:

Example 5:
Input:
[
  "//",
  "/ "
]
Output: 3
Explanation: The 2x2 grid is as follows:

Note:
1 <= grid.length == grid[0].length <= 30
grid[i][j] is either '/', '\', or ' '.
*/
class DSU {
public:
    std::vector<int> parent;
    DSU(const int N) {
        parent = std::vector<int>(N); 
        for (int i = 0; i < N; ++i) {
            parent[i] = i;
        }
    }

    int find(const int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void join(const int x, const int y) {
        parent[find(x)] = find(y);
    }  
};
class Solution {
private:
    int solution1(std::vector<std::string>& grid) {
        const int N = grid.size();
        auto dsu = DSU(4*N*N);

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                const int root = 4 * (i * N + j);
                const char val = grid[i][j];
                if (val != '\\') {
                    dsu.join(root + 0, root + 1);
                    dsu.join(root + 2, root + 3);
                }
                if (val != '/') {
                    dsu.join(root + 0, root + 2);
                    dsu.join(root + 1, root + 3);
                }
                if (i + 1 < N) {
                    dsu.join(root + 3, (root + 4 * N) + 0);
                }
                if (i - 1 >= 0) {
                    dsu.join(root + 0, (root - 4 * N) + 3);
                }
                if (j + 1 < N) {
                    dsu.join(root + 2, (root + 4) + 1);
                }
                if (j - 1 >= 0) {
                    dsu.join(root + 1, (root - 4) + 2);
                }
            }
        }
        
        int connected_components = 0; 
        for (int x = 0; x < 4 * N * N; ++x) {
            // is x the representative (root) of its set ?
            if (dsu.find(x) == x) {
                ++connected_components;
            }
        }
    
        return connected_components;
    }
public:
    int regionsBySlashes(vector<string>& grid) {
        return solution1(grid);       
    }
};
