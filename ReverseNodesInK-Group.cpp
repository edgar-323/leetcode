/*
Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.
K is a positive integer and is less than or equal to the length of the linked list.
If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

Example:
Given this linked list: 1->2->3->4->5
For k = 2, you should return: 2->1->4->3->5
For k = 3, you should return: 3->2->1->4->5

Note:
Only constant extra memory is allowed.
You may not alter the values in the list's nodes, only nodes itself may be changed.
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
    int length(ListNode* head) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(1)
         *      Where:
         *          N = length(head)
         */
        int sz = 0;
        for (auto node = head; node; node = node->next, ++sz);
        return sz;
    }

    std::pair<ListNode*,ListNode*> reverse1(ListNode* head, const int K) {
        /* Time-Complexity:     O(K)
         * Space-Complexity:    O(1)
         */

        auto tail = head;
        auto prev = head;
        head = head->next;
        auto next = head->next;
        int k = 2;
        while (k < K) {
            auto temp = head->next;
            head->next = prev;
            prev = head;
            head = temp;
            next = head->next; 
            ++k; 
        }
        tail->next = next;
        head->next = prev;

        return {head, tail};
    }

    ListNode* solution1(ListNode* head, const int K) {
        /* Space-Complexity:    O(N)
         * Space-Complexity:    O(1)
         *      Where:
         *          N = length(head)
         */
        if (K == 1) {
            return head;
        }
        const auto N = length(head);
        auto node = head;
        ListNode* tail = NULL;
        for (int k = 0; N - k >= K; k += K) {
            auto node_pair = reverse1(node, K);
            if (tail) {
                tail->next = node_pair.first;
                tail = node_pair.second;
            } else {
                head = node_pair.first;
                tail = node_pair.second;
            }
            node = tail->next;
        }

        return head;
    }
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        return solution1(head, k);    
    }
};
