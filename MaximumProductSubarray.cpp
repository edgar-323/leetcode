/*
Given an integer array nums, find the contiguous subarray within an array (containing at least one number) which has the largest product.

Example 1:
Input: [2,3,-2,4]
Output: 6
Explanation: [2,3] has the largest product 6.

Example 2:
Input: [-2,0,-1]
Output: 0
Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
*/

iclass Solution {
private:
    /******************************************************************/
    int solution1(vector<int>& nums) {
        /*
        Time-Complexity:    O(N^2)
        Space-Complexity:   O(1)
        */
        const int N = nums.size();
        int prod = INT_MIN;
        for (int i = 0; i < N; ++i) {
            int curr = nums[i];
            prod = max(prod, curr);
            for (int j = i+1; j < N; ++j) {
                curr *= nums[j];
                prod = max(prod, curr);
            }
        }
        return prod;
    }
    /******************************************************************/
    int negativeCase(int curr, int num, bool negativeExists) {
        if (curr == 0) {
            curr = num;
        } else if (curr < 0) {
            curr *= num;
        } else if (negativeExists) {
            curr *= num;
        } else {
            curr = num;
        } 
        return curr;
    }
    
    int positiveCase(int curr, int num, bool negativeExists) {
        if (curr == 0) {
            curr = num;
        } else if (curr > 0) {
            curr *= num;
        } else if (negativeExists) {
            curr *= num;
        } else {
            curr = num;
        }
        return curr;
    }
    
    int maxForwardProduct(std::vector<int>& nums) {
        const int N = nums.size();
        std::vector<bool> negativeExists(N);
        bool neg = false;
        for (int i = N-1; i >= 0; --i) {
            negativeExists[i] = neg;
            neg = (nums[i] < 0) ? true : ((nums[i] == 0) ? false : neg);
        }
        int prod = nums[0];
        int curr = nums[0];
        for (int index = 1; index < N; ++index, prod = max(prod, curr)) {
            curr =  (nums[index] == 0) ? 0 :
                    (nums[index] < 0) ? 
                    negativeCase(curr, nums[index], negativeExists[index]) :
                    positiveCase(curr, nums[index], negativeExists[index]);
        }
        return prod;
    }
    
    int maxBackwardsProduct(std::vector<int>& nums) {
        const int N = nums.size();
        std::vector<bool> negativeExists(N);
        bool neg = false;
        for (int i = 0; i < N; ++i) {
            negativeExists[i] = neg;
            neg = (nums[i] < 0) ? true : ((nums[i] == 0) ? false : neg);
        }
        int prod = nums[N-1];
        int curr = nums[N-1];
        for (int index = N-2; index > -1; --index, prod = max(prod, curr)) {
            curr =  (nums[index] == 0) ? 0 :
                    (nums[index] < 0) ? 
                    negativeCase(curr, nums[index], negativeExists[index]) :
                    positiveCase(curr, nums[index], negativeExists[index]);
        }
        return prod;
    }
    
    int solution2(std::vector<int>& nums) {
        /*
        Time-Complexity:    O(N)
        Space-Complexity:   O(N)
        */
        if (nums.empty()) {
            return INT_MIN;
        }
        return max( maxForwardProduct( nums ), maxBackwardsProduct( nums ) );
    }
    /******************************************************************/
    int max(int x, int y) {
        return (x < y) ? y : x;
    }
    
    int min(int x, int y) {
        return (x < y) ? x : y;
    }
    
    int max(int x, int y, int z) {
        return max(x, max(y, z));
    }
    
    int min(int x, int y, int z) {
        return min(x, min(y, z));
    }
    
    int solution3(std::vector<int>& nums) {
        /*
        Time-Complexity:    O(N)
        Space-Complexity:   O(1)
        */
        const int N = nums.size();
        if ( !N ) {
            return INT_MIN;
        }
        int globalMax = nums[0];
        int localMax = nums[0];
        int localMin = nums[0];
        int oldLocalMax;
        for (int i = 1; i < N; ++i, globalMax = max(globalMax, localMax)) {
            oldLocalMax = localMax;
            localMax = max(
                        nums[i], 
                        oldLocalMax * nums[i], 
                        localMin * nums[i]);
            localMin = min(
                        nums[i], 
                        oldLocalMax * nums[i], 
                        localMin * nums[i]);
        }
        return globalMax;
    }
    /******************************************************************/
public:
    int maxProduct(vector<int>& nums) {
        /*
        Denote Time-Space pair complexities by {O(T), O(S)}.
        In this problem, I went from a very simple {O(N^2), O(1)} 
        solution to a complicated (and clever) {O(N), O(N)} solution
        and finally to a {O(N), O(1)} solution by noticing that keeping
        a running min-max pair easily solves this problem.
        */
        return solution3(nums);
    }
};
