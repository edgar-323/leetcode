/*
A complete binary tree is a binary tree in which every level, except possibly the last, is completely filled, and all nodes are as far left as possible.
Write a data structure CBTInserter that is initialized with a complete binary tree and supports the following operations:
CBTInserter(TreeNode root) initializes the data structure on a given tree with head node root;
CBTInserter.insert(int v) will insert a TreeNode into the tree with value node.val = v so that the tree remains complete, and returns the value of the parent of the inserted TreeNode;
CBTInserter.get_root() will return the head node of the tree.

Example 1:
Input: inputs = ["CBTInserter","insert","get_root"], inputs = [[[1]],[2],[]]
Output: [null,1,[1,2]]

Example 2:
Input: inputs = ["CBTInserter","insert","insert","get_root"], inputs = [[[1,2,3,4,5,6]],[7],[8],[]]
Output: [null,3,4,[1,2,3,4,5,6,7,8]]

Note:
The initial given tree is complete and contains between 1 and 1000 nodes.
CBTInserter.insert is called at most 10000 times per test case.
Every value of a given or inserted node is between 0 and 5000.
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
class CBTInserter {
private:
    TreeNode* root;
    std::vector<TreeNode*> heap;

    int size(TreeNode* node) {
        if (not node) {
            return 0;
        }
        return 1 + size(node->left) + size(node->right); 
    }

    void init_heap(TreeNode* node, const int i) {
        heap[i] = node;  
        if (not node->left) {
            return;
        }
        init_heap(node->left, left_child(i));
        if (node->right) {
            init_heap(node->right, right_child(i));
        }
    }

    int parent(const int i) {
        return i / 2;
    }

    int left_child(const int i) {
        return 2*i;
    }

    int right_child(const int i) {
        return 2*i + 1;
    }

public:
    CBTInserter(TreeNode* root) {
        // O(initial_sz)
        this->root = root; 
        const int initial_sz = size(root);
        heap = std::vector<TreeNode*>(initial_sz + 1, NULL);
        init_heap(root, 1);
    }
    
    int insert(int v) {
        // O(1) (Amortized)
        const int i = heap.size();    
        heap.push_back(new TreeNode(v));
        TreeNode* par = heap[parent(i)];
        if (i & 1) {
            par->right = heap[i];
        } else {
            par->left = heap[i];
        }

        return par->val; 
    }
    
    TreeNode* get_root() {
        // O(1)
        return root; 
    }
};

/**
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter* obj = new CBTInserter(root);
 * int param_1 = obj->insert(v);
 * TreeNode* param_2 = obj->get_root();
 */
