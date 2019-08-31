/*
Given n non-negative integers a1, a2, ..., an , where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). 
Find two lines, which together with x-axis forms a container, such that the container contains the most water.
Note: You may not slant the container and n is at least 2.

Example:
Input: [1,8,6,2,5,4,8,3,7]
Output: 49
*/

class Solution {
private:
    int solution1(vector<int>& nums) {
        /*
        Time-Complexity:    O(N^2)
        Space-Complexity:   O(1)
        */
        int maxWater = 0;
        
        const int N = nums.size();
        int height, width;
        
    	for (int i = 0; i < N; ++i) {
            for (int j = i+1; j < N; ++j) {
                height = std::min( nums[i], nums[j] );
                width = j - i;
                maxWater = std::max( maxWater, width * height );
            }
        }
        
        return maxWater;
    }
    
    int solution2(vector<int>& nums) {
        /*
        Time-Complexity:    O(N)
        Space-Complexity:   O(1)
        */
        int maxWater = 0;
        
        const int N = nums.size();
        int width, height;

        int left = 0;
        int right = N-1;

        while (left < right) {
            height = std::min( nums[left], nums[right] );
            width = right - left;
            maxWater = std::max( maxWater, width*height );
            
            // We want to keep the tallest coordinate as it will store most water 
            if (nums[left] < nums[right]) {
                ++left;
            } else {
                --right;
            }
        }
        
        return maxWater;
    }
    
public:
    int maxArea(vector<int>& height) {
        return solution2(height);
    }
};
