/*
Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊n/2⌋ times.
You may assume that the array is non-empty and the majority element always exist in the array.

Example 1:
Input: [3,2,3]
Output: 3

Example 2:
Input: [2,2,1,1,1,2,2]
Output: 2
*/

class Solution {
private:
    int solution1(std::vector<int>& nums) {
        /*
        Time-Complexity:    O(N) (Average)
        Space-Complexity:   O(N)
        */
        const int N = nums.size();
        if (N == 0) {
            return 0;
        }
        
        std::unordered_map<int,int> wordCount;
        int maxElem = nums[0];
        int maxCount = 1;
        int newCount;
        std::unordered_map<int,int>::iterator it;
        wordCount.emplace(maxElem, maxCount);
        for (int i = 1; i < N; ++i) {
            newCount = 1;
            it = wordCount.find(nums[i]);
            if (it != wordCount.end()) {
                newCount += it->second;
                it->second = newCount;
            } else {
                wordCount.emplace(nums[i], newCount);
            }
            if (newCount > maxCount) {
                maxCount = newCount;
                maxElem = nums[i];
            }
        }
        
        return maxElem;
    }
    
    int solution2(std::vector<int>& nums) {
        /* Time-Complexity:     O( N )
         * Space-Complexity:    O( 1 )
         * */
        // UNINTUITIVE SOLUTION
        const int N = nums.size();
        int count = 1;
        int candidate = nums[0];
        
        for (int i = 1; i < N; ++i) {
            if (count == 0) {
                candidate = nums[i];
            }
            count += (nums[i] == candidate) ? 1 : -1;
        }

        return candidate;
    }
    
public:
    int majorityElement(vector<int>& nums) {
        return solution2(nums);
    }
};
