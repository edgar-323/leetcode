/*
You are given two arrays (without duplicates) nums1 and nums2 where nums1’s elements are subset of nums2. Find all the next greater numbers for nums1's elements in the corresponding places of nums2.

The Next Greater Number of a number x in nums1 is the first greater number to its right in nums2. If it does not exist, output -1 for this number.

Example 1:
Input: nums1 = [4,1,2], nums2 = [1,3,4,2].
Output: [-1,3,-1]
Explanation:
    For number 4 in the first array, you cannot find the next greater number for it in the second array, so output -1.
    For number 1 in the first array, the next greater number for it in the second array is 3.
    For number 2 in the first array, there is no next greater number for it in the second array, so output -1.
Example 2:
Input: nums1 = [2,4], nums2 = [1,2,3,4].
Output: [3,-1]
Explanation:
    For number 2 in the first array, the next greater number for it in the second array is 3.
    For number 4 in the first array, there is no next greater number for it in the second array, so output -1.
Note:
All elements in nums1 and nums2 are unique.
The length of both nums1 and nums2 would not exceed 1000.
*/
class Solution {
private:
	std::vector<int> solution1(const std::vector<int>& nums1, const std::vector<int>& nums2) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         *      Where:
         *          N = len(nums2)
         */
        // EXPLANATION:
        // For each nums2[j], we maintain:
        //      map[nums2[j]] = next greater element in nums2[j+1:N] (will be -1 if no such number)
        // 
        // Additionally, we maintain a monotonically decreasing stack. 
        // How does this help?
        // Well, we iterate num2[] from left to right:
        // for j in {0,...,N-1}:
        //      // if nums2[j] is less than top(stack) then it shall be part of the monotonically decreasing list of
        //      // numbers so we push it to the stack.
        //      // Otherwise, this means that there is some sequence of numbers that are less than nums2[j] in the stack.
        //      // For all these numbers, nums2[j] will be the next greater element to their right.
        //      // So we update our map to refelct this information:
        //      // while stack is not empty and top(stack) < nums2[j]:
        //      //      map[stack.top()] = nums2[j]
        //      //      pop(stack)
        //      // Finally we still push nums2[j] to the stack because at this point the stack is either empty, or it has
        //      // numbers that are all greater than nums2[j], and so pushing nums2[j] will still maintain the monotonic 
        //      // proeprty of this stack.
        //
        // Once we do this processing for all nums2[j], we know that the numbers which remain in the stack do not have 
        // a next greater element to their right.
        // Therefore, we add them to our map with a value of -1, as follows:
        //      while stack is not empty:
        //          map[top(stack)] = -1
        //          pop(stack)
        //
        // Finally, we know that all nums2[j] exist in map[].
        // And since nums1[] is a subset of nums2[], then all elements of nums1[] exist in map[] as well.
        // Thus, we iterate through nums1[], and we know the answer for all its elements:
        // For i in {0,...,M-1}:
        //      answer[i] = map[nums1[i]]
        //
        // The actual C++ code is shown below:

        const int M = nums1.size();
        const int N = nums2.size();

        auto stack = std::stack<int>();
        auto map = std::unordered_map<int,int>();
        auto results = std::vector<int>(M);  

        for (int j = 0; j < N; ++j) {
            while (not stack.empty() and nums2[j] > stack.top()) {
                map[stack.top()] = nums2[j];
                stack.pop();
            }
            stack.push(nums2[j]);
        }
        
        while (not stack.empty()) {
            map[stack.top()] = -1;
            stack.pop();
        }

        for (int i = 0; i < M; ++i) {
            results[i] = map[nums1[i]];
        }

        return results;
	}	
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
 		return solution1(nums1, nums2);       
    }
};
