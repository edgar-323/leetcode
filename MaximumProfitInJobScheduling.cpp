/*
We have n jobs, where every job is scheduled to be done from startTime[i] to endTime[i], obtaining a profit of profit[i].
You're given the startTime , endTime and profit arrays, you need to output the maximum profit you can take such that there are no 2 jobs in the subset with overlapping time range.
If you choose a job that ends at time X you will be able to start another job that starts at time X.
 
Example 1:
Input: startTime = [1,2,3,3], endTime = [3,4,5,6], profit = [50,10,40,70]
Output: 120
Explanation: The subset chosen is the first and fourth job. 
Time range [1-3]+[3-6] , we get profit of 120 = 50 + 70.

Example 2:
Input: startTime = [1,2,3,4,6], endTime = [3,5,10,6,9], profit = [20,20,100,70,60]
Output: 150
Explanation: The subset chosen is the first, fourth and fifth job. 
Profit obtained 150 = 20 + 70 + 60.

Example 3:
Input: startTime = [1,1,1], endTime = [2,3,4], profit = [5,6,4]
Output: 6

Constraints:
1 <= startTime.length == endTime.length == profit.length <= 5 * 10^4
1 <= startTime[i] < endTime[i] <= 10^9
1 <= profit[i] <= 10^4
*/

class Job {
public:
    int start;
    int end;
    int profit;
    Job(const int _start, const int _end, const int _profit):
        start(_start), end(_end), profit(_profit) {}
    Job() {}
};


class Solution {
private:
    int N;
    /********************************************************************************************************************************/
    int* cache1;
    void init_cache1() {
        cache1 = new int[N];
        for (int i = 0; i < N; ++i) {
            cache1[i] = -1;
        }
    }
    void destroy_cache1() {
        delete[] cache1;
    }
    bool in_cache1(const int i) {
        return cache1[i] >= 0;
    }
    int set_cache1(const int i, const int val) {
        return cache1[i] = val;
    }
    int recurse1(const int i, const std::vector<Job>& jobs) {
        // How much profit can we make from jobs[i:N]
        // Well first lets decide how well we can do if we decide to do job i.
        // This would mean that we need to locate index j, such that
        //  jobs[i].end <= jobs[k].start, for k € {j, j+1, ..., N-1}
        // Then our answer is:
        //  max{ recurse1(i+1, jobs), profit[i] + recurse1(j, jobs) }
        // 
        // We can do binary-search for jobs[i].end in the start times of jobs[i+1:N]
        if (i >= N) {
            return 0;
        } else if (in_cache1(i)) {
            return cache1[i];
        }
        int j;
        int left = i+1;
        int right = N;
        while (left <= right) {
            j = (left + right) / 2;
            if (j >= N) {
                break;
            } else if (jobs[i].end > jobs[j].start) {
                // Job i ends after job j starts, so we need to keep searching
                left = j == left ? j+1 : j;
            } else if (jobs[i].end <= jobs[j-1].start) {
                // We have a match but it is not the first such match 
                right = j == right ? j-1 : j;
            } else {
                // We found the first such match
                break;
            }
        }
        const int max_profit = std::max(recurse1(i+1, jobs), jobs[i].profit + recurse1(j, jobs));

        return set_cache1(i, max_profit);
    }
	int solution1(const std::vector<int>& start_time, const std::vector<int>& end_time, const std::vector<int>& profit) {
        /* Time-Complexity:     O(N * log(N))
         * Space-Complexity:    O(N)
         */
        N = start_time.size();
        auto jobs = std::vector<Job>(N); 
        for (int i = 0; i < N; ++i) {
            jobs[i] = Job(start_time[i], end_time[i], profit[i]);
        }
        std::sort(jobs.begin(), jobs.end(), 
                    []
                    (const Job& job1, const Job& job2) -> bool {
                        return job1.start < job2.start;
                    });
        init_cache1();
        const int max_profit = recurse1(0, jobs);
        destroy_cache1();

        return max_profit;
	}
    /********************************************************************************************************************************/
    int solution2(const std::vector<int>& start_time, const std::vector<int>& end_time, const std::vector<int>& profit) {
        /* Time-Complexity:     O(N * log(N))
         * Space-Complexity:    O(N)
         */
        // DP Version of Solution1
      	N = start_time.size();
		auto jobs = std::vector<Job>(N);
		for (int i = 0; i < N; ++i) {
	        jobs[i] = Job(start_time[i], end_time[i], profit[i]);
        }
        std::sort(jobs.begin(), jobs.end(), [] (const Job& job1, const Job& job2) -> bool {return job1.start < job2.start;});
        auto DP = std::vector<int>(N+1);
        DP[N] = 0;
        for (int i = N-1; i >= 0; --i) {
            int j;
            int left = i+1;
            int right = N;
            while (left <= right) {
                j = (left + right) / 2;
                if (j >= N) {
                    break;
                } else if (jobs[i].end > jobs[j].start) {
                    left = j == left ? j+1 : j;
                } else if (jobs[i].end <= jobs[j-1].start) {
                    right = j == right ? j-1 : j;
                } else {
                    break;
                }
            }
            DP[i] = std::max(DP[i+1], jobs[i].profit + (j <= N ? DP[j] : 0));
        }

        return DP[0];
    }
    /********************************************************************************************************************************/
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
  		return solution2(startTime, endTime, profit);      
    }
};
