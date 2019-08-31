/*
Write a function to delete a node (except the tail) in a singly linked list, given only access to that node.
Given linked list -- head = [4,5,1,9], which looks like following:
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
	void solution1(ListNode* node) {
	    if (node == NULL || node->next == NULL) {
            return;
        }
        node->val = node->next->val;
        node->next = node->next->next;
	}
public:
    void deleteNode(ListNode* node) {
    	solution1(node);   
    }
};
