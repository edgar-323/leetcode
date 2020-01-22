/*
Given n balloons, indexed from 0 to n-1. 
Each balloon is painted with a number on it represented by array nums. 
You are asked to burst all the balloons. 
If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins. 
Here left and right are adjacent indices of i. 
After the burst, the left and right then becomes adjacent.
Find the maximum coins you can collect by bursting the balloons wisely.

Note:
You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100

Example:
Input: [3,1,5,8]
Output: 167 
Explanation: nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
             coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167
*/

class Solution {
private:
    /***********************************************************************/
    int recurse1(std::vector<int>& nums) {
        const int N = nums.size();
        if (N <= 1) {
            return (N == 0) ? 0 : nums[0];
        }
        
        int maxBurst = 0;
        std::vector<int> arr(N-1);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < i; ++j) {
                arr[j] = nums[j];
            }
            for (int j = i; j < N-1; ++j) {
                arr[j] = nums[j+1];
            }
            int pop = nums[i];
            pop *= ((i > 0) ? nums[i-1] : 1);
            pop *= ((i < N-1) ? nums[i+1] : 1);
            pop += recurse1(arr);
            maxBurst = std::max(maxBurst, pop);
        }
        
        return maxBurst;
    }
    int solution1(std::vector<int>& nums) {
        // BRUTE-FORCE --> TIME & SPACE EXCEEDED
        /*
        Time-Complexity:    O(N^2 * 2^N)
        Space-Complexity:   O(N * 2^N)
        */
        return recurse1(nums);
    }
    /***********************************************************************/
    std::unordered_map<std::string, int> memo;
    std::vector<int> nums;
    
    int recurse2(std::vector<int>& indices, std::string& key) {
        if (memo.count(key) > 0) {
            return memo.at(key);
        }
        const int N = indices.size();
        if (N == 0) {
            return 0;
        } else if (N == 1) {
            memo.emplace(key, nums[indices[0]]);
            return nums[indices[0]];
        }
        
        int maxBurst = 0;
        std::vector<int> subIndices(N-1);
        std::string subKey;
        
        for (int i = 0; i < N; ++i) {
            subKey = "";
            for (int j = 0; j < i; ++j) {
                subIndices[j] = indices[j];
                subKey += (std::to_string(indices[j]) + "#");
            }
            for (int j = i; j < N-1; ++j) {
                subIndices[j] = indices[j+1];
                subKey += (std::to_string(indices[j+1]) + "#");
            }
            
            int pop = nums[indices[i]];
            pop *= ((i > 0) ? nums[indices[i-1]] : 1);
            pop *= ((i < N-1) ? nums[indices[i+1]] : 1);
            pop += recurse2(subIndices, subKey);
            maxBurst = std::max(maxBurst, pop);
        }
        
        memo.emplace(key, maxBurst);
        return maxBurst;
    }
    
    int solution2(std::vector<int>& nums) {
        /*
        A memo-ized version of solution1(...).
        Still too slow.
        */
        memo.clear();
        const int N = nums.size();
        if (N == 0) {
            return 0;
        }
        this->nums = nums;
        std::vector<int> indices(N);
        std::string key = "";
        for (int i = 0; i < N; ++i) {
            indices[i] = i;
            key += (std::to_string(i) + "#");
        }
        return recurse2(indices, key);
    }
    /***********************************************************************/    
    int solution3(std::vector<int>& nums) {
        /*
        **********************************************************
        I would have never thought of this solution.
        Took idea from: 
            https://www.youtube.com/watch?v=IFNibRVgFBo&t=1233s
        But I implemented this myself without looking at actual
        solution code from anyone else.
        I simply analyzed a sample-run of the proposed algorithm.
        **********************************************************
        Time-Complexity:    O(N^3)
        Space-Complexity:   O(N^2)
        **********************************************************
        */
        // EXPLANATION:
        // Use Dynamic-Programming methodology.
        // Let left, right € [0, N) be the max subsequence nums[left:right].
        // Then let DP[left][right] denote the maximum burst in subsequence
        // nums[left:right].
        // We want to find DP[0][N-1].
        // Suppose we want to resolve DP[i][j].
        
        const int N = nums.size();
        if (!N) {
            return 0;
        }
        
        int DP[N][N];
        int factor;
        for (int len = 1; len <= N; ++len) {
            for (int left = 0, right = len-1; right < N; ++left, ++right) {
                DP[left][right] = 0;
                factor = (left ? nums[left-1] : 1) * (right < N-1 ? nums[right+1] : 1);
                for (int k = left; k <= right; ++k) {
                    DP[left][right] = std::max(
                                            DP[left][right], 
                                            (k > left ? DP[left][k-1] : 0) + (k < right ? DP[k+1][right] : 0) + factor*nums[k]
                                      );
                }
            }
        }
        
        return DP[0][N-1];
    }
    /***********************************************************************/    
public:
    int maxCoins(vector<int>& nums) {
        return solution3(nums);
    }
};
