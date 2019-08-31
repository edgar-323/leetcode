/*

Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, add spaces in s to construct a sentence where each word is a valid dictionary word. Return all such possible sentences.

Note:
The same word in the dictionary may be reused multiple times in the segmentation.
You may assume the dictionary does not contain duplicate words.

Example 1:
Input:
s = "catsanddog"
wordDict = ["cat", "cats", "and", "sand", "dog"]
Output:
[
  "cats and dog",
  "cat sand dog"
]

Example 2:
Input:
s = "pineapplepenapple"
wordDict = ["apple", "pen", "applepen", "pine", "pineapple"]
Output:
[
  "pine apple pen apple",
  "pineapple pen apple",
  "pine applepen apple"
]
Explanation: Note that you are allowed to reuse a dictionary word.

Example 3:
Input:
s = "catsandog"
wordDict = ["cats", "dog", "sand", "and", "cat"]
Output:
[]

*/
class Solution {
private:
    /***********************************************************************/
    bool startsWith(std::string& s, std::string& t) {
        // return whether `t` is a prefix of string `s`.
        const int S = s.size();
        const int T = t.size();
        if (S < T) {
            return false;
        }
        for (int i = 0; i < T; ++i) {
            if (s[i] != t[i]) {
                return false;
            }
        }
        return true;
    }
    bool containsKey(std::unordered_map<std::string, 
                        std::vector<std::string>>& map, 
                     std::string& key) {
        return map.count(key) > 0;
    }
    std::vector<std::string> DFS(std::string& s, 
                                std::vector<std::string> wordDict,
                                std::unordered_map<std::string, 
                                    std::vector<std::string>>& map) {
        // returns array that includes all substrings derived from s
        if (containsKey(map, s)) {
            return map.at(s);
        }

        std::vector<std::string> results;
        for (std::string& word : wordDict) {
            if (startsWith(s, word)) {
                std::string next = s.substr(word.length());
                if (next.empty()) {
                    results.push_back(word);
                } else {
                    std::vector<std::string> sublist = DFS(next, wordDict, map);
                    for (std::string& sub : sublist) {
                        results.push_back(word + " " + sub);
                    }
                }
            }   
        }
        map.insert(std::make_pair(s, results));
        return results;
    }
    std::vector<std::string> solution1(std::string& s, 
                                        std::vector<std::string>& wordDict) {
        std::unordered_map<std::string, std::vector<std::string>> map;
        return DFS(s, wordDict, map);
    }
    /***********************************************************************/
public:
    std::vector<std::string> wordBreak(std::string s, std::vector<std::string>& wordDict) {
        return solution1(s, wordDict);
    }
};


