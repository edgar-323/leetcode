/*
Given a circular array (the next element of the last element is the first element of the array),
print the Next Greater Number for every element.
The Next Greater Number of a number x is the first greater number to its traversing-order next in the array,
which means you could search circularly to find its next greater number.
If it doesn't exist, output -1 for this number.

Example 1:
Input: [1,2,1]
Output: [2,-1,2]
Explanation: The first 1's next greater number is 2; 
The number 2 can't find next greater number; 
The second 1's next greater number needs to search circularly, which is also 2.
Note: The length of given array won't exceed 10000.
*/
class Solution {
private:
    std::vector<int> solution1(const std::vector<int>& nums) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         */
        // Explanation:
        // Used same idea as first version of this problem, but due to new contraints,
        // the stack now contains indices instead of actual values (due to duplicate values),
        // and we were able to also use the results as our map.
        if (nums.empty()) {
            return {};
        }

        const int N = nums.size();

        auto stack = std::stack<int>();
        auto results = std::vector<int>(N, -1);
        
        for (int i = 0; i < N; ++i) {
            while (not stack.empty() and nums[i] > nums[stack.top()]) {
                results[stack.top()] = nums[i];
                stack.pop();
            }
            stack.push(i);
        }
        for (int i = 0; i < N; ++i) {
            while (not stack.empty() and i < stack.top() and nums[i] > nums[stack.top()]) {
                results[stack.top()] = nums[i];
                stack.pop();
            }
        }

        return results;
    }
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        return solution1(nums);    
    }
};
