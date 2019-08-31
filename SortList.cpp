/*
Sort a linked list in O(n log n) time using constant space complexity.

Example 1:
Input: 4->2->1->3
Output: 1->2->3->4

Example 2:
Input: -1->5->3->4->0
Output: -1->0->3->4->5
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
    /**************************************************/
    ListNode* solution1(ListNode* head) {
        /*
        Time-Complexity:    O( N*log(N) )
        Space-Complexity:   O(     N    )
        */
        
        std::vector<int> nums;
        ListNode* node = head;
        while (node != NULL) {
            nums.push_back(node->val);
            node = node->next;
        }
        std::sort(nums.begin(), nums.end());
        node = head;
        int i = 0;
        while (node != NULL) {
            node->val = nums[i++];
            node = node->next;
        }
        
        return head;
    }
    /**************************************************/ 
    int size(ListNode* head) {
        int sz = 0;
        while (head) {
            head = head->next;
            ++sz;
        }
        return sz;
    }
    ListNode* solution2(ListNode* head) {
        /* Time-Complexity:     O( N*log(N) )
         * Space-Complexity:    O(  log(N)  )
         *  Note:
         *  The space complexity is due to the stack calls.
         *  For each call we allocate constant number of 
         *  variables.
         * */
        int N = size( head );
        if (N <= 1) {
            return head;
        }
        ListNode* firstHalf = head;
        for (int i = 0; i < N/2-1; ++i) {
            head = head->next;
        }
        ListNode* secondHalf = head->next;
        head->next = NULL;
        firstHalf = solution2( firstHalf );
        secondHalf = solution2( secondHalf );
        
        if (firstHalf->val < secondHalf->val) {
            head = firstHalf;
            firstHalf = firstHalf->next;
        } else {
            head = secondHalf;
            secondHalf = secondHalf->next;
        }
        ListNode* tail = head;

        while (firstHalf and secondHalf) {
            if (firstHalf->val < secondHalf->val) {
                tail->next = firstHalf;
                tail = firstHalf;
                firstHalf = firstHalf->next;
            } else {
                tail->next = secondHalf;
                tail = secondHalf;
                secondHalf = secondHalf->next;
            }
        }
        while (firstHalf) {
            tail->next = firstHalf;
            tail = firstHalf;
            firstHalf = firstHalf->next;
        }
        while (secondHalf) {
            tail->next = secondHalf;
            tail = secondHalf;
            secondHalf = secondHalf->next;
        }

        return head;
    }
    /**************************************************/
public:
    ListNode* sortList(ListNode* head) {
        return solution1( head );
    }
};
