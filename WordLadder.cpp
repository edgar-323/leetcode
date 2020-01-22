/*
Given two words (beginWord and endWord), and a dictionary's word list, find the length of shortest transformation sequence from beginWord to endWord, such that:
Only one letter can be changed at a time.
Each transformed word must exist in the word list. 
Note that beginWord is not a transformed word.

Note:
Return 0 if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
You may assume no duplicates in the word list.
You may assume beginWord and endWord are non-empty and are not the same.

Example 1:
Input:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]
Output: 5
Explanation: As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.

Example 2:
Input:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]
Output: 0
Explanation: The endWord "cog" is not in wordList, therefore no possible transformation.
*/
class Solution {
    static const int ALPH_SZ = 26;

    char to_char(const int j) {
        return 'a' + j;
    }

    int solution1(
            const std::string& begin_word,
            const std::string& end_word,
            const std::vector<std::string>& word_list) {
        /* Time-Complexity:     O(ALPH_SZ*K*N)
         * Space-Complexity:    O(K*N)
         *      Where:
         *          N = # of words
         *          K = size of each word
         */
        const int K = end_word.size();
        const auto dictionary = std::unordered_set<std::string>(
                                        word_list.begin(), 
                                        word_list.end());
        
        auto seen = std::unordered_set<std::string>();
        std::queue<std::string> Q;
        Q.push(beginWord);

        int min_transformations = 1;

        while (not Q.empty()) {
            for (size_t size = Q.size(); size; --size, Q.pop()) {
                auto word = Q.front();
                if (word == end_word) {
                    return min_transformations;
                }
                for (int i = 0; i < K; ++i) {
                    const char c = word[i];
                    for (int j = 0; j < ALPH_SZ; ++j) {
                        word[i] = to_char(j);
                        if (dictionary.count(word) and not seen.count(word)) {
                            Q.push(next);
                            seen.insert(next);
                        }
                    }
                    word[i] = c;
                }
            }
            ++min_transformations;
        }
        // no transformation is possible
        return 0;
    }
public:
    int ladderLength(std::string beginWord, std::string endWord, std::vector<std::string>& wordList) {
       return solution1(beginWord, endWord, wordList); 
    }
};
