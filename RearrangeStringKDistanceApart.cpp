/*
Given a non-empty string s and an integer k, rearrange the string such that the same characters are at least distance k from each other.

All input strings are given in lowercase to_letters. If it is not possible to rearrange the string, return an empty string "".

Example 1:

Input: s = "aabbcc", k = 3
Output: "abcabc" 
Explanation: The same to_letters are at least distance 3 from each other.
Example 2:

Input: s = "aaabc", k = 3
Output: "" 
Explanation: It is not possible to rearrange the string.
Example 3:

Input: s = "aaadbbcc", k = 2
Output: "abacabcd"
Explanation: The same to_letters are at least distance 2 from each other.
*/
class Solution {
private:
    typedef std::pair<char,int> Node;

    static const int ALPH_SZ = 26;

    int to_index(const char c) {
        return c - 'a';
    }

    char to_letter(const int i) {
        return i + 'a';
    }

    std::string solution1(const std::string& S, const int K) {
        /* Time-Complexity:     O(N*log(ALPH_SZ))
         * Space-Complexity:    O(N)
         */
        if (S.empty()) {
            return "";
        } else if (not K) {
            return S;
        }

        const int N = S.size();
        // O(N)
        auto freq = std::vector<int>(ALPH_SZ, 0);
        for (const auto& c : S) {
            ++freq[to_index(c)];
        }
        const auto cmp =    []
                            (const Node& node1, const Node& node2) -> bool {
                                return node1.second < node2.second;
                            };
        auto PQ = std::priority_queue<Node, std::vector<Node>, decltype(cmp)>(cmp);
        // O(ALPH_SZ * log(ALPH_SZ))
        for (int i = 0; i < ALPH_SZ; ++i) {
            if (freq[i]) {
                PQ.push({ to_letter(i), freq[i] }); 
            }
        }
        auto Q = std::queue<Node>();
        auto output = std::string(N, ' ');
        int index = 0;
        // O(N * log(ALPH_SZ))
        while (not PQ.empty()) {
            auto v = PQ.top(); PQ.pop();
            output[index++] = v.first;
            --v.second;
            Q.push(v);
            if (Q.size() == K) {
                v = Q.front(); Q.pop();
                if (v.second) {
                    PQ.push(v);
                }
            }
        }

        return index == N ? output : "";
    }
public:
    string rearrangeString(string s, int k) {
        return solution1(s, k);       
    }
};
