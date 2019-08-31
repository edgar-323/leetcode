/*
You are given a perfect binary tree where all leaves are on the same level, and every parent has two children. The binary tree has the following definition:

struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}
Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.
Initially, all next pointers are set to NULL.

Note:
You may only use constant extra space.
Recursive approach is fine, implicit stack space does not count as extra space for this problem.
*/

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() {}

    Node(int _val, Node* _left, Node* _right, Node* _next) {
        val = _val;
        left = _left;
        right = _right;
        next = _next;
    }
};
*/

class Solution {
private:
    void recurse1(Node* node, Node* next) {
        if (node == NULL) {
            return;
        }
        node->next = next;
        recurse1(node->right, next ? next->left : NULL);
        recurse1(node->left, node->right);
    }

	Node* solution1(Node* root) {
        /* *****************************************
         * Time-Complexity:     O(N)
         * Space-Complexity:    O(H)
         *
         * where 
         *  N = size(root)
         *  H = height(root)
         * *****************************************
         * This is the problem I was asked during my
         * one of my interviews at BloombergLP.
         * They placed no restrictions on the space
         * complexity and only asked that I solve 
         * the problem in linear time and I used 
         * BFS alforithm to solve this.
         * However, this LeetCode version of the 
         * problem only allows implicit stack space
         * and so I utilized DFS alforithm in a 
         * clever manner to solve this.
         * *****************************************
         * */ 
        recurse1(root, NULL);
        return root;
	}
public:
    Node* connect(Node* root) {
   		return solution1(root);   
    }
};
