/*
In a warehouse, there is a row of barcodes, where the i-th barcode is barcodes[i].
Rearrange the barcodes so that no two adjacent barcodes are equal.  You may return any answer, and it is guaranteed an answer exists.
 
Example 1:
Input: [1,1,1,2,2,2]
Output: [2,1,2,1,2,1]

Example 2:
Input: [1,1,1,1,2,2,3,3]
Output: [1,3,1,3,2,1,2,1]

Note:
1 <= barcodes.length <= 10000
1 <= barcodes[i] <= 10000
*/
class Solution {
private:
    typedef std::pair<int,int> Node;
    std::vector<int> solution1(const std::vector<int>& barcodes) {
        auto freq = std::unordered_map<int,int>();
        for (const auto barcode : barcodes) {
            ++freq[barcode];
        }
        const auto cmp =    []
                            (const Node& node1, const Node& node2) -> bool {
                                return node1.second < node2.second;
                            }; 
        auto PQ = std::priority_queue<Node, std::vector<Node>, decltype(cmp)>(cmp);
        for (const auto& it : freq) {
            PQ.push({it.first, it.second});
        }
        
        const int N = barcodes.size();
        auto output = std::vector<int>(N);
        int i = 0;
        while (not PQ.empty()) {
            auto node1 = PQ.top(); PQ.pop();
            while (node1.second > 1 and not PQ.empty()) {
                auto node2 = PQ.top(); PQ.pop();
                output[i++] = node1.first;
                output[i++] = node2.first;
                --node2.second;
                if (node2.second) {
                    PQ.push(node2);
                }
                --node1.second;
            }
            output[i++] = node1.first;
        }

        return output;
    }
public:
    vector<int> rearrangeBarcodes(vector<int>& barcodes) {
        return solution1(barcodes);       
    }
};
