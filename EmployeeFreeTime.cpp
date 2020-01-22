/*
We are given a list schedule of employees, which represents the working time for each employee.
Each employee has a list of non-overlapping Intervals, and these intervals are in sorted order.
Return the list of finite intervals representing common, positive-length free time for all employees, also in sorted order.
Even though we are representing Intervals in the form [x, y], the objects inside are Intervals, not lists or arrays. 
For example, schedule[0][0].start = 1, schedule[0][0].end = 2, and schedule[0][0][0] is not defined.  
Also, we wouldn't include intervals like [5, 5] in our answer, as they have zero length.

Example 1:
Input: schedule = [[[1,2],[5,6]],[[1,3]],[[4,10]]]
Output: [[3,4]]
Explanation: There are a total of three employees, and all common
free time intervals would be [-inf, 1], [3, 4], [10, inf].
We discard any intervals that contain inf as they aren't finite.

Example 2:
Input: schedule = [[[1,3],[6,7]],[[2,4]],[[2,5],[9,12]]]
Output: [[5,6],[7,9]]

Constraints:
1 <= schedule.length , schedule[i].length <= 50
0 <= schedule[i].start < schedule[i].end <= 10^8
*/
/*
// Definition for an Interval.
class Interval {
public:
    int start;
    int end;

    Interval() {}

    Interval(int _start, int _end) {
        start = _start;
        end = _end;
    }
};
*/
class Solution {
private:
    typedef std::pair<Interval, int> Node;

    std::vector<Interval> solution1(const std::vector<std::vector<Interval>>& schedules) {
        /* Time-Complexity:     O()
         * Space-Complexity:    O()
         */
        const int N = schedules.size();
        const auto cmp =    []
                            (const Node& node1, const Node& node2) -> bool
                            {
                                return node1.first.start > node2.first.start;
                            };
        auto PQ = std::priority_queue<Node, std::vector<Node>, decltype(cmp)>(cmp);
        for (int i = 0; i < N; ++i) {
            PQ.push({ schedules[i][0], i });
        }
        auto next = std::vector<int>(N, 1);
        auto results = std::vector<Interval>();
        int end = INT_MIN; 
        while (not PQ.empty()) {
            const auto node = PQ.top(); PQ.pop();
            const auto& interval = node.first;
            const auto& index = node.second;
            if (interval.start > end and end != INT_MIN) {
                results.push_back(Interval(end, interval.start)); 
            }
            if (next[index] < schedules[index].size()) {
                PQ.push({ schedules[index][next[index]++], index }); 
            }
            end = std::max(end, interval.end);
        }
        return results;
    }
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
        return solution1(schedule);        
    }
};
