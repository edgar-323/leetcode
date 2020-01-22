/*
Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.

Example:

Input:
[
  ["1","0","1","0","0"],
  ["1","0","1","1","1"],
  ["1","1","1","1","1"],
  ["1","0","0","1","0"]
]
Output: 6
*/
class Solution {
private:
    int largestRectangleArea(vector<int>& heights) {
        int area = 0;
        const int N = heights.size();
        int curr, prev, currHeight, prevHeight, width;
        std::stack<int> indices;
        indices.push(-1);
        for (curr = 0; curr < N; ++curr) {
            prev = indices.top();
            prevHeight = (prev < 0) ? prev : heights[prev];
            currHeight = heights[curr];
            while (currHeight < prevHeight) {
                indices.pop();
                prev = indices.top();
                width = curr - prev - 1;
                area = max(area, width*prevHeight);
                prevHeight = (prev < 0) ? prev : heights[prev];
            }
            indices.push(curr);
        }
        indices.push(N);
        while (indices.size() > 2) {
            curr = indices.top();
            indices.pop();
            prevHeight = heights[indices.top()];
            indices.pop();
            prev = indices.top();
            width = curr - prev - 1;
            area = max(area, width*prevHeight);
            indices.push(curr);
        }

        return area;
    }
    
    int solution(vector<vector<char>>& matrix) {
        /*
        ****************************************************
        I took concept from YouTube video but ALL the code 
        is my own. 
        Basically, we create another matrix, call it `heights`,
        of size MxN.
        Then, for each cell (i,j) of heights, we record the 
        maximum bar (or height) from matrix[0][j] to matrix[i][j].
        Note that this bar will be at most equal to i but can 
        also be zero due to the fact that there can exist a zero
        anywhere in the jth column of matrix.
        With this information recorded, when we look at the ith
        row of heights, we have an array of bars, and we can get
        the largest rectangular area of these bars by using the 
        solution to problem 84 (largestRectangleArea), which runs
        in linear time.
        If we do this for every single row of heihts, then we 
        will acquire the maximum rectangle in the matrix, and 
        will be done.
        ****************************************************
        Time-Complexity: 
            ==> M*N + M*(N+N)
            ==> 3*M*N
            ==> O(M*N)
        Space-Complexity:
            ==> M*N + 1*N
            ==> M*(N+1)
            ==> O(M*N)
        ****************************************************
        */
        int maxRect = 0;
        const int M = matrix.size();
        if (M == 0) {
            return maxRect;
        }
        const int N = matrix[0].size();
        if (N == 0) {
            return maxRect;
        }
        vector<vector<int>> rowHeights(M, vector(N, 0));
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                rowHeights[i][j] = (matrix[i][j] == '0') ? 0 : 
                            (1 + ((i > 0) ? rowHeights[i-1][j] : 0));
            }
            maxRect = max(maxRect, largestRectangleArea(rowHeights[i]));
        }
        return maxRect;
    }
    
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        return solution(matrix);
    }
};
