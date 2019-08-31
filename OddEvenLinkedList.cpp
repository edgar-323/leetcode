/*
Given a singly linked list, group all odd nodes together followed by the even nodes. Please note here we are talking about the node number and not the value in the nodes.
You should try to do it in place. The program should run in O(1) space complexity and O(nodes) time complexity.

Example 1:
Input: 1->2->3->4->5->NULL
Output: 1->3->5->2->4->NULL


Example 2:
Input: 2->1->3->5->6->4->7->NULL
Output: 2->3->6->7->1->5->4->NULL

Note:
The relative order inside both the even and odd groups should remain as it was in the input.
The first node is considered odd, the second node even and so on ...
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
    ListNode* remove(ListNode** list) {
        ListNode* head = *list;
        *list = head->next;
        head->next = NULL;
        return head;
    }
    ListNode* prepend(ListNode* list, ListNode* node) {
        node->next = list;
        return node;
    }
    ListNode*i reverse(ListNode* head) {
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
    ListNode* concat(ListNode* first_list, ListNode* second_list) {
        if (first_list == NULL) {
            return second_list;
        } else if (second_list == NULL) {
            return first_list;
        }
        ListNode* last = first_list;
        for (; last->next != NULL; last = last->next);
        last->next = second_list;
        return first_list; 
    } 
    ListNode* solution1(ListNode* head) {
        /* 
         * Time-Complexity:
         *  N + 0.5*N + 0.5*N + 0.5N
         *  ==> 2.5*N
         *  ==> O( N )
         *  Space-Complexity:
         *  ==> O( 1 )
         *  */
        ListNode* odds = NULL;
        ListNode* evens = NULL;
        for (size_t i = 1; head != NULL; ++i) {
            if ( i & 1 ) {
                odds = prepend( odds,  remove( &head ) );
            } else {
                evens = prepend( evens, remove( &head ) );
            }
        }
        return concat( reverse( odds ), reverse( evens ) );
    }
public:
    ListNode* oddEvenList(ListNode* head) {
        return solution1( head ); 
    }
};
