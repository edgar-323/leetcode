/*
Given an array of integers and an integer k, you need to find the total number of continuous subarrays whose sum equals to k.

Example 1:

Input:nums = [1,1,1], k = 2
Output: 2
Note:

The length of the array is in range [1, 20,000].
The range of numbers in the array is [-1000, 1000] and the range of the integer k is [-1e7, 1e7].
*/

class Solution {
private:
    /*****************************************************************************************/
    int solution1(std::vector<int>& nums, const int k) {
        /*
        Time-Complexity:    O( N^2 )
        Space-Complexity:   O(  1  )
        */
	    /* Explanation:
         * Consider all possible continuous subarrays.
         * There are (N choose 2) possible subarrays (we only need start and end for each subarray).
         * For each subarray, we need to see if its sum equals `k`.
         * We return number of subarrays that sum up to `k`.
         * */
        int ctsSubArrays = 0;
        const int N = nums.size();
        
        for (int i = 0; i < N; ++i) {
            int total = 0;
            for (int j = i; j < N; ++j) {
                total += nums[j];
                if (total == k) {
                    ++ctsSubArrays;
                }
            }
        }
        
        return ctsSubArrays;
    }
    /*****************************************************************************************/
    int solution2(std::vector<int>& nums, const int k) {
        /* Time-Complexity:    O( N )
         * Space-Complexity:   O( N )
         * */
        const int N = nums.size();
        if (N == 0) {
            return 0;
        }
        
        int ctsSubArrays = 0;
        
        std::unordered_map<int,int> map;
        map.emplace(0, 1);
        
        int runningSum = 0;
        for (int i = 0; i < N; ++i) {
            runningSum += nums[i];
            // if (runningSum - k) is in `map`, it means that there exists a subarray at some
            // earlier index s.t. the sum of elements from that index to `i` sum up to k.
            if (map.count(runningSum - k)) {
                ctsSubArrays += map.at(runningSum - k);
            }
            auto it = map.find(runningSum);
            if (it != map.end()) {
                ++(it->second);
            } else {
                map.insert( std::make_pair( runningSum, 1 ) );
            }
        }
        
        return ctsSubArrays;
    }
    /*****************************************************************************************/ 
public:
    int subarraySum(vector<int>& nums, int k) {
        return solution2(nums, k);
    }
};
