/*
Given a binary tree rooted at root, the depth of each node is the shortest distance to the root.
A node is deepest if it has the largest depth possible among any node in the entire tree.
The subtree of a node is that node, plus the set of all descendants of that node.
Return the node with the largest depth such that it contains all the deepest nodes in its subtree.

Example 1:
Input: [3,5,1,6,2,0,8,null,null,7,4]
Output: [2,7,4]
Explanation:
We return the node with value 2, colored in yellow in the diagram.
The nodes colored in blue are the deepest nodes of the tree.
The input "[3, 5, 1, 6, 2, 0, 8, null, null, 7, 4]" is a serialization of the given tree.
The output "[2, 7, 4]" is a serialization of the subtree rooted at the node with value 2.
Both the input and output have TreeNode type.

Note:
The number of nodes in the tree will be between 1 and 500.
The values of each node are unique.
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
    TreeNode* deepest_node;
    int max_nodes;
    int max_depth;
    
    std::pair<int,int> recurse1(TreeNode* node, const int depth) {
        // Returns pair (a, b), where:
        //  a = maximum depth from `root` to deepest descendant of `node`
        //  b = number of descendants of `node` having depth `a`
        
        if (not node) {
            return std::make_pair(-1,-1);
        }
        
        if (not node->left and not node->right) {
            if (depth > max_depth) {
                max_depth = depth;
                max_nodes = 1;
                deepest_node = node;
            }
            return std::make_pair(depth, depth == max_depth);
        }
        
        const auto left = recurse1(node->left, depth+1);
        const auto right = recurse1(node->right, depth+1);
        
        int child_depth;
        int num_nodes;
        if (left.first == right.first) {
            child_depth = left.first;
            num_nodes = left.second + right.second;
        } else if (left.first > right.first) {
            child_depth = left.first;
            num_nodes = left.second;
        } else {
            child_depth = right.first;
            num_nodes = right.second;
        }
        
        if (child_depth == max_depth and num_nodes > max_nodes) {
            max_nodes = num_nodes;
            deepest_node = node;
        }
        
        return std::make_pair(child_depth, num_nodes);
    }

    TreeNode* solution1(TreeNode* root) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(H)
         *      Where:
         *          N = number of nodes in root
         *          H = height of root
         */
        deepest_node = NULL;
        max_nodes = 0;
        max_depth = -1;

        recurse1(root, 0);

        return deepest_node;
    }
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        return solution1(root);
    }
};
