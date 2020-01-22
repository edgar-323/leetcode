/*
In a row of dominoes, A[i] and B[i] represent the top and bottom halves of the i-th domino.  (A domino is a tile with two numbers from 1 to 6 - one on each half of the tile.)

We may rotate the i-th domino, so that A[i] and B[i] swap values.

Return the minimum number of rotations so that all the values in A are the same, or all the values in B are the same.

If it cannot be done, return -1.

 

Example 1:



Input: A = [2,1,2,4,2,2], B = [5,2,6,2,3,2]
Output: 2
Explanation: 
The first figure represents the dominoes as given by A and B: before we do any rotations.
If we rotate the second and fourth dominoes, we can make every value in the top row equal to 2, as indicated by the second figure.
Example 2:

Input: A = [3,5,1,2,3], B = [3,6,3,3,4]
Output: -1
Explanation: 
In this case, it is not possible to rotate the dominoes to make one row of values equal.
 

Note:

1 <= A[i], B[i] <= 6
2 <= A.length == B.length <= 20000
*/
class Solution {
private:
    int N;

    int recurse1(const int i, const int prev_val, const std::vector<int>& A, const std::vector<int>& B) {
        if (i == N) {
            return 0;
        }
        if (A[i] == prev_val) {
            return recurse1(i+1, prev_val, A, B);
        } else if (B[i] == prev_val) {
            auto ans = recurse1(i+1, prev_val, A, B);
            return ans < 0 ? -1 : 1 + ans;
        } else {
            return -1;
        }
    }

    int solution1(std::vector<int>& A, std::vector<int>& B) {
        N = A.size();
        const auto w = recurse1(1, A[0], A, B);
        const auto x = recurse1(1, B[0], A, B);
        const auto y = recurse1(1, B[0], B, A);
        const auto z = recurse1(1, A[0], B, A);
        
        auto ans = INT_MAX;
        for (auto& v : std::vector<int>{w, x, y, z}) {
            if (v >= 0 and v < ans) {
                ans = v;
            }
        }
        return ans == INT_MAX ? -1 : ans;
    }
public:
    int minDominoRotations(vector<int>& A, vector<int>& B) {
        return solution1(A, B);
    }
};
