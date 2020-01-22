/*
We have jobs: difficulty[i] is the difficulty of the ith job, and profit[i] is the profit of the ith job. 
Now we have some workers. worker[i] is the ability of the ith worker, which means that this worker can only complete a job with difficulty at most worker[i]. 
Every worker can be assigned at most one job, but one job can be completed multiple times.
For example, if 3 people attempt the same job that pays $1, then the total profit will be $3.  If a worker cannot complete any job, his profit is $0.
What is the most profit we can make?

Example 1:
Input: difficulty = [2,4,6,8,10], profit = [10,20,30,40,50], worker = [4,5,6,7]
Output: 100 
Explanation: Workers are assigned jobs of difficulty [4,4,6,6] and they get profit of [20,20,30,30] seperately.

Notes:
1 <= difficulty.length = profit.length <= 10000
1 <= worker.length <= 10000
difficulty[i], profit[i], worker[i]  are in range [1, 10^5]
*/
class Solution {
private:
    int solution1(const std::vector<int>& difficulty, const std::vector<int>& profit, const std::vector<int>& worker) {
        /* Time-Complexity:     O((M + N)*log(M))
         * Space-Complexity:    O(M)
         *      Where:
         *          M = len(difficulty)
         *          N = len(worker)
         */
        const int M = difficulty.size();
        auto jobs = std::vector<std::pair<int,int>>(M);
        for (int i = 0; i < M; ++i) {
            jobs[i] = std::make_pair(difficulty[i], profit[i]);
        }
        std::sort(jobs.begin(), jobs.end(),
                    []
                    (const std::pair<int,int>& job1, const std::pair<int,int>& job2) -> bool {
                        return job1.first < job2.first;
                    });
        for (int i = 1; i < M; ++i) {
            jobs[i].second = std::max(jobs[i].second, jobs[i-1].second);
        } 
        
        int max_profit = 0;
        for (const auto& skill : worker) {
            int left = 0;
            int right = M;
            int job_index = -1;
            while (left <= right) {
                const int mid = (right + left) / 2;
                if (mid == M) {
                    job_index = M-1;
                    break;
                } else if (jobs[mid].first > skill) {
                    right = right == mid ? mid-1 : mid;
                } else if (mid < M-1 and jobs[mid+1].first <= skill) {
                    left = left == mid ? mid+1 : mid;
                } else {
                    job_index = mid;
                    break;
                }
            }
            if (job_index >= 0) {
                max_profit += jobs[job_index].second;
            }
        }

        return max_profit;
    }
public:
    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
        return solution1(difficulty, profit, worker);        
    }
};
