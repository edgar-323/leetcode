/*
You have k lists of sorted integers in ascending order. Find the smallest range that includes at least one number from each of the k lists.
We define the range [a,b] is smaller than range [c,d] if b-a < d-c or a < c if b-a == d-c.

Example 1:
Input: [[4,10,15,24,26], [0,9,12,20], [5,18,22,30]]
Output: [20,24]
Explanation: 
List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
List 2: [0, 9, 12, 20], 20 is in range [20,24].
List 3: [5, 18, 22, 30], 22 is in range [20,24].

Note:
The given list may contain duplicates, so ascending order means >= here.
1 <= k <= 3500
-105 <= value of elements <= 105.
*/
class Solution {
private:
    std::vector<int> solution1(const std::vector<std::vector<int>>& lists) {
        /* Time-Complexity:     O(N*log(K))
         * Space-Complexity:    O(K)
         *      Where:
         *          N = ∑ { lists[i].size() | i € {0,...,K-1} }
         */
        const int K = lists.size();
        auto next = std::vector<int>(K, 0);
        auto cmp =  [&next, &lists] 
                    (const int i, const int j) -> bool
                    {
                        return lists[i][next[i]] > lists[j][next[j]];
                    };
        auto PQ = std::priority_queue<int, std::vector<int>, decltype(cmp)>(cmp);
        int max_val = INT_MIN;
        for (int i = 0; i < K; ++i) {
            PQ.push(i);
            max_val = std::max(max_val, lists[i][0]);
        }
        int min_range = INT_MAX;
        int begin = -1;
        int end = -1;
        while (PQ.size() == K) {
            const auto i = PQ.top(); PQ.pop();
            if (max_val - lists[i][next[i]] < min_range) {
                min_range = max_val - lists[i][next[i]];
                begin = lists[i][next[i]];
                end = max_val;
            }
            if (++next[i] < lists[i].size()) {
                max_val = std::max(max_val, lists[i][next[i]]); 
                PQ.push(i);
            }
        }

        return {begin, end};
    }
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        return solution1(nums); 
    }
};
