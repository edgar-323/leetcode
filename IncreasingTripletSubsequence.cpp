/*
Given an unsorted array return whether an increasing subsequence of length 3 exists or not in the array.
Formally the function should:
Return true if there exists i, j, k
such that arr[i] < arr[j] < arr[k] given 0 ≤ i < j < k ≤ n-1 else return false.
Note: Your algorithm should run in O(n) time complexity and O(1) space complexity.

Example 1:
Input: [1,2,3,4,5]
Output: true

Example 2:
Input: [5,4,3,2,1]
Output: false
*/
class Solution {
private:
    bool solution1(const std::vector<int>& A) {
        // Thoughts:
        // There are many ways to solve:
        // 1)   Sort the array, and look at all adjacent triplets.
        // 2)   Go through A[] and throw each value in a hash set and check if is part of some
        //      triplet sequnce by checking if they are in the set.
        // However, both these solutions mess with our time-memory constraints.
        // Obviouly, if we find a subsequence of any size greater than 3 then we are done but
        // even the LIS algo takes (N*log(N)) time (sometimes O(N^2)) and O(N) space.
        // 
    } 
public:
    bool increasingTriplet(vector<int>& nums) {
        return solution1(nums);        
    }
};
