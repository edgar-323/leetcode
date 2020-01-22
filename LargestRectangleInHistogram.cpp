/*
Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.

Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].
The largest rectangle is shown in the shaded area, which has area = 10 unit.

Example:
Input: [2,1,5,6,2,3]
Output: 10
*/class Solution {
private:
    int solution1(const std::vector<int>& heights) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         */
        /* Explanation:
         *  1)  Idea is, we will consider every element a[i] to be a candidate for the area calculation. 
         *      That is, if a[i] is the minimum element then what is the maximum area possible for all such rectangles? 
         *      We can easily figure out that it's a[i]*(R-L+1-2) or a[i] * (R-L-1), where a[R] is first subsequent element(R>i) in the array just smaller than a[i], 
         *      similarly a[L] is first previous element just smaller than a[i]. 
         *      makes sense? (or take a[i] as a center and expand it to left and right and stop when first just smaller elements are found on both the sides). 
         *      But how to implement it efficiently?
         *
         *  2)  We add the element a[i] directly to the stack if it's greater than the peak element (or a[i-1] ), because we are yet to find R for this. 
         *      Can you tell what's L for this? 
         *      Exactly, it's just the previous element in stack. (We will use this information later when we will pop it out).
         *
         *  3)  What if we get an element a[i] which is smaller than the peak value, it is the R value for all the elements present in stack which are greater than a[i]. 
         *      Pop out the elements greater than a[i], we have their R value and L value(point 2). and now push a[i] and repeat..
         */
        const int N = heights.size();

        int max_area = 0;
        
        auto stack = std::stack<int>();
        stack.push(-1);

        for (int i = 0; i < N; ++i) {
            while (stack.top() != -1 and heights[i] <= heights[stack.top()]) {
                const auto height_index = stack.top(); stack.pop();
                const auto width = i - stack.top() - 1; // R - L + 1 - 2
                max_area = std::max(max_area, heights[height_index] * width);
            }
            stack.push(i);
        }
        while (stack.top() != -1) {
            const auto height_index = stack.top(); stack.pop();
            const auto width = N - stack.top() - 1; // R - L + 1 - 2
            max_area = std::max(max_area, heights[height_index] * width);
        }

        return max_area;
    }
public:
    int largestRectangleArea(vector<int>& heights) {
        return solution1(heights);       
    }
};
