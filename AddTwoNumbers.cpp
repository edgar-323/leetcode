/*
You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.
You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Example:
Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
Explanation: 342 + 465 = 807.
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
    ListNode* solution1(ListNode* l1, ListNode* l2) { 
        if (l1 == NULL || l2 == NULL) {
            return NULL;
        }
        ListNode* result = new ListNode(0);
        ListNode* runner = result;
        int sum;
        int remainder = 0;
        while (l1 != NULL || l2 != NULL || remainder) {
            sum = ((l1 != NULL) ? l1->val : 0) + 
                    ((l2 != NULL) ? l2->val : 0) +
                    remainder;
            runner->val = sum % 10;
            remainder = sum / 10;
            l1 = (l1 != NULL) ? l1->next : NULL;
            l2 = (l2 != NULL) ? l2->next : NULL;
            runner->next = (l1 != NULL || l2 != NULL || remainder) ? 
                            new ListNode(0) : NULL;
            runner = runner->next;
        }
        
        return result;
    }
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		return solution1( l1, l2 );
	}
};
