/*
Given two words (beginWord and endWord), and a dictionary's word list, 
find all shortest transformation sequence(s) from beginWord to endWord, 
such that:
    1)  Only one letter can be changed at a time
    2)  Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
Note:
    1)  Return an empty list if there is no such transformation sequence.
    2)  All words have the same length.
    3)  All words contain only lowercase alphabetic characters.
    4)  You may assume no duplicates in the word list.
    5)  You may assume beginWord and endWord are non-empty and are not the same.

Example 1:
Input:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]
Output:
[
  ["hit","hot","dot","dog","cog"],
  ["hit","hot","lot","log","cog"]
]

Example 2:
Input:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]
Output: []
Explanation: The endWord "cog" is not in wordList, therefore no possible transformation.
*/
class Solution {
private:
    typedef std::vector<std::string> Path;
    typedef std::unordered_set<std::string> Words;
    typedef std::pair<Path, std::unordered_set<std::string>> Node;

    static const int ALPH_SZ = 26;

    int to_char(const char c) {
        return c + 'a';
    }

    /***********************************************************************************************/
    std::vector<Path> get_paths(std::queue<Node>& Q, const std::string& end_word) {
        auto results = std::vector<Path>();
        const int D = Q.front().first.size();
        while (not Q.empty() and Q.front().first.size() == D) {
            const auto& path = Q.front().first;
            if (path.back() == end_word) {
                results.push_back(path);
            }
            Q.pop();
        }
        return results;
    }

    std::vector<Path> solution1(
            const std::string& begin_word, 
            const std::string& end_word,
            const std::vector<std::string>& word_list) {
        /* MEMORY-LIMIT-EXCEEDED */ 
        const int K = begin_word.size();
        const auto dictionary = Words( word_list.begin(), word_list.end() );
        
        
        auto Q = std::queue<Node>();
        Q.push( { Path{begin_word}, Words() } ); 

        auto results = std::vector<Path>();

        while (not Q.empty()) {
            for (int size = Q.size(); size; --size, Q.pop()) {
                if (Q.front().first.back() == end_word) {
                    return get_paths(Q, end_word);
                }
                const auto& node = Q.front();
                auto path = node.first;
                auto seen = node.second;
                auto word = path.back();
                for (int i = 0; i < K; ++i) {
                    const char c = word[i];
                    for (int j = 0; j < ALPH_SZ; ++j) {
                        word[i] = to_char(j);
                        if (dictionary.count(word) and not seen.count(word)) {
                            path.push_back(word);
                            seen.insert(word);
                            Q.push({path, seen});
                            path.pop_back();
                            seen.erase(word);
                        }
                        word[i] = c;
                    }
                }
            }
        }
        
        return {};
    }
    /***********************************************************************************************/
    std::vector<Path> solution2(
                        const std::string& begin_word,
                        const std::string& end_word,
                        const std::vector<std::string>& word_list) {
        auto adj_list = get_adj_list(begin_word, word_list);
        auto dist = std::unordered_map<std::string, int>();
        auto path = Path();
        auto results = std::vector<Path>();

        BFS2( begin_word, end_word, adj_list, dist );
        DFS2( begin_word, end_word, adj_list, dist, path, results );

        return results;
    }
    
    std::unordered_map<std::string, std::vector<std::string>> get_adj_list(
                                                                    const std::string& begin_word, 
                                                                    const std::vector<std::string>& word_list) {
        auto dictionary = Words(word_list.begin(), word_list.end());
        if (not dictionary.count(begin_word)) {
            dictionary.insert(begin_word);
        }
        const int K = dictionary.begin()->size();
        auto adj_list = std::unordered_map<std::string, std::vector<std::string>>();
        for (const auto& word : dictionary) {
            auto neighbor = word;
            for (int i = 0; i < K; ++i) {
                const auto c = neighbor[i]; 
                for (int j = 0; j < ALPH_SZ; ++j) {
                    if (c == to_char(j)) {
                        continue;
                    }
                    neighbor[i] = to_char(j);
                    if (dictionary.count(neighbor)) {
                        adj_list[word].push_back(neighbor);
                    }
                }
                neighbor[i] = c;
            }
        }
        return adj_list;
    }

    void BFS2(
            const std::string& begin_word,
            const std::string& end_word,
            std::unordered_map<std::string, std::vector<std::string>>& adj_list,
            std::unordered_map<std::string, int>& dist) {
        
        auto Q = std::queue<std::string>();
        Q.push( begin_word );
        dist[begin_word] = 0;

        while (not Q.empty()) {
            auto found_end_word = false;
            for (int size = Q.size(); size and not found_end_word; --size) {
                const auto node = Q.front(); Q.pop();
                const auto d = dist[node];
                
                for (const auto& neighbor : adj_list[node]) {
                    if (not dist.count(neighbor)) {
                        dist[neighbor] = d+1;
                        if (neighbor == end_word) {
                            found_end_word = true;
                        } else {
                            Q.push(neighbor);
                        }
                    }
                }
            }
        }

    }

    void DFS2(
            const std::string& node,
            const std::string& end_node,
            std::unordered_map<std::string, std::vector<std::string>>& adj_list,
            std::unordered_map<std::string, int>& dist,
            Path& path,
            std::vector<Path>& results) {

        path.push_back(node);
        if (node == end_node) {
            results.push_back(path);
        } else {
            for (const auto& neighbor : adj_list[node]) {
                if (dist.count(neighbor) and dist[neighbor] == dist[node]+1) {
                    DFS2(neighbor, end_node, adj_list, dist, path, results);
                }
            }
        }
        path.pop_back();
    }
    /***********************************************************************************************/
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        return solution2(beginWord, endWord, wordList);
    }
};
