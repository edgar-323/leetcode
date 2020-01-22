/*
Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.

Example 1:
Input: [[1,1],[2,2],[3,3]]
Output: 3
Explanation:
^
|
|        o
|     o
|  o  
+------------->
0  1  2  3  4

Example 2:
Input: [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
Output: 4
Explanation:
^
|
|  o
|     o        o
|        o
|  o        o
+------------------->
0  1  2  3  4  5  6

NOTE: input types have been changed on April 15, 2019. Please reset to default code definition to get new method signature.
*/
class Solution {
private:
    typedef std::unordered_map<std::string,int> Slopes;
    typedef std::vector<int> Point;
    static const int X = 0;
    static const int Y = 1;

    int N;

    std::string get_slope(const int x1, const int y1, const int x2, const int y2) {
        const auto x_diff = x1 - x2;
        const auto y_diff = y1 - y2;
        const auto gcd = std::__gcd(x_diff, y_diff);
        return std::to_string(x_diff / gcd) + "#" + std::to_string(y_diff / gcd);
    }

    void add_line(
            const Point& p1, 
            const Point& p2, 
            Slopes& slopes,
            int& max_pts, 
            int& duplicates_pts) {

        const auto x1 = p1[X];
        const auto y1 = p1[Y];
        const auto x2 = p2[X];
        const auto y2 = p2[Y];
        
        if (x1 == x2 and y1 == y2) {
            ++duplicates_pts;
        } else {
            const auto slope = get_slope(x1, y1, x2, y2);
            if (not slopes.count(slope)) {
                slopes[slope]++;
            }
            slopes[slope]++;
            max_pts = std::max(max_pts, slopes[slope]);
        }
    }

    int get_max_pts(const int i, const std::vector<Point>& points) {
        auto slopes = Slopes();
        int max_pts = 1;
        int duplicates_pts = 0;
        for (int j = i+1; j < N; ++j) {
            add_line(points[i], points[j], slopes, max_pts, duplicates_pts);
        }
        return max_pts + duplicates_pts;
    }

    int solution1(const std::vector<Point>& points) {
        N = points.size();
        if (N < 3) {
            return N;
        }
        int max_pts = 1;
        for (int i = 0; i < N-1; ++i) {
            max_pts = std::max( max_pts, get_max_pts(i, points) );
        }
        return max_pts;
    }
public:
    int maxPoints(vector<vector<int>>& points) {
        return solution1(points); 
    }
};
