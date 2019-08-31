/*
Given an array nums of n integers where n > 1, return an array output such that output[i] is equal to the product of all the elements of nums except nums[i].

Example:
Input:  [1,2,3,4]
Output: [24,12,8,6]

Note: Please solve it without division and in O(n).
Follow up: Could you solve it with constant space complexity? (The output array does not count as extra space for the purpose of space complexity analysis.)
*/

class Solution {
private:
    std::vector<int> solution1(std::vector<int>& nums) {
        /*
        Time-Complexity:    O(N)
        Space-Complexity:   O(N)
        */
        const int N = nums.size();
        
        std::vector<int> forward(N);
        std::vector<int> backwards(N);
        
        forward[0] = nums[0];
        backwards[N-1] = nums[N-1];

        for (int i = 1; i < N; ++i) {
            forward[i] = forward[i-1] * nums[i];
            backwards[N-1-i] = backwards[N-1-i+1] * nums[N-1-i];
        }
        
        std::vector<int> output(N);
        output[0] = backwards[1];
        output[N-1] = forward[N-2];
        
        for (int i = 1; i < N-1; ++i) {
            output[i] = forward[i-1] * backwards[i+1];
        }
        
        return output;
    }    
    
    std::vector<int> solution2(std::vector<int>& nums) {
        /*
        Time-Complexity:    O(N)
        Space-Complexity:   O(1)
        */
        const int N = nums.size();
        
        std::vector<int> output(N);
        output[0] = nums[0];
        
        for (int i = 1; i < N; ++i) {
            output[i] = output[i-1] * nums[i];
        }
        
        output[N-1] = output[N-2];
        int old = nums[N-1];
        for (int i = N-2; i > 0; --i) {
            output[i] = output[i-1] * old;
            old *= nums[i];
        }
        output[0] = old;
        
        return output;
    }
    
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        return solution2(nums);
    }
};
