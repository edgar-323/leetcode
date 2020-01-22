/*
Two players play a turn based game on a binary tree.
We are given the root of this binary tree, and the number of nodes n in the tree.
n is odd, and each node has a distinct value from 1 to n.
Initially, the first player names a value x with 1 <= x <= n, and the second player names a value y with 1 <= y <= n and y != x.
The first player colors the node with value x red, and the second player colors the node with value y blue.
Then, the players take turns starting with the first player.
In each turn, that player chooses a node of their color (red if player 1, blue if player 2) 
and colors an uncolored neighbor of the chosen node (either the left child, right child, or parent of the chosen node.)

If (and only if) a player cannot choose such a node in this way, they must pass their turn.  
If both players pass their turn, the game ends, and the winner is the player that colored more nodes.

You are the second player.  
If it is possible to choose such a y to ensure you win the game, return true.  
If it is not possible, return false.
 
Example 1:
Input: root = [1,2,3,4,5,6,7,8,9,10,11], n = 11, x = 3
Output: true
Explanation: The second player can choose the node with value 2.

Constraints:
root is the root of a binary tree with n nodes and distinct node values from 1 to n.
n is odd.
1 <= x <= n <= 100
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
private:
    std::unordered_map<TreeNode*,int> size;   
    TreeNode* X;
            
    int compute_sizes(TreeNode* node, const int x) {
        if (not node) {
            return 0;
        }
        if (node->val == x) {
            X = node;
        }
        const int sz = 1 + compute_sizes(node->left, x) + compute_sizes(node->right, x);
        size[node] = sz;

        return sz;
    } 

    bool solution1(TreeNode* root, const int N, const int x) {
        size.clear();
        X = NULL;
        compute_sizes(root, x);

        auto left = X->left;
        auto right = X->right;

        return  (size[root] - 2*size[X] > 0) or
                (left and 2*size[left] - size[root] > 0) or
                (right and 2*size[right]  - size[root] > 0);
    }
public:
    bool btreeGameWinningMove(TreeNode* root, int n, int x) {
        return solution1(root, n, x);       
    }
};
