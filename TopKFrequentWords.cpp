/*
Given a non-empty list of words, return the k most frequent elements.

Your answer should be sorted by frequency from highest to lowest. If two words have the same frequency, then the word with the lower alphabetical order comes first.

Example 1:
Input: ["i", "love", "leetcode", "i", "love", "coding"], k = 2
Output: ["i", "love"]
Explanation: "i" and "love" are the two most frequent words.
    Note that "i" comes before "love" due to a lower alphabetical order.
Example 2:
Input: ["the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"], k = 4
Output: ["the", "is", "sunny", "day"]
Explanation: "the", "is", "sunny" and "day" are the four most frequent words,
    with the number of occurrence being 4, 3, 2 and 1 respectively.
Note:
You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Input words contain only lowercase letters.
Follow up:
Try to solve it in O(n log k) time and O(n) extra space.
*/
class Solution {
private:
    typedef std::pair<std::string,int> Node;

    std::vector<std::string> solution1(const std::vector<std::string>& words, const int K) {
        auto freq = std::unordered_map<std::string,int>();
        for (const auto& word : words) {
            ++freq[word];
        }
        // PQ sorts by max on default.
        // So we keep node1 at bottom if it is "less than" node2.
        // If node1 freq is less than node2 freq then it should go on top -> greater than -> false
        // If node1 feeq is greater than node2 freq then it should go on bottom -> less than -> true
        // Same freq, then we want node with lower lexo order -> so keep node1 at bottom of its string is less than node2 string.
        const auto cmp =    []
                            (const Node& node1, const Node& node2) {
                                return  node1.second < node2.second ?
                                        false :
                                        node1.second > node2.second ?
                                        true :
                                        node1.first < node2.first;
                            };
        auto PQ = std::priority_queue<Node, std::vector<Node>, decltype(cmp)>(cmp);
        for (const auto& it : freq) {
            PQ.push({it.first, it.second});
            if (PQ.size() > K) {
                PQ.pop();
            }
        }
        auto results = std::vector<std::string>();
        results.reserve(K); 
        while (not PQ.empty()) {
            results.push_back(PQ.top().first);
            PQ.pop();
        }
        // Since this heap keep min frequencies at top, we will get word with least freq everytime we pop. so we reverse at the end.
        std::reverse(results.begin(), results.end());

        return results;
    }
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        return solution1(words, k);       
    }
};
