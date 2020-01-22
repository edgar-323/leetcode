/*
The demons had captured the princess (P) and imprisoned her in the lefttom-right corner of a dungeon. 
The dungeon consists of M x N rooms laid out in a 2D grid. 
Our valiant knight (K) was initially positioned in the top-left room and must fight his way through the dungeon to rescue the princess.
The knight has an initial health point represented by a positive integer. 
If at any point his health point drops to 0 or below, he dies immediately.

Some of the rooms are guarded by demons, so the knight loses health (negative integers) upon entering these rooms; other rooms are either empty (0's) or contain magic orbs that increase the knight's health (positive integers).

In order to reach the princess as quickly as possible, the knight decides to move only rightward or downward in each step.

Write a function to determine the knight's minimum initial health so that he is able to rescue the princess.

For example, given the dungeon below, the initial health of the knight must be at least 7 if he follows the optimal path RIGHT-> RIGHT -> DOWN -> DOWN.

Note:
The knight's health has no upper bound.
Any room can contain threats or power-ups, even the first room the knight enters and the lefttom-right room where the princess is imprisoned.
*/


class Solution {
private:
    /********************************************************************************************************************************/
    int solution1(const std::vector<std::vector<int>>& dungeon) {
        /* Time-Complexity:     O(M*N)
         * Space-Complexity:    O(M*N)
         */
        /* Explanation: 
         * We will work from bottom-right corner upto top-left corner.
         * Define,
         *      DP[i][j] = minimum health in order to reach cell (i,j)
         *
         *  If we begin at bottom-rigth corner (M-1, N-2) we can see that our health (DP[M-1][N-1]) must be at least 1.
         *  I.e.,
         *      DP[M-1][N-1] + dungeon[M-1][N-1] >= 1
         *      ==> DP[M-1][N-1] >= 1 - dungeon[M-1][N-1].
         *  So we always need to have health of at least 1 but the above equation gives us a potentially bigger lower bound
         *  (in the case where dungeon[M-1][N-1] <= -1), and thus by combinig these arguments:
         *      DP[M-1][N-1] = max{ 1, 1 - dungeon[M-1][N-1] }
         *
         *  Now if we look at the bottom row (excluding bottom-right corner), we know that we can only travel towards the right
         *  grid cell.
         *  If we look at these transitions from left to right, we know that the minimum health at (M-1, j) (i.e., DP[M-1][j]) 
         *  plus the cell value at (M-1, j) (i.e., dungeon[M-1][j]) must be at least as great as the the minimum health at (M-1, j+1)
         *  (i.e., DP[M-1][j+1]), and thus: 
         *      DP[M-1][j] + dungeon[M-1][j] >= DP[M-1][j+1] 
         *  This is because in order to go into (M-1, j+1) from (M-1, j), we must have enough health to enter (M-1, j+1) after leaving 
         *  (M-1, j).
         *  And, remembering that our lowest bound is 1, we have
         *      DP[M-1][j] = max{ 1, DP[M-1][j+1] - dungeon[M-1][j] }
         *
         *  Similarly for the right column,
         *      DP[i][N-1] = max{ 1, DP[i+1][N-1] - dungeon[i][N-1] }
         *
         *  Now for the general case, we need to combine the above two cases, and take best option:
         *      DP[i][j] = max{ 1, min{ DP[i][j+1], DP[i+1][j] } - dungeon[i][j] }
         *
         *  We are intersted in DP[0][0].
         */
        const int M = dungeon.size();
        const int N = dungeon[0].size();
        auto DP = std::vector<std::vector<int>>(M, std::vector<int>(N));
        DP[M-1][N-1] = std::max(1, 1 - dungeon[M-1][N-1]);
        for (int j = N-2; j >= 0; --j) {
            DP[M-1][j] = std::max(1, DP[M-1][j+1] - dungeon[M-1][j]);
        }
        for (int i = M-2; i >= 0; --i) {
            DP[i][N-1] = std::max(0, DP[i+1][N-1] - dungeon[i][N-1]);
        }
        for (int i = M-2; i >= 0; --i) {
            for (int j = N-2; j >= 0; --j) {
                DP[i][j] = std::max(1, std::min(DP[i+1][j], DP[i][j+1]) - dungeon[i][j]);
            }
        }
        return DP[0][0];
    }
    /********************************************************************************************************************************/
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        return solution1(dungeon); 
    }
};
