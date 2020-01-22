/*
Given N axis-aligned rectangles where N > 0, 
determine if they all together form an exact cover of a rectangular region.
Each rectangle is represented as a bottom-left point and a top-right point. 
For example, a unit square is represented as [1,1,2,2]. 
(coordinate of bottom-left point is (1, 1) and top-right point is (2, 2)).

Example 1:
rectangles = [
  [1,1,3,3],
  [3,1,4,2],
  [3,2,4,4],
  [1,3,2,4],
  [2,3,3,4]
]
Return true. All 5 rectangles together form an exact cover of a rectangular region.

Example 2:
rectangles = [
  [1,1,2,3],
  [1,3,2,4],
  [3,1,4,2],
  [3,2,4,4]
]
Return false. Because there is a gap between the two rectangular regions.

Example 3:
rectangles = [
  [1,1,3,3],
  [3,1,4,2],
  [1,3,2,4],
  [3,2,4,4]
]
Return false. Because there is a gap in the top center.

Example 4:

rectangles = [
  [1,1,3,3],
  [3,1,4,2],
  [1,3,2,4],
  [2,2,4,4]
]
Return false. Because two of the rectangles overlap with each other.
*/
class Solution {
private:
    typedef std::vector<int> Rectangle;
    static const int X1 = 0;
    static const int Y1 = 1;
    static const int X2 = 2;
    static const int Y2 = 3;

    std::string get_point(const int x, const int y) {
        return std::to_string(x) + "#" + std::to_string(y);
    }

    bool solution1(const std::vector<Rectangle>& rectangles) {
        int x1 = INT_MAX;
        int y1 = INT_MAX;
        int x2 = INT_MIN;
        int y2 = INT_MIN;

        auto point_set = std::unordered_set<std::string>();
        int total_area = 0;

        for (const auto& rect : rectangles) {
            x1 = std::min( x1, rect[X1] );
            y1 = std::min( y1, rect[Y1] );
            x2 = std::max( x2, rect[X2] );
            y2 = std::max( y2, rect[Y2] );

            total_area += (rect[X2] - rect[X1]) * (rect[Y2] - rect[Y1]);

            const auto bottom_left = get_point(rect[X1], rect[Y1]);
            const auto bottom_right = get_point(rect[X2], rect[Y1]);
            const auto top_left = get_point(rect[X1], rect[Y2]);
            const auto top_right = get_point(rect[X2], rect[Y2]);

            if (not point_set.insert(bottom_left).second) {
                point_set.erase(bottom_left);
            }
            if (not point_set.insert(bottom_right).second) {
                point_set.erase(bottom_right);
            }
            if (not point_set.insert(top_left).second) {
                point_set.erase(top_left);
            }
            if (not point_set.insert(top_right).second) {
                point_set.erase(top_right);
            }
        }
        const auto expected_area = (x2 - x1) * (y2 - y1);

        return  total_area == expected_area and
                point_set.count(get_point(x1, y1)) and
                point_set.count(get_point(x1, y2)) and
                point_set.count(get_point(x2, y1)) and
                point_set.count(get_point(x2, y2)) and
                point_set.size() == 4;
    }
public:
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        return solution1(rectangles);        
    }
};
