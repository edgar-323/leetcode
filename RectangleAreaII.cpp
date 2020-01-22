/*
We are given a list of (axis-aligned) rectangles.  Each rectangle[i] = [x1, y1, x2, y2] , where (x1, y1) are the coordinates of the bottom-left corner, and (x2, y2) are the coordinates of the top-right corner of the ith rectangle.

Find the total area covered by all rectangles in the plane.  Since the answer may be too large, return it modulo 10^9 + 7.



Example 1:

Input: [[0,0,2,2],[1,0,2,3],[1,0,3,1]]
Output: 6
Explanation: As illustrated in the picture.
Example 2:

Input: [[0,0,1000000000,1000000000]]
Output: 49
Explanation: The answer is 10^18 modulo (10^9 + 7), which is (10^9)^2 = (-7)^2 = 49.
Note:

1 <= rectangles.length <= 200
rectanges[i].length = 4
0 <= rectangles[i][j] <= 10^9
The total area covered by all rectangles will never exceed 2^63 - 1 and thus will fit in a 64-bit signed integer.
*/
class Solution {
private:
    typedef std::vector<int> Rectangle;
    typedef std::vector<int> Event;
    static const int X1 = 0;
    static const int Y1 = 1;
    static const int X2 = 2;
    static const int Y2 = 3;
    static const int OPEN = 0;
    static const int CLOSE = 1;
    static const int TYPE = 1;
    static const int Y = 3;
    static const int MOD_VAL = 1e9 + 7;

    std::vector<Event> get_events(const std::vector<Rectangle>& rectangles) {
        const int N = rectangles.size();
        auto events = std::vector<Event>(2*N);
        int i = 0;
        for (const auto& rect : rectangles) {
            events[i++] = { rect[X1], OPEN, rect[X2], rect[Y1] };
            events[i++] = { rect[X1], CLOSE, rect[X2], rect[Y2] };
        }
        std::sort(events.begin(), events.end(),
                    [] (const Event& event1, const Event& event2) -> bool
                    {
                        return event1[Y] < event2[Y];
                    });
        return events;
    }
    /***************************************************************************************************/
    long long get_current_area1(const std::vector<std::vector<int>>& active_x_pairs, const int curr_y, const int new_y) {
        /* Time-Complexity:     O(A)
         * Space-Complexity:    O(1)
         *      Where:
         *          A = len(active_x_pairs)
         */
        long long sum_dx = 0;
        int curr_x = -1;
        for (const auto& x_pair : active_x_pairs) {
            curr_x = std::max( curr_x, x_pair[0] );
            sum_dx += std::max( 0, x_pair[1] - curr_x );
            curr_x = std::max( curr_x, x_pair[1] );
        }
        long long dy = new_y - curr_y;

        return sum_dx * dy;
    }

    void process_x_pair1(std::vector<std::vector<int>>& active_x_pairs, const Event& event) {
      	if (event[TYPE] == OPEN) {
			active_x_pairs.push_back({event[X1], event[X2]});
			std::sort(active_x_pairs.begin(), active_x_pairs.end(),
					[] (const std::vector<int>& p1, const std::vector<int>& p2) -> bool
					{
						return p1[0] < p2[0];
					}); 
		} else { // CLOSE
			const int A = active_x_pairs.size();
			for (int i = 0; i < A; ++i) {
				if (active_x_pairs[i][0] == event[X1] and active_x_pairs[i][1] == event[X2]) {
					active_x_pairs.erase(active_x_pairs.begin() + i);
					break;
				}
			}
		} 
    }

    int solution1(const std::vector<Rectangle>& rectangles) {
        /* Time-Complexity:     O(N^2 * log(N))
         * Space-Complexity:    O(N)
         *      Where:
         *          N = len(rectangles)
         */
        const auto events = get_events(rectangles);
        auto active_x_pairs = std::vector<std::vector<int>>();
        int curr_y = events[0][Y];
        long long result = 0;

        for (const auto& event : events) {
            result += get_current_area1( active_x_pairs, curr_y, event[Y] );
			process_x_pair1( active_x_pairs, event );
            curr_y = event[Y];
        }

        return int(result % MOD_VAL);
    }
    /***************************************************************************************************/
    int solution2(const std::vector<Rectangle>& rectangles) {
        const auto events = get_events(rectangles); 
        const auto cmp =    [] (const std::vector<int>& x_pair1, const std::vector<int>& x_pair2) -> bool
                            {
                                return x_pair1[0] < x_pair2[0];
                            };
        auto active_x_pairs = std::multiset<std::vector<int>, decltype(cmp)>(cmp);
        int curr_y = events[0][Y];
        long long result = 0;
        
        for (const auto& event : events) {
            
            long long sum_dx = 0;
            int curr_x = -1;
            for (const auto x_pair : active_x_pairs) {
                curr_x = std::max( curr_x, x_pair[0] );
                sum_dx += std::max( 0, x_pair[1] - curr_x );
                curr_x = std::max( curr_x, x_pair[1] );
            }
            long long dy = event[Y] - curr_y;
            result += sum_dx * dy;

            if (event[TYPE] == OPEN) {
                active_x_pairs.insert({event[X1], event[X2]});
            } else {
                active_x_pairs.erase(active_x_pairs.find({event[X1], event[X2]}));
            }
             
            curr_y = event[Y];
        }
        
        return int(result % MOD_VAL);
    }
    /***************************************************************************************************/
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        return solution2(rectangles);        
    }
};
