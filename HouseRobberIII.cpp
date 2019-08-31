/*
The thief has found himself a new place for his thievery again. 
There is only one entrance to this area, called the "root." 
Besides the root, each house has one and only one parent house. 
After a tour, the smart thief realized that "all houses in this place forms a binary tree". 
It will automatically contact the police if two directly-linked houses were broken into on the same night.
Determine the maximum amount of money the thief can rob tonight without alerting the police.

Example 1:
Input: [3,2,3,null,3,null,1]

     3
    / \
   2   3
    \   \ 
     3   1

Output: 7 
Explanation: Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.

Example 2:
Input: [3,4,5,1,3,null,1]

     3
    / \
   4   5
  / \   \ 
 1   3   1

Output: 9
Explanation: Maximum amount of money the thief can rob = 4 + 5 = 9.
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

class Pair {
public:
    int includedParent;
    int excludedParent;
    Pair(int val, bool included) {
        if (included) {
            includedParent = val;
            excludedParent = -1;
        } else {
            excludedParent = val;
            includedParent = -1;
        }
    }
 };

class Solution {
private:
	/*************************************************************************/
    int recurse1(TreeNode* node) {
        if (node == NULL) {
            return 0;
        }
        int retVal = node->val;
        TreeNode* L = node->left;
        TreeNode* R = node->right;
        if (L != NULL) {
            retVal += recurse1(L->left) + recurse1(L->right);
        }
        if (R != NULL) {
            retVal += recurse1(R->left) + recurse1(R->right);
        }
        return retVal;
    }
    int solution1(TreeNode* root) {
        /*
        INCORRECT SOLUTION, DOESN'T CONSIDER ALL CASES.
        */
        if (root == NULL) {
            return 0;
        }
        return max(recurse1(root), 
                   recurse1(root->left) + recurse1(root->right));
    }
    /*************************************************************************/
    int recurse2(TreeNode* node, bool includedParent) {
        if (node == NULL) {
            return 0;
        } else if (includedParent) {
            return recurse2(node->left, false) + recurse2(node->right, false);
        } else {
            return max(recurse2(node->left, false) + 
                       recurse2(node->right, false), 
                      node->val + 
                       recurse2(node->left, true) + 
                       recurse2(node->right, true));
        }
    }
    int solution2(TreeNode* root) {
        /*
        CORRECT SOLUTION, BUT VERY SLOW BECAUSE WE RECOMPUTE 
        PREVIOUSLY COMPUTED VALUES INSTEAD OF STORING THEM.
        */
        return recurse2(root, false);
    }
   	/*************************************************************************/ 
    std::unordered_map<TreeNode*, Pair> memo;
    int recurse3(TreeNode* node, bool includedParent) {
        if (node == NULL) {
            return 0;
        } else if (memo.count(node)) {
            Pair& p = memo.at(node);
            if (includedParent && p.includedParent < 0) {
                p.includedParent = (recurse3(node->left, false) + 
                                    recurse3(node->right, false));
            }
            if (!includedParent && p.excludedParent < 0) {
                p.excludedParent = max(recurse3(node->left, false) + 
                                       recurse3(node->right, false), 
                                      node->val + 
                                       recurse3(node->left, true) + 
                                       recurse3(node->right, true));
            }
            return includedParent ? p.includedParent : p.excludedParent;
        } else {
            int val = includedParent ? 
                    (recurse3(node->left, false) + 
                     recurse3(node->right, false)) :
                    max(recurse3(node->left, false) + 
                       recurse3(node->right, false), 
                      node->val + 
                       recurse3(node->left, true) + 
                       recurse3(node->right, true));
            memo.emplace(node, Pair(val, includedParent));
            return val;
        }
    }
    int solution3(TreeNode* root) {
        /*
        SAME AS SOLUTION2 BUT WE STORE PREVIOUSLY COMPUTED VALUES AND 
        RETRIEVE THEM VIA A HASH TABLE, WHICH GIVES US ABOUT A x112 
        SPEED-UP FROM SOLUTION2.
        */
        return recurse3(root, false);
    }
   	/*************************************************************************/ 
    void recurse4(TreeNode* node, int& max_if_me, int& max_if_not_me) {
        if (node == NULL) {
            max_if_me = max_if_not_me = 0;
            return;
        }
        
        int max_if_left, max_if_not_left;
        recurse4(node->left, max_if_left, max_if_not_left);
        
        int max_if_right, max_if_not_right;
        recurse4(node->right, max_if_right, max_if_not_right);
        
        max_if_me = node->val + max_if_not_left + max_if_not_right;
        max_if_not_me = std::max(
				            max_if_left     + std::max(max_if_right, max_if_not_right), 
                           	max_if_not_left + std::max(max_if_right, max_if_not_right));
    }
    int solution4(TreeNode* root) {
        /*
        Wow this is an AWESOME solution.
        Found it in the discussion session. 
        Credit goes to "Sai Parthasarathy".
        No need to store/retrieve any values.
        Only visit each node once. 
        It gives a x1.33 speedup from solution3.
        */
        int max_if_root, max_if_not_root;
        recurse4(root, max_if_root, max_if_not_root);
        return max(max_if_root, max_if_not_root);
    }
   	/*************************************************************************/ 
public:
    int rob(TreeNode* root) {
        return solution4(root);
    }
};
