/*
Given an array of strings, group anagrams together.

Example:
Input: ["eat", "tea", "tan", "ate", "nat", "bat"],
Output:
[
  ["ate","eat","tea"],
  ["nat","tan"],
  ["bat"]
]

Note:
All inputs will be in lowercase.
The order of your output does not matter.
*/

class Solution {
private:
    vector<vector<string>> solution1(vector<string>& strs) {
        vector<vector<string>> results;
        std::unordered_map<string, vector<string>> map;
        for (string& s : strs) {
            string str = s;
            std::sort(str.begin(), str.end());
            if (map.count(str)) {
                vector<string>& list = map.at(str);
                list.push_back(s);
            } else {
                vector<string> vec;
                vec.push_back(s);
                map.emplace(str, vec);
            }
        }
        for (auto& e : map) {
            results.push_back(e.second);
        }
        return results;
    }
    
    vector<vector<string>> solution2(vector<string>& strs) {
        vector<vector<string>> results;
        std::unordered_map<string, vector<string>> map;
        for (string& str : strs) {
            vector<int> counts(26, 0);
            for (char c : str) {
                counts[c - 'a'] += 1;
            }
            string key = "";
            for (int i = 0; i < 26; ++i) {
                key += ("#" + std::to_string(counts[i]));
            }
            if (map.count(key)) {
                vector<string>& list = map.at(key);
                list.push_back(str);
            } else {
                vector<string> list;
                list.push_back(str);
                map.emplace(key, list);
            }
        }
        for (auto& e : map) {
            results.push_back(e.second);
        }
        return results;
    }
    
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        return solution2(strs);
    }
};
