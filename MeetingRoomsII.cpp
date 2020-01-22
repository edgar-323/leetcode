/*
Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms required.

Example 1:
Input: [[0, 30],[5, 10],[15, 20]]
Output: 2

Example 2:
Input: [[7,10],[2,4]]
Output: 1
*/

class Solution {
private:
    typedef std::vector<int> Interval;
    static const int START = 0;
    static const int END = 1;

    int solution1(std::vector<Interval>& intervals) {
        if (intervals.empty()) {
            return 0;
        }

        const int N = intervals.size();
        auto PQ = std::priority_queue<int, std::vector<int>, std::greater<int>>(); 
        std::sort(intervals.begin(), intervals.end(), 
                    [](const Interval& x, const Interval& y) -> bool 
                    { 
                        return x[START] < y[START]; 
                    });
        PQ.push(intervals[0][END]);
        
        for (int i = 1; i < N; ++i) {
            if (intervals[i][START] >= PQ.top()) {
                PQ.pop();
            }
            PQ.push(intervals[i][END]);
        }

        return PQ.size();
    }

public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        return solution1(intervals); 
    }
};
