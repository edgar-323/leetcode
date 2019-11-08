/*
Alice and Bob take turns playing a game, with Alice starting first.

Initially, there is a number N on the chalkboard.  On each player's turn, that player makes a move consisting of:

Choosing any x with 0 < x < N and N % x == 0.
Replacing the number N on the chalkboard with N - x.
Also, if a player cannot make a move, they lose the game.

x divides N
==> x*m = N, for some non-negative m
==> N - x = x*m - x = x*(m - 1)



Return True if and only if Alice wins the game, assuming both players play optimally.
 
Example 1:
Input: 2
Output: true
Explanation: Alice chooses 1, and Bob has no more moves.

Example 2:
Input: 3
Output: false
Explanation: Alice chooses 1, Bob chooses 1, and Alice has no more moves.

Note:
1 <= N <= 1000
*/

class Solution {
private:
	bool solution1(const int N) {
		return !(N&1); 
	}
public:
    bool divisorGame(int N) {
		return solution1(N);        
    }
};
