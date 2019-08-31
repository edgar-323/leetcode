/*
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.

Example:
Input: [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
*/

class Solution {
private:
    int solution1(const std::vector<int>& nums) {
        int water = 0;
        const int N = nums.size();
        int i = 0;
        int peak = -1;
        int j, k, shortest;
        bool found = false;
        while (i < N) {
            // We are looking for the biggest Left peak (it starts at `i`)
            while (i < N-1 and nums[i] <= nums[i+1]) {
                ++i;
            }
            // The earliest position that the right peak can start at is `i+2`
            // (will be denoted by `j`)
            j = i+2;
            // let's try to see where the right peak is (i.e., how far `j` can go).
            while (j < N) {
                if (nums[i] <= nums[j]) {
                    // we found the right peak.
                    found = true;
                    break;
                }
                if (peak < 0) {
                    // peak has not been assigned
                    if (nums[j] > nums[j-1]) {
                        // now we can assign it
                        peak = j;
                    }
                } else if (nums[peak] <= nums[j]) {
                    // found better peak
                    peak = j;
                }
                ++j;
            }
            if (!found and peak >= 0) {
                for (k = i+1; k < peak; ++k) {
                    int diff = nums[peak] - nums[k];
                    water += ((diff > 0) ? diff : 0);
                }
                i = peak;
            } else {
                if (found) {
                    for (k = i+1; k < j; ++k) {
                        water += (nums[i] - nums[k]);
                    }
                }
                i = j;
            }
            peak = -1;
            found = false;
        }
        
        return water;
    }
public: 
    int trap(std::vector<int>& height) {
        return solution1(height);
    }
};
