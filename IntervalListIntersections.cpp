/*
Given two lists of closed intervals, each list of intervals is pairwise disjoint and in sorted order.
Return the intersection of these two interval lists.
Formally, a closed interval [a, b] (with a <= b) denotes the set of real numbers x with a <= x <= b.  
The intersection of two closed intervals is a set of real numbers that is either empty, 
or can be represented as a closed interval.  
For example, the intersection of [1, 3] and [2, 4] is [2, 3].

Example 1:
Input: A = [[0,2],[5,10],[13,23],[24,25]], B = [[1,5],[8,12],[15,24],[25,26]]
Output: [[1,2],[5,5],[8,10],[15,23],[24,24],[25,25]]
Reminder: The inputs and the desired output are lists of Interval objects, and not arrays or lists.
 
Note:
0 <= A.length < 1000
0 <= B.length < 1000
0 <= A[i].start, A[i].end, B[i].start, B[i].end < 10^9
NOTE: input types have been changed on April 15, 2019. Please reset to default code definition to get new method signature.

*/
class Solution {
private:
    typedef std::vector<int> Interval;
    static const int START = 0;
    static const int END = 1;

    std::vector<int> get_intersection(const Interval& x, const Interval& y) {
        return  x[START] <= y[START] and y[START] <= x[END] ?
                Interval{ y[START], std::min( y[END], x[END] ) } :
                y[START] <= x[START] and x[START] <= y[END] ?
                Interval{ x[START], std::min( x[END], y[END] ) } :
                Interval{};
    }

    std::vector<Interval> solution1(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
        const int M = A.size();
        const int N = B.size();

        auto intersections = std::vector<Interval>(); 

        int i = 0;
        int j = 0;

        while (i < M and j < N) {
            const auto& x = A[i];
            const auto& y = B[j];
            const auto intersection = get_intersection(x, y); 

            if (not intersection.empty()) {
                intersections.push_back(intersection);
            }

            if (x[END] <= y[END]) {
                ++i;
            } else {
                ++j;
            }
        }

        return intersections; 
    }
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
        return solution1(A, B); 
    }
};
