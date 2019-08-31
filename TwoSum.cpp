/*
Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

Example:

Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
*/

class Solution {
private:
    std::vector<int> solution2(std::vector<int>& nums, const int target) {
        /* Time-Complexity:     O( N * F )
         * Space-Complexity:    O(   N   )
         *  where F = O( map.find() )
         *  if map is unordered:
         *      F = O(1) (on average)
         *  else if map is tree-set:
         *      F = O( log(N) )
         *  else:
         *      UNKNOWN
         * */
        std::vector<int> results(2, -1);
        const int N = nums.size(); 
        std::unordered_map<int, int> map;
        for (int i = 0; i < N; ++i) {
            auto it = map.find( target - nums[i] );
            if (it != map.end()) {
                results[0] = it->second;
                results[1] = i;
                break;
            }
            map.insert( std::make_pair( nums[i], i ) );
        }

        return results; 
    }
	std::vector<int> solution1(std::vector<int>& nums, const int target) {
        /* Time-Complexity:     O( N^2 )
         * Space-Complexity:    O(  1  )
         * */
        std::vector<int> results(2, -1);
        const int N = nums.size();
        
        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j < N; ++j) {
                if (nums[i] + nums[j] == target) {
                    results[0] = i;
                    results[1] = j;
                    return results;
                } 
            }
        }

        return results;
	}
public:
    vector<int> twoSum(vector<int>& nums, int target) {
     	return solution2( nums, target ); 
    }
};
