/*
Given an array nums of integers, you can perform operations on the array.
In each operation, you pick any nums[i] and delete it to earn nums[i] points. 
After, you must delete every element equal to nums[i] - 1 or nums[i] + 1.
You start with 0 points. 
Return the maximum number of points you can earn by applying such operations.

Example 1:
Input: nums = [3, 4, 2]
Output: 6
Explanation: 
Delete 4 to earn 4 points, consequently 3 is also deleted.
Then, delete 2 to earn 2 points. 6 total points are earned.

Example 2:
Input: nums = [2, 2, 3, 3, 3, 4]
Output: 9
Explanation: 
Delete 3 to earn 3 points, deleting both 2's and the 4.
Then, delete 3 again to earn 3 points, and 3 again to earn 3 points.
9 total points are earned.

Note:
The length of nums is at most 20000.
Each element nums[i] is an integer in the range [1, 10000].
*/

class Solution {
private:
    int N;
    /******************************************************************************************************************************/
    int* cache1;
    void init_cache1() {
        cache1 = new int[N+1];
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
    int set_cache1(const int i, const int max_earnings) {
        return cache1[i] = max_earnings;
    }
    int recurse1(const int i, const std::vector<int>& A, std::unordered_map<int,int>& count) {
        if (in_cache1(i)) {
            return cache1[i];
        }
        int max_earnings;    
        if (i == N) {
            max_earnings = 0;
        } else if (i == N-1) {
            max_earnings = count[A[i]] * A[i];
        } else if (i == N-2) {
            max_earnings =  A[i]+1 != A[i+1] ?
                            count[A[i]] * A[i] + count[A[i+1]] * A[i+1]:
                            std::max(count[A[i]] * A[i], count[A[i+1]] * A[i+1]);
        } else if (A[i] + 1 == A[i+1]) {
            max_earnings = std::max(
                                count[A[i]] * A[i] + recurse1(i+2, A, count),
                                count[A[i+1]] * A[i+1] + (A[i+1] + 1 == A[i+2] ? recurse1(i+3, A, count) : recurse1(i+2, A, count)));
        } else {
            max_earnings = count[A[i]] * A[i] + recurse1(i+1, A, count);
        }

        return set_cache1(i, max_earnings);
    }
	int solution1(std::vector<int>& A) {
        if (A.empty()) {
            return 0;
        }
        auto count = std::unordered_map<int,int>();
        for (const int a : A) {
            ++count[a];
        }
        std::sort(A.begin(), A.end());
        A.erase(std::unique(A.begin(), A.end()), A.end());
        N = A.size(); 
        init_cache1();
        const int max_earnings = recurse1(0, A, count);
        destroy_cache1();

        return max_earnings; 
	}
    /******************************************************************************************************************************/
public:
    int deleteAndEarn(vector<int>& nums) {
 		return solution1(nums);
    }
};
