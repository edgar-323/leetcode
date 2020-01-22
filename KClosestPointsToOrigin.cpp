/*
We have a list of points on the plane.  
Find the K closest points to the origin (0, 0).
(Here, the distance between two points on a plane is the Euclidean distance.)
You may return the answer in any order.  
The answer is guaranteed to be unique (except for the order that it is in.)

Example 1:
Input: points = [[1,3],[-2,2]], K = 1
Output: [[-2,2]]
Explanation: 
The distance between (1, 3) and the origin is sqrt(10).
The distance between (-2, 2) and the origin is sqrt(8).
Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
We only want the closest K = 1 points from the origin, so the answer is just [[-2,2]].

Example 2:
Input: points = [[3,3],[5,-1],[-2,4]], K = 2
Output: [[3,3],[-2,4]]
(The answer [[-2,4],[3,3]] would also be accepted.)

Note:
1 <= K <= points.length <= 10000
-10000 < points[i][0] < 10000
-10000 < points[i][1] < 10000
*/
class Solution {
private:
    typedef std::vector<int> Point;

    std::vector<std::vector<int>> solution1(const vector<vector<int>>& points, const int K) {
        // C++ std::priority_queue<> will keep "biggest" (i.e., max elements at the top. So smaller elements will be kept at the bottom leaves.
        // Becuase of the nature of this problem, we want to keep smallest elements (i.e., those closest to origin) so our comparator uses "<" operator.
        const auto cmp =    []
                            (const Point& p1, const Point& p2) -> bool {
                                return p1[0]*p1[0] + p1[1]*p1[1] < p2[0]*p2[0] + p2[1]*p2[1]; 
                            };
        auto PQ = std::priority_queue<Point, std::vector<Point>, decltype(cmp)>(cmp);
         
        for (const auto& point : points) {
            PQ.push(point);
            // Always ensure that PQ size is at most K
            if (PQ.size() > K) {
                PQ.pop();
            }
        }
        // At this point `PQ` has closest K elements, so we extract them all.
        auto results = std::vector<Point>();
        results.reserve(K);
        while (not PQ.empty()) {
            results.push_back(PQ.top());
            PQ.pop();
        }

        return results; 
    }
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        return solution1(points, K); 
    }
};
