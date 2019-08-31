/*
Given a binary tree, flatten it to a linked list in-place.

For example, given the following tree:

    1
   / \
  2   5
 / \   \
3   4   6
The flattened tree should look like:

1
 \
  2
   \
    3
     \
      4
       \
        5
         \
          6
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
    TreeNode* head;
    TreeNode* tail;
    Pair(TreeNode* _head, TreeNode* _tail):
        head( _head ), tail( _tail ) {}
};

class Solution {
private:
    Pair recurse1(TreeNode* node) {
        // Assumes `node` is never NULL
        if (node->left == NULL && node->right == NULL) {
            // `node` is a leaf, so we return a list with head and tail as `node`
            // Note that `Pair` is a really light weight object with two pointers
            // as its data members
            return Pair(node, node);
        } else if (node->left == NULL) {
            // left subtree is NULL so we flatten right subtree and set `node's` 
            // right subtree as the head of the returned list.
            // Then we change head of returned tree to `node`. 
            Pair rightPair = recurse1(node->right);
            node->right = rightPair.head;
            rightPair.head = node;
            return rightPair;
        } else if (node->right == NULL) {
            // right subtree is NULL, so we faltten left subtree.
            // Since we can to transform the entire tree to only have the right
            // subtrees set, we first set the right subtree to the head of the 
            // list and then we set the left subtree to NULL and then we set 
            // the head of the list to `node`. 
            Pair leftPair = recurse1(node->left);
            node->right = leftPair.head;
            node->left = NULL;
            leftPair.head = node;
            return leftPair;
        } else {
            // Combination of above cases
            Pair leftPair = recurse1(node->left);
            Pair rightPair = recurse1(node->right);
            node->left = NULL;
            node->right = leftPair.head;
            leftPair.head = node;
            leftPair.tail->right = rightPair.head;
            leftPair.tail = rightPair.tail;
            return leftPair;
        }
    }
    
    void solution1(TreeNode* root) {
        /*
        ****************************************************
        Idea: 
        Let rS = right subtree, lS = left subtree
        flatten rS with root as tail,
        flatten lS with rS as tail
        return root with lS as tail.
        ****************************************************
        Time-Complexity: 
        Space-Complexity: 
        ****************************************************
        */
        if (root == NULL) {
            return;
        }
        recurse1(root);
    }
    
public:
    void flatten(TreeNode* root) {
        solution1(root);
    }
};
