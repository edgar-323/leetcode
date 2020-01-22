/*
Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).
You may assume that the intervals were initially sorted according to their start times.

Example 1:
Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]

Example 2:
Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].

NOTE: input types have been changed on April 15, 2019. Please reset to default code definition to get new method signature.
*/
class Solution {
private:
    static const int begin = 0;
    static const int end = 1;
    typedef std::vector<int> Interval;

    std::vector<Interval> solution1(const std::vector<Interval>& intervals, const std::vector<int>& new_interval) {
        const int N = intervals.size();
        auto results = std::vector<Interval>();

        int i = 0;
        
        while (i < N and intervals[i][begin] < new_interval[begin]) {
            results.push_back(intervals[i++]);    
        }
        
        if (results.empty() or results.back()[end] < new_interval[begin]) {
            // Either new_interval begins before all other intervals begin, or new_interval is NOT overlapping with the
            // last interval (which starts before new_interval) that we added 
            results.push_back(new_interval);
        } else {
            // There is at least one interval in results and the last one is overlapping with new_interval so we merge them
            results.back()[end] = std::max(results.back()[end], new_interval[end]);
        }

        while (i < N) {
            if (results.back()[end] < intervals[i][begin]) {
                // No conflict => Just add next interval
                results.push_back(intervals[i]);
            } else {
                // Conflict => Merge Intervals
                results.back()[end] = std::max(results.back()[end], intervals[i][end]);
            }
            ++i;
        }

        return results;
    }
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        return solution1(intervals, newInterval);        
    }
};
