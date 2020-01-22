/*
Given an array consisting of n integers, find the contiguous subarray whose length is greater than or equal to k that has the maximum average value. And you need to output the maximum average value.

Example 1:
Input: [1,12,-5,-6,50,3], k = 4
Output: 12.75
Explanation:
when length is 5, maximum average value is 10.8,
when length is 6, maximum average value is 9.16667.
Thus return 12.75.
Note:
1 <= k <= n <= 10,000.
Elements of the given array will be in range [-10,000, 10,000].
The answer with the calculation error less than 10-5 will be accepted.
*/
class Solution {
private:
    double solution1(const std::vector<int>& A, const int K) {
        const int N = A.size();

    } 
public:
    double findMaxAverage(vector<int>& nums, int k) {
        return solution1(nums, k);        
    }
};
