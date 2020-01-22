/*
Given an n-ary tree, return the level order traversal of its nodes' values.
Nary-Tree input serialization is represented in their level order traversal, each group of children is separated by the null value (See examples).

Example 1:
Input: root = [1,null,3,2,4,null,5,6]
Output: [[1],[3,2,4],[5,6]]

Example 2:
Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
Output: [[1],[2,3,4,5],[6,7,8,9,10],[11,12,13],[14]]

Constraints:
The height of the n-ary tree is less than or equal to 1000
The total number of nodes is between [0, 10^4]
*/
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/
class Solution {
private:
	std::vector<std::vector<int>> solution1(Node* root) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         *      Where N = # of nodes in root
         * The space complexity is due to the Queue property of BFS algorithm.
         * If the tree is full, then the last level will hold N/2 nodes.
         */
        if (not root) {
            return {};
        }
        auto levels = std::vector<std::vector<int>>();
        std::queue<Node*> Q;
        Q.push(root);
        
        while (not Q.empty()) {
            const int N = Q.size(); // Size of current level
            auto level = std::vector<int>(N);
            for (int i = N; i; --i) {
                Node* node = Q.front(); Q.pop(); 
                level[N-i] = node->val;
                for (auto child : node->children) {
                    Q.push(child);
                }
            }
            levels.push_back(level);
        }

        return levels;
	}
public:
    vector<vector<int>> levelOrder(Node* root) {
  		return solution1(root);      
    }
};
