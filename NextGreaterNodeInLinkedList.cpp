/*
We are given a linked list with head as the first node.  Let's number the nodes in the list: node_1, node_2, node_3, ... etc.
Each node may have a next larger value: 
    for node_i, next_larger(node_i) is the node_j.val such that j > i, node_j.val > node_i.val, and j is the smallest possible choice.  
    If such a j does not exist, the next larger value is 0.

Return an array of integers answer, where answer[i] = next_larger(node_{i+1}).

Note that in the example inputs (not outputs) below, arrays such as [2,1,5] represent the serialization of a linked list with a head node value of 2, second node value of 1, and third node value of 5.

 

Example 1:

Input: [2,1,5]
Output: [5,5,0]
Example 2:

Input: [2,7,4,3,5]
Output: [7,0,5,5,0]
Example 3:

Input: [1,7,5,1,9,2,5,1]
Output: [7,9,9,9,0,5,0,0]
 

Note:

1 <= node.val <= 10^9 for each node in the linked list.
The given list has length in the range [0, 10000].
*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
private:
    std::vector<int> solution1(ListNode* head) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         */

        if (not head) {
            return {};
        }
        
        auto node_stack = std::stack<ListNode*>();
        while (head) {
            node_stack.push(head);
            head = head->next;
        }
        const int N = node_stack.size();

        auto val_stack = std::stack<int>();
        auto next_greater_val = std::vector<int>(N);
        for (int i = N-1; i >= 0; --i) {
            auto node = node_stack.top(); node_stack.pop();
            while (not val_stack.empty() and node->val >= val_stack.top()) {
                val_stack.pop();
            }
            next_greater_val[i] = val_stack.empty() ? 0 : val_stack.top();
            val_stack.push(node->val);
        }

        return next_greater_val; 
    }
public:
    vector<int> nextLargerNodes(ListNode* head) {
        return solution1(head);       
    }
};
