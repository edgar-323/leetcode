/*
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:

string convert(string s, int numRows);
Example 1:

Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"
Example 2:

Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:

P     I    N
A   L S  I G
Y A   H R
P     I
*/

class Solution {
private:
    std::string solution1(const std::string& input, const int R) {
        const int N = input.size();
        if (R <= 0) {
            return "";
        } else if (R == 1 or R >= N) {
            return input;
        } 
        
        std::string output(N, ' ');
        int index = 0;

        // row 0
        for (int i = 0; i < N; i += (2 * (R-1)) ) {
            output[index++] = input[i];
        }
        // rows [1,..., R-2]    
        for (int row = 1; row < R-1; ++row) {
            bool odd = false;
            int oddIndex = 2 * (R-1) - 2 * row; 
            int evenIndex = 2 * row;
            output[index++] = input[row];
            int rowIndex = row + oddIndex;
            while (rowIndex < N) {
                output[index++] = input[rowIndex];
                rowIndex += (odd ? oddIndex : evenIndex);
                odd = !odd;
            }
        }
        // row R-1
        for (int i = R-1; i < N; i += (2 * (R-1))) {
            output[index++] = input[i];
        }
        
        return output;
    }
public:
    std::string convert(std::string s, int numRows) {
        return solution1(s, numRows); 
    }
};
