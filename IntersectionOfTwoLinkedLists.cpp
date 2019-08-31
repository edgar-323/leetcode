/*
Write a program to find the node at which the intersection of two singly linked lists begins.

Notes:
If the two linked lists have no intersection at all, return null.
The linked lists must retain their original structure after the function returns.
You may assume there are no cycles anywhere in the entire linked structure.
Your code should preferably run in O(n) time and use only O(1) memory.
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
    ListNode* solution1(ListNode *headA, ListNode *headB) {
        /*
        Time-Complexity:    O(N) (Average)
        Space-Comlpexity:   O(N)
        */
        std::unordered_set<ListNode*> seen;
        while (headA != NULL) {
            seen.emplace(headA);
            headA = headA->next;
        }
        while (headB != NULL) {
            if (seen.count(headB) > 0) {
                return headB;
            }
            headB = headB->next;
        }
        return NULL;
    }
    
    int size(ListNode* node) {
        int len = 0;
        while (node != NULL) {
            ++len;
            node = node->next;
        }
        return len;
    }
    
    ListNode* solution2(ListNode *headA, ListNode *headB) {
        /*
        Time-Complexity:    O(N)
        Space-Complexity:   O(1)
        */
        int sizeA = size(headA);
        int sizeB = size(headB);
        while (sizeA > sizeB) {
            headA = headA->next;
            --sizeA;
        }
        while (sizeA < sizeB) {
            headB = headB->next;
            --sizeB;
        }
        while (headA != NULL) {
            if (headA == headB) {
                return headA;
            }
            headA = headA->next;
            headB = headB->next;
        }
        return NULL;
    }
    
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        return solution2(headA, headB);
    }
};
