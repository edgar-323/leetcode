/*
Given a non-empty array of integers, every element appears twice except for one. Find that single one.

Note:

Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

Example 1:

Input: [2,2,1]
Output: 1
Example 2:

Input: [4,1,2,1,2]
Output: 4
*/

class Solution {
private:
    int solution1(const std::vector<int>& nums) {
        /* Time-Complexity:     O( N )
         * Space-Complexity:    O( 1 )
         */ 
		int X = 0;
        for (auto& num : nums) {
            X ^= num;
        }
        return X;
    }
public:
	int singleNumber(vector<int>& nums) {
		return solution1( nums );
	}
};
