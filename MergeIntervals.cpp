/*
Given a collection of intervals, merge all overlapping intervals.

Example 1:
Input: [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].

Example 2:
Input: [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.

NOTE: input types have been changed on April 15, 2019. Please reset to default code definition to get new method signature.
*/

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
private:
    void swap(vector<Interval>& intervals, int i, int j) {
        Interval temp = intervals[i];
        intervals[i] = intervals[j];
        intervals[j] = temp;
    }
    
    int compare(Interval& x, Interval& y) {
        // return (x == y) ? 0 : ((x < y) ? -1 : 1);
        return (x.start == y.start) ? 
                ((x.end == y.end) ? 
                    0 : ((x.end < y.end) ? 
                            -1 : 1)) : 
                ((x.start < y.start) ? -1 : 1);
    }
    
    void mergeHalves(vector<Interval>& intervals, int start, int mid, int end) {
        vector<Interval> v;
        int i = start;
        int j = mid;
        while (i < mid || j < end) {
            if (i < mid && j < end) {
                int cmp = compare(intervals[i], intervals[j]);
                if (cmp <= 0) {
                    v.push_back(intervals[i++]);
                } else {
                    v.push_back(intervals[j++]);
                }
            } else if (i < mid) {
                v.push_back(intervals[i++]);
            } else {
                v.push_back(intervals[j++]);
            }
        }
        for (i = 0; start < end; ++i, ++start) {
            intervals[start] = v[i];
        }
    }
    
    void mergeRecurse(vector<Interval>& intervals, int start, int end) {
        int diff = end - start;
        if (diff <= 2) {
            if (diff == 2 && 
                compare(intervals[start], intervals[start+1]) > 0) {
                swap(intervals, start, start+1);
            }
        } else {
            int mid = (start + end) / 2;
            mergeRecurse(intervals, start, mid);
            mergeRecurse(intervals, mid, end);
            mergeHalves(intervals, start, mid, end);        
        }
    }
    
    void mergeSort(vector<Interval>& intervals) {
        mergeRecurse(intervals, 0, intervals.size());
    }
    
    vector<Interval> solution1(vector<Interval>& intervals) {
        /*
        MY SOLUTION 
        Time-Complexity:    O(N * log(N))
        Space-Complexity:   O(N)
        */
        vector<Interval> results;
        const int N = intervals.size();
        if (N == 0) {
            return results;
        }
        mergeSort(intervals);
        results.push_back(intervals[0]);
        for (int i = 1; i < N; ++i) {
            Interval& prev = results[results.size()-1];
            Interval& curr = intervals[i];
            if (prev.end < curr.start) {
                results.push_back(curr);
            } else if (prev.end == curr.start || prev.end < curr.end) {
                prev.end = curr.end;
            } 
        }
        return results;
    }
    
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        return solution1(intervals);        
    }
};
