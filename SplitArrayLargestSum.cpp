/*
Given an array which consists of non-negative integers and an integer m, you can split the array into m non-empty continuous subarrays. 
Write an algorithm to minimize the largest sum among these m subarrays.

Note:
If n is the length of array, assume the following constraints are satisfied:
1 ≤ n ≤ 1000
1 ≤ m ≤ min(50, n)

Examples:
Input:          nums = [7,2,5,10,8], m = 2
Output:         18
Explanation:    There are four ways to split nums into two subarrays.
                The best way is to split it into [7,2,5] and [10,8],
                where the largest sum among the two subarrays is only 18.
*/

class Solution {
private:
    typedef long long LL;
    int N;
    LL* running_sum;
    void init_running_sum(const std::vector<int>& A) {
        running_sum = new LL[N];
        running_sum[0] = A[0];
        for (int i = 1; i < N; ++i) {
            running_sum[i] = LL(A[i]) + running_sum[i-1];
        }
    }
    void destroy_running_sum() {
        delete[] running_sum;
    }
	LL sum(const int i, const int j) {
        return running_sum[j-1] - (i ? running_sum[i-1] : 0);
    }
    /********************************************************************************/
    LL** cache1;
    void init_cache1(const int M) {
        cache1 = new LL*[N];
        for (int i = 0; i < N; ++i) {
            cache1[i] = new LL[M+1];
            for (int m = 0; m <= M; ++m) {
                cache1[i][m] = -1;
            }
        }
    }
    void destroy_cache1() {
        for (int i = 0; i < N; ++i) {
            delete[] cache1[i];
        }
        delete[] cache1;
    }
    bool in_cache1(const int i, const int m) {
        return cache1[i][m] >= 0;
    }
    LL set_cache1(const int i, const int m, const int val) {
       return cache1[i][m] = val;
    }
    LL recurse1(const int i, const int m) {
        if (in_cache1(i, m)) {
            return cache1[i][m];
        }
        LL min_max = INT_MAX;
        if (m == 1) {
            min_max = sum(i, N);
        } else {
            for (int j = i+1; N-j >= m-1; ++j) {
                min_max = std::min(min_max, std::max(sum(i, j), recurse1(j, m-1)));
            }
        }
        return set_cache1(i, m, min_max);
    }
	int solution1(const std::vector<int>& nums, const int M) {
        /* Time-Complexity:     O(N^2 * M)
         * Space-Complexity:    O(N*M)
         */
        N = nums.size();
        init_running_sum(nums);
        init_cache1(M);
        const int min_max = int(recurse1(0, M));
        destroy_cache1();
        destroy_running_sum();
        return min_max;
	}
    /********************************************************************************/
    int split(const LL largest_sum, const std::vector<int>& nums) {
        int pieces = 1;
        LL sum = 0;
        for (const auto num : nums) {
            if (sum + num > largest_sum) {
                sum = num;
                ++pieces;
            } else {
                sum += num;
            }
        }
        return pieces;
    }

    int solution2(const std::vector<int>& nums, const int M) {
        LL max_val = INT_MIN;
        LL total_sum = 0;
        for (const auto num : nums) {
            max_val = std::max(max_val, LL(num));
            total_sum += num;
        }
        LL left = max_val;
        LL right = total_sum;
        while (left < right) {
            const LL mid = left + (right - left) / 2;
            const int pieces = split(mid, nums);
            if (pieces > M) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        return int(left);
    }
    /********************************************************************************/
public:
    int splitArray(vector<int>& nums, int m) {
  		return solution1(nums, m);      
    }
};
