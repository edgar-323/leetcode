/*
A city's skyline is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance. 
Now suppose you are given the locations and height of all the buildings as shown on a cityscape photo (Figure A), 
write a program to output the skyline formed by these buildings collectively (Figure B).

The geometric information of each building is represented by a triplet of integers [Li, Ri, Hi], 
where Li and Ri are the x coordinates of the left and right edge of the ith building, respectively, and Hi is its height. 
It is guaranteed that 0 ≤ Li, Ri ≤ INT_MAX, 0 < Hi ≤ INT_MAX, and Ri - Li > 0. 
You may assume all buildings are perfect rectangles grounded on an absolutely flat surface at height 0.

For instance, the dimensions of all buildings in Figure A are recorded as: 
[ [2 9 10], [3 7 15], [5 12 12], [15 20 10], [19 24 8] ] .

The output is a list of "key points" (red dots in Figure B) in the format of [ [x1,y1], [x2, y2], [x3, y3], ... ] that uniquely defines a skyline. 
A key point is the left endpoint of a horizontal line segment. 
Note that the last key point, where the rightmost building ends, is merely used to mark the termination of the skyline, 
and always has zero height. 
Also, the ground in between any two adjacent buildings should be considered part of the skyline contour.

For instance, the skyline in Figure B should be represented as:[ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ].

Notes:
The number of buildings in any input list is guaranteed to be in the range [0, 10000].
The input list is already sorted in ascending order by the left x position Li.
The output list must be sorted by the x position.
There must be no consecutive horizontal lines of equal height in the output skyline. 
For instance, [...[2 3], [4 5], [7 5], [11 5], [12 7]...] is not acceptable; 
the three lines of height 5 should be merged into one in the final output as such: [...[2 3], [4 5], [12 7], ...]
*/
class Solution {
private:
    static const int BOTTOM_LEFT = 0;
    static const int BOTTOM_RIGHT = 1;
    static const int HEIGHT = 2;
    static const int X = 0;
    static const int Y = 1;
    typedef std::vector<int> Building;
    typedef std::vector<int> Point;

    void update_skyline1(
           std::vector<Point>& skyline, 
           const int x, 
           const int y) {
        // if skyline change is not vertical -> add new coordinate
        if (skyline.empty() or skyline.back()[X] != x) {
            skyline.push_back( Point{ x, y } );
        } else {
            // update last coordinate height
            skyline.back()[Y] = y;
        }
    }

    std::vector<Point> merge_sky_lines1(
                                const std::vector<Point>& left,
                                const std::vector<Point>& right) {
        const int M = left.size();
        const int N = right.size();

        int left_index = 0;
        int right_index = 0;
        int curr_height = 0;
        int curr_left_height = 0;
        int curr_right_height = 0;


        auto skyline = std::vector<Point>();

        // While we're in the region where both skylines are present
        while (left_index < M and right_index < N) {
            const auto& left_point = left[left_index];
            const auto& right_point = right[right_index];
            // pick smallest x
            int x;
            if (left_point[X] < right_point[X]) {
                x = left_point[X];
                curr_left_height = left_point[Y];
                ++left_index;
            } else {
                x = right_point[X];
                curr_right_height = right_point[Y];
                ++right_index;
            }
            // get max height btwn both skylines
            const int max_height = std::max(curr_left_height, curr_right_height);
            // update our skyline if there is a skyline change
            if (curr_height != max_height) {
                update_skyline1(skyline, x, max_height);
                curr_height = max_height;
            }
        }
        // there is only one left skyline
        while (left_index < M) {
            const auto& point = left[left_index++];
            if (curr_height != point[Y]) {
                update_skyline1(skyline, point[X], point[Y]);
                curr_height = point[Y];
            } 
        }
        // there is only one right skyline
        while (right_index < N) {
            const auto& point = right[right_index++];
            if (curr_height != point[Y]) {
                update_skyline1(skyline, point[X], point[Y]);
                curr_height = point[Y];
            }
        }
                
        return skyline; 
    }

	std::vector<Point> recurse1(const std::vector<Building>& buildings) {
        if (buildings.empty()) {
            return {};
        } else if (buildings.size() == 1) {
            return std::vector<Point>{
                        Point{ buildings[0][BOTTOM_LEFT],  buildings[0][HEIGHT] },
                        Point{ buildings[0][BOTTOM_RIGHT], 0                    }};
        }
        const int N = buildings.size();
        
        const auto left_sky_line =  recurse1(std::vector<Building>( 
                                                buildings.begin(),  
                                                buildings.begin() + N/2));
        const auto right_sky_line = recurse1(std::vector<Building>( 
                                                buildings.begin() + N/2,
                                                buildings.end()));
        
        return merge_sky_lines1(left_sky_line, right_sky_line);
    }


    std::vector<std::vector<int>> solution1(const std::vector<std::vector<int>>& buildings) {
        /* Time-Complexity:     O(N*log(N))
         * Space-Complexity:    O(N)
         */
        // Explanation: https://leetcode.com/problems/the-skyline-problem/solution/
        return recurse1(buildings);
    }
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        return solution1(buildings);        
    }
};
