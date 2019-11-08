/*
Given an integer array with all positive numbers and no duplicates, find the number of possible combinations that add up to a positive integer target.

Example:
nums = [1, 2, 3]
target = 4
The possible combination ways are:
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)
Note that different sequences are counted as different combinations.
Therefore the output is 7.
 
Follow up:
What if negative numbers are allowed in the given array?
How does it change the problem?
What limitation we need to add to the question to allow negative numbers?
*/

class Solution {
private:
    int W;
    int N;

    /**************************************************************************************/
    int recurse1(const std::vector<int>& nums, const int w) {
        if (w >= W) {
            return w == W;
        }
        int combos = 0;
        for (const int& num : nums) {
            combos += recurse1(nums, w + num);
        }
        return combos;
    }
    int solution1(const std::vector<int>& nums, const int target) {
        // How Do We Brute-Force This ?!
        // First off, it is evident that we can re-use any element
        // within `nums`.
        // So we need to continuously loop over `nums` and continue to add numbers
        // to the current sum?
        N = nums.size();
        W = target;

        return recurse1(nums, 0);
    }
    /**************************************************************************************/
    int* cache;
    int recurse2(const std::vector<int>& nums, const int w) {
        if (w > W) {
            return 0;
        } else if (cache[w] >= 0) {
            return cache[w];
        }

        int combos = 0;
        for (const int& num : nums) {
            combos += recurse2(nums, w + num);
        }
        
        return (cache[w] = combos);
    }
    int solution2(const std::vector<int>& nums, const int target) {
        // Excellent. We figured out a brute-force solution to this problem (see solution1).
        // Now, we need to create a cached version of solution1.
        N = nums.size();
        W = target;

        cache = new int[W+1];
        for (int w = 0; w < W; ++w) {
            cache[w] = -1;
        }
        cache[W] = 1;
        const int combos = recurse2(nums, 0);
        delete [] cache;

        return combos;
    }
    /**************************************************************************************/
    int solution3(const std::vector<int>& nums, const int target) {
        /* Time-Complexity:     O( N*W )
         * Space-Complexity:    O(  W  )
         * */

        N = nums.size();
        W = target;

        auto DP = std::vector<long long>( W+1, 0 );
        
        DP[W] = 1;
        for (int w = W-1; w >= 0; --w) {
            int combos = 0;
            for (const int num : nums) {
                if (w + num <= W) {
                    combos += DP[w + num];
                }
            }
            DP[w] = combos;
        }

        return int(DP[0]);
    }
    /**************************************************************************************/
public:
 	int combinationSum4(vector<int>& nums, int target) {
 		// Solution1() -> Brute-Force
        // Solution2() -> Cached
        // Solution3() -> Dynamic-Programming
        return solution3( nums, target );       
    }
};
