/*
Given a singly linked list, determine if it is a palindrome.

Example 1:

Input: 1->2
Output: false
Example 2:

Input: 1->2->2->1
Output: true
Follow up:
Could you do it in O(n) time and O(1) space?
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
    
    int size(ListNode* node) {
        int len = 0;
        while (node != NULL) {
            node = node->next;
            ++len;
        }
        return len;
    }
    
    bool equal(ListNode* A, ListNode* B) {
        while (A != NULL && B != NULL) {
            if (A->val != B->val) {
                return false;
            }
            A = A->next;
            B = B->next;
        }
        
        return A == B;
    }
    
    bool mySolution(ListNode* root) {
        /*
        Time-Complexity:    O(N)
        Space-Complexity:   O(1)
        */
        
        int N = size(root);
        if (N <= 1) {
            return true;
        }
        
        int halfSize = N / 2 - 1;
        ListNode* halfList = root;
        
        for (int i = 0; i < halfSize; ++i) {
            halfList = halfList->next;
        }
        
        ListNode* temp = halfList->next;
        halfList->next = NULL;
        halfList = temp;
        if (N % 2 == 1) {
            temp = halfList->next;
            halfList->next = NULL;
            halfList = temp;
        }
        
        return equal(root, reverse(halfList));
    }
    
public:
    bool isPalindrome(ListNode* head) {
        return mySolution(head);
    }
};
