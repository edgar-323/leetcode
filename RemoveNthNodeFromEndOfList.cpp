/*
Given a linked list, remove the n-th node from the end of list and return its head.

Example:
Given linked list: 1->2->3->4->5, and n = 2.
After removing the second node from the end, the linked list becomes 1->2->3->5.

Note:
Given n will always be valid.
Follow up:
Could you do this in one pass?
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
    ListNode* reverse(ListNode* head) {
        if (head == NULL || head->next == NULL) {
            return head;
        }
        ListNode* temp;
        ListNode* prev = head;
        head = head->next;
        prev->next = NULL;
        while (head->next != NULL) {
            temp = head->next;
            head->next = prev;
            prev = head;
            head = temp;
        }
        head->next = prev;
        return head;
    }
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (n <= 0) {
            return head;
        }
        head = reverse(head);
        ListNode* node = head;
        ListNode* prev = NULL;
        int count = 1;
        while (count < n and node) {
            prev = node;
            node = node->next;
            ++count;
        }
        if (count == n and node) {
            if (prev == NULL) {
                head = node->next;
            } else {
                prev->next = node->next;
            }
            node->next = NULL;
        }
        return reverse(head);
    }
};
