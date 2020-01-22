/*
A car travels from a starting position to a destination which is target miles east of the starting position.
Along the way, there are gas stations.  
Each station[i] represents a gas station that is station[i][0] miles east of the starting position, and has station[i][1] liters of gas.
The car starts with an infinite tank of gas, which initially has startFuel liters of fuel in it.  
It uses 1 liter of gas per 1 mile that it drives.
When the car reaches a gas station, it may stop and refuel, transferring all the gas from the station into the car.
What is the least number of refueling stops the car must make in order to reach its destination?  If it cannot reach the destination, return -1.
Note that if the car reaches a gas station with 0 fuel left, the car can still refuel there.  
If the car reaches the destination with 0 fuel left, it is still considered to have arrived.

Example 1:
Input: target = 1, startFuel = 1, stations = []
Output: 0
Explanation: We can reach the target without refueling.

Example 2:
Input: target = 100, startFuel = 1, stations = [[10,100]]
Output: -1
Explanation: We can't reach the target (or even the first gas station).

Example 3:
Input: target = 100, startFuel = 10, stations = [[10,60],[20,30],[30,30],[60,40]]
Output: 2
Explanation: 
We start with 10 liters of fuel.
We drive to position 10, expending 10 liters of fuel.  We refuel from 0 liters to 60 liters of gas.
Then, we drive from position 10 to position 60 (expending 50 liters of fuel),
and refuel from 10 liters to 50 liters of gas.  We then drive to and reach the target.
We made 2 refueling stops along the way, so we return 2.
 
Note:
1 <= target, startFuel, stations[i][1] <= 10^9
0 <= stations.length <= 500
0 < stations[0][0] < stations[1][0] < ... < stations[stations.length-1][0] < target
*/

class Solution {
private:
    /***************************************************************************************************************************/
    typedef long long LL;
	int solution1(const int target, const int startFuel, const std::vector<std::vector<int>>& stations) {
        /* Time-Complexity:     O(N^2)
         * Space-Complexity:    O(N)
         */
        /* OFFICIAL LEETCODE DYNAMIC PROGRAMMING SOLUTION.
      	*  CONCEPT:
        *  When analyzing/adding station[i] = (locaion, capacity), 
        *  if we can reach station[i] with j refueling stops, 
        *  then we can now reach `capacity` further with j+1 refueling stops.
        *  station[i] is the (j+1)-st refueling stop.
        */
  
        // N = # of refueling stations.
        const int N = stations.size(); 
        // DP[i] = farthest location we can reach with exactly i refueling stops.
        auto DP = std::vector<LL>(N+1, 0);
        // Farthest we can reach with 0 refueling stops is startFuel.
        DP[0] = startFuel;
        /* We will compute DP[] by iteratvely introducing new stations {stations[0], ..., stations[N-1]}.
         * When considering stations[i], we have computed DP[] using {stations[0], ..., stations[i-1]}.
         * We will recompute DP[] by now introducing stations[i].
         * Remeber DP[j] represents farthest location we can reach by making j stops.
         * If we can reach stations[i] by making j stops (i.e., DP[j] >= stations[i][0]),
         * then we can we can see if its beneficial to make stations[i] the (j+1)-st stop
         * (i.e., if (DP[j+1] < DP[j] + station[i][1]) then we set DP[j+1] = DP[j] + station[i][1]).
         * We recompute DP[] by in a descending order {DP[i+1], DP[i], ..., DP[1]}.
         * Reason for descending order is that we are considering making station[i] the (j+1)-st
         * stop and DP[j+1] depends on DP[j], so if DP[j] decided to stop at station[i], then 
         * this computation can  be incorrect because DP[j+1] may also decide to stop at station[i],
         * We can't stop at a station twice.
         * */
        for (int i = 0; i < N; ++i) {
            for (int j = i; j >= 0; --j) {
                if (DP[j] >= stations[i][0]) {
                    DP[j+1] = std::max( DP[j+1], DP[j] + LL(stations[i][1]) );
                }
            }
        }
        // return minimum i for with DP[i] >= target.
        for (int i = 0; i <= N; ++i) {
            if (DP[i] >= target) {
                return i;
            }
        }
        // No solution.
        return -1;
	}
    /***************************************************************************************************************************/
    int solution2(
            const int target, 
            const int startFuel, 
            const std::vector<std::vector<int>>& stations) {
        /* Time-Complexity:     O(N * log(N))
         * Space-Complexity:    O(N)
         * */
        // GREEDY / MAX-HEAP SOLUTION
        /* Explanation:
         * We begin with an empty tank, and a max-heap which we initially push startFuel into.
         * Into, this max-heap, we will push the capacities of all stations that we can currently
         * reach with our current tank.
         * While the priority queue, is not empty, we add the top capacity of the queue to
         * tank and we then pop this element off the queue.
         * If the adjusted tank can take us all the way to target, then we are finished,
         * otherwise we still need more fuel to reach it, so we inspect all stations which
         * we havent inspected before and we push their capacities into the queue.
         * We repeat the process until we can reach target or until the queue is empty, in which
         * case we know the task is impossible.
         * After Each time we check if we can currently reach target, we increment our answer.
         * This solution is correct, because we always choose the route that will take us the
         * farthest, while choosing the smallest number of stations.
         */ 
        const int N = stations.size();
        int tank = 0;
        std::priority_queue<int> PQ;
        PQ.push(startFuel);
        
        for (int i = 0, min_stops = 0; not PQ.empty(); ++min_stops) {
            tank += PQ.top(); PQ.pop();
            if (tank >= target) {
                return min_stops;
            }
            for (; i < N and tank >= stations[i][0]; ++i) {
                PQ.push(stations[i][1]);
            }
        }

        return -1; // Impossible to reach target with startFuel and available stations.
    }
    /***************************************************************************************************************************/
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
  		return solution2(target, startFuel, stations);      
    }
};
