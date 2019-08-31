/*
Given an array of integers, find if the array contains any duplicates.

Your function should return true if any value appears at least twice in the array, and it should return false if every element is distinct.

Example 1:

Input: [1,2,3,1]
Output: true
Example 2:

Input: [1,2,3,4]
Output: false
Example 3:

Input: [1,1,1,3,3,4,3,2,4,2]
Output: true
*/

class Solution {
private:
    bool solution2(std::vector<int>& nums) {
        /* Time-Comlexity:      O( N * lg( N ) ) 
         * Space-Comlexity:     O(   ???       )
         * the space complexity depends on the mechanics
         * of underlying sorting alforithm.
         * If (in-place) HeapSort is used, we can 
         * achieve O( 1 ) space complexity.
         * */
        std::sort( nums.begin(), nums.end() );
        const size_t N = nums.size();
        for (int i = 1; i < N; ++i) {
            if (nums[i] == nums[i-1]) {
                return true;
            }
        }

        return false;
    }
    bool solution1(std::vector<int>& nums) {
        /* Time-Comlexity:      O( N )
         * Space-Comlexity:     O( N )
         * */
        std::unordered_set<int> seen;
        for (auto num : nums) {
            if (!seen.count( num )) {
                seen.insert( num ); 
            } else {
                return true;
            }
        }

        return false;
    }
public:
    bool containsDuplicate(vector<int>& nums) {
       return solution1( nums ); 
    }
};
