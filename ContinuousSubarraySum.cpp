/*
Given a list of non-negative numbers and a target integer k, write a function to check if the array has a continuous subarray of size at least 2 that sums up to a multiple of k, that is, sums up to n*k where n is also an integer.

Example 1:
Input: [23, 2, 4, 6, 7],  k=6
Output: True
Explanation: Because [2, 4] is a continuous subarray of size 2 and sums up to 6.

Example 2:
Input: [23, 2, 6, 4, 7],  k=6
Output: True
Explanation: Because [23, 2, 6, 4, 7] is an continuous subarray of size 5 and sums up to 42.

Note:
The length of the array won't exceed 10,000.
You may assume the sum of all the numbers is in the range of a signed 32-bit integer.
*/

class Solution {
private:
    bool is_multiple(const int sum, const int k) {
        return sum == k or (k > 0 and !(sum%k)); 
    }

	bool solution1(const std::vector<int>& nums, const int k) {
		/* Time-Complexity:     O( N^2 )
         * Space-Complexity:    O(  1  )
         * */
        
        const int N = nums.size();
        
        for (int i = 0; i < N; ++i) {
            int sum = nums[i];
            for (int j = i+1; j < N; ++j) {
                sum += nums[j];
                if (is_multiple( sum, k )) {
                    return true;
                }
            }
        }

        return false;
	}

    bool solution2(const std::vector<int>& nums, const int k) {
        /* Time-Complexity:     O( N )
         * Space-Complexity:    O( N )
         * */

        const int N = nums.size();
        
        // MAP<running_sum, index>
        std::unordered_map<int,int> map;
        
        // Running sum of 0 at index -1
        // This is for corner case of encountering 
        map.insert( std::make_pair( 0, -1 ) );

        int running_sum = 0;
        
        for (int current_index = 0; current_index < N; ++current_index) {
            running_sum += nums[current_index];
            if (k) {
                running_sum %= k;
            }

            if (map.count( running_sum )) {
                const int& previous_index = map[running_sum]; 
                if (current_index - previous_index > 1) {
                    // subarray size must be at least 2
                    return true;
                }
            } else {
                map.insert( std::make_pair( running_sum, current_index ) );
            }
        }

        return false;
    }    
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
  		return solution1( nums, k );      
    }
};
