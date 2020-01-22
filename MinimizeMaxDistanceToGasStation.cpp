/*
On a horizontal number line, we have gas stations at positions stations[0], stations[1], ..., stations[N-1], where N = stations.length.

Now, we add K more gas stations so that D, the maximum distance between adjacent gas stations, is minimized.

Return the smallest possible value of D.

Example:

Input: stations = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], K = 9
Output: 0.500000
Note:

stations.length will be an integer in range [10, 2000].
stations[i] will be an integer in range [0, 10^8].
K will be an integer in range [1, 10^6].
Answers within 10^-6 of the true value will be accepted as correct.
*/
class Solution {
private:
    const double EPSILON = 1e-6;

    int get_stations_needed(const std::vector<int>& stations, const double max_dist) {
        const int N = stations.size();
        int stations_needed = 0;
        for (int i = 0; i < N-1; ++i) {
            stations_needed += int(double(stations[i+1] - stations[i]) / max_dist);
        }
        return stations_needed;
    }

    double solution1(const std::vector<int>& stations, const int K) {
        double left = 0.0;
        double right = 1e8;
        while (right - left > EPSILON) {
            const auto max_dist = (left + right) / 2.0;
            const auto stations_needed = get_stations_needed(stations, max_dist);
            if (stations_needed > K) {
                left = max_dist;
            } else {
                right = max_dist;
            }
        }
        return left;
    }
public:
    double minmaxGasDist(vector<int>& stations, int K) {
        return solution1(stations, K);       
    }
};
