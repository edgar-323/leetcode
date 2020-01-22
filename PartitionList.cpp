/*
Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.
You should preserve the original relative order of the nodes in each of the two partitions.

Example:
Input: head = 1->4->3->2->5->2, x = 3
Output: 1->2->2->4->3->5
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
    ListNode* solution1(ListNode* head, const int x) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         */
        auto lt_x = std::deque<ListNode*>();
        auto gt_x = std::deque<ListNode*>();        
        for (auto node = head; node; node = node->next) {
            if (node->val < x) {
                lt_x.push_back(node);
            } else {
                gt_x.push_back(node);
            }
        }
        ListNode* last = NULL;
        if (not lt_x.empty()) { 
            head = lt_x.front(); lt_x.pop_front();
            last = head;
            while (not lt_x.empty()) {
                last->next = lt_x.front(); lt_x.pop_front();
                last = last->next;
            }
            last->next = NULL; 
        }
        if (not gt_x.empty()) {
            if (not last) {
                head = gt_x.front(); gt_x.pop_front();
                last = head;
            }
            while (not gt_x.empty()) {
                last->next = gt_x.front(); gt_x.pop_front();
                last = last->next;
            }
            last->next = NULL;
        }
        return head;
    }
public:
    ListNode* partition(ListNode* head, int x) {
        return solution1(head, x);        
    }
};
