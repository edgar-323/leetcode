/*
Given a non-empty integer array, 
find the minimum number of moves required to make all array elements equal, 
where a move is incrementing a selected element by 1 or decrementing a selected element by 1.

You may assume the array's length is at most 10,000.

Example:
Input:
[1,2,3]
Output:
2
Explanation:
Only two moves are needed (remember each move increments or decrements one element):
[1,2,3]  =>  [2,2,3]  =>  [2,2,2]
*/
class Solution {
private:
    int solution1(std::vector<int>& A) {
        std::sort(A.begin(), A.end());

        int moves = 0;
        int left = 0;
        int right = A.size() - 1;

        while (left < right) {
            moves += A[right--] - A[left++];
        }

        return moves;
    }
public:
    int minMoves2(vector<int>& nums) {
        return solution1(nums);    
    }
};
