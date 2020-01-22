/*
Given a string S, check if the letters can be rearranged so that two characters that are adjacent to each other are not the same.
If possible, output any possible result.  If not possible, return the empty string.

Example 1:
Input: S = "aab"
Output: "aba"

Example 2:
Input: S = "aaab"
Output: ""

Note:
S will consist of lowercase letters and have length in range [1, 500].
*/
class Solution {
private:
    static const int ALPH_SZ = 26;

    typedef std::pair<char,int> Node;

    int index(const char c) {
        return c - 'a';
    }
    
    char letter(const int i) {
        return i + 'a';
    }

    std::string solution1(const std::string& S) {
        /* Time-Complexity:     O(N + ALPH_SZ*log(ALPH_SZ) + N*log(ALPH_SZ))
         * Space-Complexity:    O(ALPH_SZ)
         */
        if (S.empty()) {
            return "";
        }
        const int N = S.size();
        // O(N)
        auto freq = std::vector<int>(ALPH_SZ, 0);
        for (const char c : S) {
            freq[index(c)]++;
        }
        // Check whether a solution is even possible
        for (const auto f : freq) {
            if (f > (N+1)/2) {
                return "";
            }
        }
        const auto cmp =    []
                            (const Node& node1, const Node& node2) -> bool {
                                return node1.second < node2.second;
                            }; 
        // O(ALPH_SZ * log(ALPH_SZ))
        auto PQ = std::priority_queue<Node, std::vector<Node>, decltype(cmp)>(cmp);
        for (int i = 0; i < ALPH_SZ; ++i) {
            if (freq[i]) {
                PQ.push({letter(i), freq[i]});
            }
        }
        
        // O(N * log(ALPH_SZ))
        auto output = std::string(N, ' ');
        int i = 0;
        while (not PQ.empty()) {
            auto v1 = PQ.top(); PQ.pop();
            while (v1.second > 1 and not PQ.empty()) {
                auto v2 = PQ.top(); PQ.pop();
                output[i++] = v1.first;
                output[i++] = v2.first;
                --v2.second;
                if (v2.second) {
                    PQ.push(v2);
                }
                --v1.second;
            }
            output[i++] = v1.first;
        }

        return output; 
    }
public:
    string reorganizeString(string S) {
        return solution1(S);   
    }
};
