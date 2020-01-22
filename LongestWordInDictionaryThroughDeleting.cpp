/*
Given a string and a string dictionary, find the longest string in the dictionary that can be formed by deleting some characters of the given string. If there are more than one possible results, return the longest word with the smallest lexicographical order. If there is no possible result, return the empty string.

Example 1:
Input:
s = "abpcplea", d = ["ale","apple","monkey","plea"]

Output: 
"apple"
Example 2:
Input:
s = "abpcplea", d = ["a","b","c"]

Output: 
"a"
Note:
All the strings in the input will only contain lower-case letters.
The size of the dictionary won't exceed 1,000.
The length of all the strings in the input won't exceed 1,000.
*/
class Solution {
private:
    std::string solution1(const std::string& S, const std::vector<std::string>& words) {
        /* Time-Complexty:  O(M * K)
         * Space-Complexty: O(1)
         *      Where:
         *          K = len(words)
         */
        auto ans = std::string();
        const int M = S.size();
        for (const auto& word : words) {
            const int N = word.size();
            int j = 0;
            for (int i = 0; i < M and j < N; ++i) {
                if (S[i] == word[j]) {
                    ++j;
                }
            }
            if (j == N and (N > ans.size() or N == ans.size() and ans > word)) {
                ans = word;
            }
        }
        
        return ans; 
    }
public:
    string findLongestWord(string s, vector<string>& d) {
        return solution1(s, d);
    }
};
