/*
Given a string, sort it in decreasing order based on the frequency of characters.

Example 1:

Input:
"tree"

Output:
"eert"

Explanation:
'e' appears twice while 'r' and 't' both appear once.
So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid answer.
Example 2:

Input:
"cccaaa"

Output:
"cccaaa"

Explanation:
Both 'c' and 'a' appear three times, so "aaaccc" is also a valid answer.
Note that "cacaca" is incorrect, as the same characters must be together.
Example 3:

Input:
"Aabb"

Output:
"bbAa"

Explanation:
"bbaA" is also a valid answer, but "Aabb" is incorrect.
Note that 'A' and 'a' are treated as two different characters.
*/

class Solution {
private:
    static const int ALPH_SZ = 48;


    typedef std::pair<char,int> Node;
    
    std::string solution1(std::string& S) {
        /* Time-Complexity:     O(M + K * log(K))
         * Space-Complexity:    O(K)
         *      Where:
         *          M = len(S)
         *          K = distinct_characters(S)
         */
        auto freqs = std::unordered_map<char,int>(); 
        for (const auto c : S) {
            ++freqs[c];
        }
        const auto cmp =    []
                            (const Node& node1, const Node& node2) -> bool {
                                return node1.second < node2.second;
                            };
        auto PQ = std::priority_queue<Node, std::vector<Node>, decltype(cmp)>(cmp);
        for (const auto& it : freqs) {
            PQ.push({it.first, it.second});
        }
        int index = 0;
        while (not PQ.empty()) {
            const auto c = PQ.top().first;
            const auto N = PQ.top().second;
            for (int _ = 0; _ < N; ++_) {
                S[index++] = c;
            }
            PQ.pop();
        }

        return S;
    }
public:
    string frequencySort(string s) {
        return solution1(s);        
    }
};
