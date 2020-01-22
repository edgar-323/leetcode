/*
Given a binary tree

struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}

Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.
Initially, all next pointers are set to NULL.
Follow up:
You may only use constant extra space.
Recursive approach is fine, you may assume implicit stack space does not count as extra space for this problem.

Example 1:
Input: root = [1,2,3,4,5,null,7]
Output: [1,#,2,3,#,4,5,7,#]
Explanation: Given the above binary tree (Figure A), your function should populate each next pointer to point to its next right node, just like in Figure B. The serialized output is in level order as connected by the next pointers, with '#' signifying the end of each level.

Constraints:
The number of nodes in the given tree is less than 6000.
-100 <= node.val <= 100
*/
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/
class Solution {
private:
    void recurse1(Node* node, Node* next) {
        if (not node) {
            return;
        }
        node->next = next;
        
        if (not next) {
            recurse1(node->right, NULL);
            recurse1(node->left, node->right);
        } else {
            for (; next and not next->left and not next->right; next = next->next);
            Node* new_next = not next ? NULL : next->left ? next->left : next->right;
            recurse1(node->right, new_next);
            recurse1(node->left, node->right ? node->right : new_next);
        }
    }

    Node* solution1(Node* root) {
        recurse1(root, NULL);
        return root;
    }

public:
    Node* connect(Node* root) {
        return solution1(root);        
    }
};
