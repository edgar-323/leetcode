/*
You are given a binary tree in which each node contains an integer value.
Find the number of paths that sum to a given value.
The path does not need to start or end at the root or a leaf, but it must go downwards (traveling only from parent nodes to child nodes).
The tree has no more than 1,000 nodes and the values are in the range -1,000,000 to 1,000,000.

Example:

root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8

      10
     /  \
    5   -3
   / \    \
  3   2   11
 / \   \
3  -2   1

Return 3. The paths that sum to 8 are:

1.  5 -> 3
2.  5 -> 2 -> 1
3. -3 -> 11
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
    /*****************************************************/
	int checkSubtree1(const TreeNode* root, const int pre, const int sum) {
        // Checks if `root->val + pre == sum` and if so, adds one to result.
        // Recursively does same for `root->left` and `root->right`.
        // This includes all nodes. Does not skip any. Of course, breaks paths between left and right nodes.
        if ( !root ) {
            return 0;
        }
        int current = pre + root->val;
        return (current == sum) + checkSubtree1(root->left, current, sum) + checkSubtree1(root->right, current, sum);
    }
	int recurse1(const TreeNode* root, int sum) {
        // If root is NULL, return 0 since there is nothing to check
        if ( !root ) {
            return 0;
        }
        // check how many paths contain value `sum` when we include all nodes in subtree rooted at `root`.
        // Then also consider when we don't include `root`, which implies we do same checks for `root->left` and `root->right`.
        return checkSubtree1(root, 0, sum) + recurse1(root->left, sum) + recurse1(root->right, sum);
    }
    int solution1(const TreeNode* root, const int sum) {
        /* Time-Complexity:     O( N^2 )
         * Space-Complexity:    O(  H  )
         *  where:
         *      N = size( root )
         *      H = height( root )
         * */
        return recurse1( root, sum );
    } 
	/*****************************************************/
	int recurse2(TreeNode* root, const int sum, std::unordered_map<int, int>& map, const int pre) {
        if ( !root ) {
            return 0;
        }
        // Accumulate sum of values of ancestor nodes:
        root->val += pre;
        // First off it checks if current accumulation equals `sum` and, if so, adds 1.
        // Secondly it checks if a previous accumulation exists: `current_accumulation - sum`.
        // If so it adds the number of previous nodes that had this accumulation.
        // Explaination:
        // If some ancestor has accumulation: `current_accumulation - sum`, it implies that the sum
        // of node-values on path from ancestor to current node (not including ancestor node itself)
        // sums up to `sum`.
        // There may be more than one ancestor who has this property, so we use the map and store the count
        // of such ancestors.
        int res = (root->val == sum) + (map.count(root->val - sum) ? map[root->val - sum] : 0);
        // Now `root` becomes an ancestor with accumulation `root->val` and so we increment that value in `map`.
        // But when we are done recursing we decrement that value because `root` will no long be an ancestor.
        map[root->val]++;
        res += recurse2(root->left, sum, map, root->val) + recurse2(root->right, sum, map, root->val);
        map[root->val]--;
        // leave `root->val` as we found it. Not a necessity for the algorithm but it is good practice.
        root->val -= pre;

        return res;
    }
    int solution2(TreeNode* root, const int sum) {
        /* Time-Complexity:     O( N ) (Avg)
         * Space-Complexity:    O( N )
         * */
        // Keys of `map` will be accumulation (sum) of node-values along a path
        // Values will be count of such keys.
        std::unordered_map<int, int> map;
        return recurse2(root, sum, map, 0);
    }
    /*****************************************************/
public:
    int pathSum(TreeNode* root, int sum) {
        return solution2(root, sum);
    }
};
