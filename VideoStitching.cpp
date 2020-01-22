/*
You are given a series of video clips from a sporting event that lasted T seconds.  
These video clips can be overlapping with each other and have varied lengths.
Each video clip clips[i] is an interval: it starts at time clips[i][0] and ends at time clips[i][1].  
We can cut these clips into segments freely: for example, a clip [0, 7] can be cut into segments [0, 1] + [1, 3] + [3, 7].
Return the minimum number of clips needed so that we can cut the clips into segments that cover the entire sporting event ([0, T]).  
If the task is impossible, return -1.

Example 1:
Input: clips = [[0,2],[4,6],[8,10],[1,9],[1,5],[5,9]], T = 10
Output: 3
Explanation: 
We take the clips [0,2], [8,10], [1,9]; a total of 3 clips.
Then, we can reconstruct the sporting event as follows:
We cut [1,9] into segments [1,2] + [2,8] + [8,9].
Now we have segments [0,2] + [2,8] + [8,10] which cover the sporting event [0, 10].

Example 2:
Input: clips = [[0,1],[1,2]], T = 5
Output: -1
Explanation: 
We can't cover [0,5] with only [0,1] and [0,2].

Example 3:
Input: clips = [[0,1],[6,8],[0,2],[5,6],[0,4],[0,3],[6,7],[1,3],[4,7],[1,4],[2,5],[2,6],[3,4],[4,5],[5,7],[6,9]], T = 9
Output: 3
Explanation: 
We can take clips [0,4], [4,7], and [6,9].

Example 4:
Input: clips = [[0,4],[2,8]], T = 5
Output: 2
Explanation: 
Notice you can have extra video after the event ends.
 
Note:
1 <= clips.length <= 100
0 <= clips[i][0], clips[i][1] <= 100
0 <= T <= 100
*/

class Solution {
private:
    static const int START = 0;
    static const int END = 1;
    /****************************************************************************************************************************/
    int solution1(std::vector<std::vector<int>>& clips, const int T) {
        /* Time-Complexity:     O(N * log(N))
         * Space-Complexity:    O(1)
         */
        /* EXPLANATION (GREEDY SOLUTION IN THE SENSE THAT IT DOESN'T REQUIRE DP SCHEME):
         * We will sort the clips by start time.
         * Then we will define `prev_stitching_point` which will mark the last stitching point.
         * We will scan through clips in their now sorted order.
         * We will see which clips are reachable from the current prev_stitching_point.
         * In other words, we iterate through clips while the current clip start time is at 
         * most `prev_stitching_point`, then we try to see if we can go even further by choosing 
         * then end of this current clip as the next stitching point.
         * If at some point we cannot find a next stitching point, then we return -1 because there
         * is no way to cover entire clip. 
         * Notice that we always go as far as possible (we maximize `next_stitching_point` given `prev_stitching_point`)
         * and that we stop as soon as we cover the entire clip.
         * Therefore this scheme MUST use optimially minimum # of clips.
         */
        // # clips
        const int N = clips.size();
        // sort clips by start time
        std::sort(clips.begin(), clips.end(),
                    []
                    (const std::vector<int>& clip1, const std::vector<int>& clip2) -> bool {
                        return clip1[START] < clip2[START];
                    });
        // Answer
        int min_clips = 0;
        
        for (int i = 0, prev_stitching_point = 0; prev_stitching_point < T; ++min_clips) {
            int next_stitching_point = prev_stitching_point;
            while (i < N and clips[i][START] <= prev_stitching_point) {
                next_stitching_point = std::max(next_stitching_point, clips[i++][END]);
            }
            if (prev_stitching_point == next_stitching_point) {
                return -1;
            } else {
                prev_stitching_point = next_stitching_point;
            }
        }

        return min_clips;
    }
    /****************************************************************************************************************************/
    int solution2(std::vector<std::vector<int>>& clips, const int T) {
        /* Time-Complexity:     O(N*log(N) + N*T)
         * Space-Complexity:    O(T)
         */
        /* EXPLANATION (DP SOLUTION):
         * We will first sort clips[] by start time.
         * 
         * We will define:
         *      DP[t] = minimum # of clips needed to cover event time range [0, t]
         * 
         * Then, we scan clips[] in their now sorted order and update DP[*]:
         *      DP[t] = min{ DP[t], DP[clips[i][0]] + 1 }
         *
         */
        std::sort(clips.begin(), clips.end(),
                    []
                    (const std::vector<int>& clip1, const std::vector<int>& clip2) -> bool {
                        return clip1[START] < clip2[START];
                    });
        
        auto DP = std::vector<int>(T+1, T+1);
        
        DP[0] = 0;
        for (const auto& clip : clips) {
            for (int t = clip[START]+ 1; t <= clip[END]; ++t) {
                DP[t] = std::min(DP[t], DP[clip[START]] + 1);
            }
        }

        return DP[T] == T+1 ? -1 : DP[T];
    }
    /****************************************************************************************************************************/
    int solution3(const std::vector<std::vector<int>>& clips, const int T) {
        /* Time-Complexity:     O(N*T)
         * Space-Complexity:    O(T)
         */
        auto DP = std::vector<int>(T+1, T+1);

        DP[0] = 0;
        for (int t = 1; t <= T and DP[t-1] < T; ++t) {
            for (const auto& clip : clips) {
                const int start = clip[0];
                const int end = clip[1];
                if (start <= t and t <= end) {
                    DP[t] = std::min(DP[t], DP[start] + 1);
                }
            } 
        }

        return DP[T] == T+1 ? -1 : DP[T];
    }
    /****************************************************************************************************************************/
public:
    int videoStitching(vector<vector<int>>& clips, int T) {
        return solution1(clips, T);       
    }
};

