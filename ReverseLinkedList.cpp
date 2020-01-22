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
    ListNode* recursively(ListNode* node) {
        if (node == NULL || node->next == NULL) {
            return node;
        }
        ListNode* temp = node->next;
        ListNode* head = recursively(node->next);
        temp->next = node;
        node->next = NULL;
        return head;
    }
    
    ListNode* iteratively(ListNode* head) {
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
    ListNode* reverseList(ListNode* head) {
        // return recursively(head);
        return iteratively(head);
    }
};
