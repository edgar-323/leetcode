/*
On a campus represented as a 2D grid, there are W workers and B bikes, with W <= B. 
Each worker and bike is a 2D coordinate on this grid.
Our goal is to assign a bike to each worker. 
Among the available bikes and workers, we choose the (worker, bike) pair with the shortest Manhattan distance between each other, and assign the bike to that worker. 
(If there are multiple (worker, bike) pairs with the same shortest Manhattan distance, we choose the pair with the smallest worker index; if there are multiple ways to do that, we choose the pair with the smallest bike index). 
We repeat this process until there are no available workers.
The Manhattan distance between two points p1 and p2 is Manhattan(p1, p2) = |p1.x - p2.x| + |p1.y - p2.y|.
Return a vector ans of length W, where ans[i] is the index (0-indexed) of the bike that the i-th worker is assigned to.

Example 1:
Input: workers = [[0,0],[2,1]], bikes = [[1,2],[3,3]]
Output: [1,0]
Explanation: 
Worker 1 grabs Bike 0 as they are closest (without ties), and Worker 0 is assigned Bike 1. So the output is [1, 0].

Example 2:
Input: workers = [[0,0],[1,1],[2,0]], bikes = [[1,0],[2,2],[2,1]]
Output: [0,2,1]
Explanation: 
Worker 0 grabs Bike 0 at first. Worker 1 and Worker 2 share the same distance to Bike 2, thus Worker 1 is assigned to Bike 2, and Worker 2 will take Bike 1. So the output is [0,2,1].

Note:
0 <= workers[i][j], bikes[i][j] < 1000
All worker and bike locations are distinct.
1 <= workers.length <= bikes.length <= 1000
*/

void print(const std::vector<std::pair<int,int>>& vec) {
    const int N = vec.size();
    std::cout << "[";
    for (int i = 0; i < N; ++i) {
        std::cout << "<" << vec[i].first << ", " << vec[i].second << ">" << ((i < N-1) ? ", " : "");
    }
    std::cout << "]" << std::endl;
}

class Solution {
private:
    static const int MAX_COORDINATE = 1000 - 1;
    static const int MIN_COORDINATE = 0;
    static const int RANGE = 2 * (MAX_COORDINATE - MIN_COORDINATE);

    typedef std::pair<int,int> Pair;
    typedef std::stack<Pair> Bucket;
    
    int distance(const int& x1, const int& y1, const int& x2, const int& y2) {
        return std::abs( x1 - x2 ) + std::abs( y1 - y2 );
    }
    int distance(const std::vector<int>& worker, const std::vector<int>& bike) {
        return distance( worker[0], worker[1], bike[0], bike[1] );
    }
    std::vector<int> solution2(const std::vector<std::vector<int>>& workers, const std::vector<std::vector<int>>& bikes) {
        /* Time-Complexity:     O( N + RANGE ) 
         * Space-Complexity:    O( N + RANGE )
         *  where N = W*B and RANGE = O(MAX_COORDINATE - MIN_COORDINATE)
         * */
        /* Explanation:
         * Same sorting concept of solution1 except that we now employ Bucket-Sort (variant of Counting-Sort)
         * Each Bucket in Buckets represents a distance.
         * Thus, we require a bucket for every possible distance (see `RANGE` variable).
         * Then, for each Bucket (implemented as a std::stack<Pair>) we will have all (worker, bike) pairs
         * whose distance is equal to the  `key` that maps to that Bucket.
         * This takes care of sorting by distance.
         * Then we reverse the order of the for-loops that computes all possible pairs.
         * This is so that the pairs at the top of the Bucket will have the pairs with smallest 
         * (worker, bike) indices.
         * This takes care of sorting by worker index, and finally bike index. 
         * */
        const int W = workers.size();
        const int B = bikes.size();
        
        // Create buckets 
        std::vector<Bucket> buckets( RANGE+1, Bucket() );
        // Fill buckets in the described order.
        for (int worker = W-1; worker >= 0; --worker) {
            for (int bike = B-1; bike >= 0; --bike) {
                // `pair` maps to `bucket[key]`, so we add `pair` to top of `bucket[key]`.
                const int key = distance( workers[worker], bikes[bike] );
                Bucket& bucket = buckets[key];
                bucket.push( Pair( worker, bike ) );
            }
        }
        
        std::vector<int> results( W, -1 );
        
        // Assign pairs
        std::vector<bool> workerAssigned( W, false );
        std::vector<bool> bikeAssigned( B, false );
        for (auto bucket: buckets) {
            for (; !bucket.empty(); bucket.pop()) {
                const Pair& pair = bucket.top();
                const int& worker = pair.first;
                const int& bike = pair.second;
                if (!workerAssigned[worker] and !bikeAssigned[bike]) {
                    workerAssigned[worker] = bikeAssigned[bike] = true;
                    results[worker] = bike;
                }
            }
        }

        return results;
    }
	std::vector<int> solution1(const std::vector<std::vector<int>>& workers, const std::vector<std::vector<int>>& bikes) {
		/* Time-Complexity:     O( N*lg(N) )
         * Space-Complexity:    O(    N    )
         *  where N = W * B
         * */
        /* Explanation:
         * This solution relies on the literal description of the problem (i.e., no optimizations are made).
         * First we compute all possible (worker, bike) pairs (see `pairs` vector).
         * We make sure each pair is unique.
         * We sort `pairs` according to the description.
         * We iterate `pairs` in (now) sorted order, and if the current `pair` has not been assigned, then we assign it.
         * */
        const int W = workers.size();
        const int B = bikes.size();
        
        // Compute all possible (unique) pairs 
        std::vector<Pair> pairs;
        pairs.reserve( W*B );
        for (int worker = 0; worker < W; ++worker) {
            for (int bike = 0; bike < B; ++bike) {
                pairs.push_back( std::make_pair( worker, bike ) );       
            }
        }
        // Sort all pairs
        std::sort( pairs.begin(), pairs.end(), 
			[this, &workers, &bikes]
            (const Pair& p1, const Pair& p2) {
                // returns true if `p1 < p2`
                const int& worker1 =    p1.first;
				const int& bike1 =      p1.second;
				const int& worker2 =    p2.first;
				const int& bike2 =      p2.second;
                const int dist1 =       distance( workers[worker1], bikes[bike1] );
				const int dist2 =       distance( workers[worker2], bikes[bike2] );

				if (dist1 < dist2) {
					return true;
				} else if (dist1 > dist2) {
					return false;
				} else if (worker1 < worker2) {
					return true;
				} else if (worker1 > worker2) {
					return false;
				} else if (bike1 < bike2) {
					return true;
				} else if (bike1 > bike2) {
					return false;
				} else {
					throw "Error: Non-unique (worker, bike) pair!";
                    return true;
		        }		
            }
        );

        std::vector<int> results( W, -1 );

        // Assign pairs
        std::vector<bool> workerAssigned( W, false );
        std::vector<bool> bikeAssigned( B, false );
        for (const auto& pair : pairs) {
            const int& worker = pair.first;
            const int& bike =   pair.second;
            if (!workerAssigned[worker] and !bikeAssigned[bike]) {
                workerAssigned[worker] = bikeAssigned[bike] = true;
                results[worker] = bike;
            }
        }
         
		return results;
	}
public:
    vector<int> assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
		return solution2( workers, bikes );
    }
};
