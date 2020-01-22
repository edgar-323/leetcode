/*
There is a new alien language which uses the latin alphabet. 
However, the order among letters are unknown to you. 
You receive a list of non-empty words from the dictionary, 
where words are sorted lexicographically by the rules of this new language. 
Derive the order of letters in this language.

Example 1:
Input:
[
  "wrt",
  "wrf",
  "er",
  "ett",
  "rftt"
]
Output: "wertf"

Example 2:
Input:
[
  "z",
  "x"
]
Output: "zx"

Example 3:
Input:
[
  "z",
  "x",
  "z"
] 
Output: "" 
Explanation: The order is invalid, so return "".

Note:
You may assume all letters are in lowercase.
You may assume that if a is a prefix of b, then a must appear before b in the given dictionary.
If the order is invalid, return an empty string.
There may be multiple valid order of letters, return any one of them is fine.
*/
class Solution {
private:
    std::vector<std::vector<bool>> adj_matrix;
    std::vector<bool> is_vertex;
    std::string ordering;
    
    static const int ALPH_SZ = 26;

    int index(const char c) {
        return c - 'a';
    }

    char to_char(const int index) {
        return index + 'a';
    }

    void build_graph(const std::vector<std::string>& words) {
		const int W = words.size();
        adj_matrix = std::vector<std::vector<bool>>( ALPH_SZ, std::vector<bool>( ALPH_SZ, false ) );
        is_vertex = std::vector<bool>( ALPH_SZ, false );
        for (int w = 0; w < W; ++w) {
            const auto& word = words[w];
            const int M = word.size();
            // First we will do ordering for current word letters
            for (int i = 0; i < M; ++i) { 
                is_vertex[index(word[i])] = true;
                for (int j = i+1; j < M; ++j) {
                    if (word[i] != word[j]) {
                        //adj_matrix[index(word[i])][index(word[j])] = true;
                    }
                }   
            }
	        if (w == W-1) {
                continue;
            }
            // Next we make edges for the rest of the words
			const auto& next = words[w+1];
			const int N = next.size();
            int i = 0;
            while (i < std::min(M,N) and word[i] == next[i]) {
                ++i;
            }
            if (i < std::min(M,N)) {
                adj_matrix[index(next[i])][index(word[i])] = true;
            }
        }
    }

    bool can_order(const int node, std::vector<bool>& recently_seen, std::vector<bool>& visited) {
        //cout << "Visiting Node " << to_char(node) << "..." << endl;
        if (recently_seen[node]) {
            //cout << "Recently Seen " << to_char(node) << " (FAIL)" << endl;
            return false;
        } else if (visited[node]) {
            //cout << "Already Visited " << to_char(node) << " (OK)" << endl;
            return true;
        }
        visited[node] = true;
        recently_seen[node] = true;
        for (int neighbor = 0; neighbor < ALPH_SZ; ++neighbor) {
            if (adj_matrix[node][neighbor] and not can_order(neighbor, recently_seen, visited)) {
                //cout << "EXITING " << to_char(node) << endl;
                return false; 
            }
        }
        recently_seen[node] = false;
        ordering += std::string(1, to_char(node));
        //cout << "EXITING " << to_char(node) << endl;
        return true;
    }

    bool can_build_node_ordering() {
        ordering = "";
        auto visited = std::vector<bool>( ALPH_SZ, false );
        auto recently_seen = std::vector<bool>( ALPH_SZ, false );
        
        for (int node = 0; node < ALPH_SZ; ++node) {
            if (is_vertex[node] and not can_order(node, recently_seen, visited)) {
                return false;
            }
        }

        return true;
    }
    
    std::string solution1(const std::vector<std::string>& words) {
        build_graph(words);

        return can_build_node_ordering() ? ordering : ""; 
    }
public:
    string alienOrder(vector<string>& words) {
        return solution1(words);        
    }
};

