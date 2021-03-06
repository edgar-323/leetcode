/*
Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.
Calling next() will return the next smallest number in the BST.
 
Example:
BSTIterator iterator = new BSTIterator(root);
iterator.next();    // return 3
iterator.next();    // return 7
iterator.hasNext(); // return true
iterator.next();    // return 9
iterator.hasNext(); // return true
iterator.next();    // return 15
iterator.hasNext(); // return true
iterator.next();    // return 20
iterator.hasNext(); // return false

Note:
next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree.
You may assume that next() call will always be valid, that is, there will be at least a next smallest number in the BST when next() is called.
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
class BSTIterator {
private:
    std::stack<TreeNode*> stack;
    void push_left_most_nodes(TreeNode* node) {
        while (node) {
            stack.push(node);
            node = node->left;  
        }
    }
public:
    BSTIterator(TreeNode* root) {
        push_left_most_nodes(root);  
    }
    
    /** @return the next smallest number */
    int next() {
        TreeNode* node = stack.top(); stack.pop();
        push_left_most_nodes(node->right); 

        return node->val;
    }
    
    /** @return whether we have a next smallest number */
    bool hasNext() {
        return not stack.empty(); 
    }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
