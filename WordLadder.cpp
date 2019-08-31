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

    int solution1(
            const std::string& beginWord,
            const std::string& endWord, 
            const std::vector<std::string>& wordList) {
        const int N = endWord.size();
        std::unordered_set<std::string> dictionary(
                                            wordList.begin(), 
                                            wordList.end());
        std::unordered_set<std::string> seen;
        
        int minTransforms = 1;
        std::queue<std::string> Q;
        Q.push(beginWord);

        while (!Q.empty()) {
            for (size_t size = Q.size(); size > 0; --size) {
                const std::string curr = Q.front(); Q.pop();
                if (curr == endWord) {
                    return minTransforms;
                }
                for (int i = 0; i < N; ++i) {
                    for (int j = 0; j < ALPH_SZ; ++j) {
                        const char c = char(int('a') + j);
                        const std::string s =   curr.substr(0, i) + 
                                                std::string(1, c) + 
                                                curr.substr(i+1);
                        if (!seen.count(s) and dictionary.count(s)) {
                            Q.push(s);
                            seen.insert(s);
                        }
                    }
                }
            }
            ++minTransforms;
        }
        
        return 0;
    }
public:
    int ladderLength(std::string beginWord, std::string endWord, std::vector<std::string>& wordList) {
       return solution1(beginWord, endWord, wordList); 
    }
};
