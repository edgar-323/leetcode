/*
Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. 
You can only see the k numbers in the window. 
Each time the sliding window moves right by one position. 
Return the max sliding window.

Example:
Input: nums = [1,3,-1,-3,5,3,6,7], and k = 3
Output: [3,3,5,5,6,7] 
Explanation: 

Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
Note: 
You may assume k is always valid, 1 ≤ k ≤ input array's size for non-empty array.

Follow up:
Could you solve it in linear time?
*/

class Node {
public:
    int val;
    int nextMax;
    Node* next;
    
    Node(int val, Node* next) {
        this->val = val;
        this->next = next;
        if (next != NULL) {
            this->nextMax = (next->next != NULL) ? 
                            max(next->val, next->nextMax) : next->val;
        }
    }
};

class MaxStack {
public:
    /** initialize your data structure here. */
    Node* head;
    MaxStack() {
        head = NULL;
    }
    
    ~MaxStack() {
        Node* next;
        while (head != NULL) {
            next = head->next;
            delete head;
            head = next;
        }
    }
    
    void push(int x) {
        head = new Node(x, head);
    }
    
    void pop() {
        if (head != NULL) {
            Node* nextNode = head->next;
            delete head;
            head = nextNode;
        }
    }
    
    int top() {
        return head->val;
    }
    
    int getMax() {
        return (head->next == NULL) ? 
            head->val : max(head->val, head->nextMax);
    }
    
    bool empty() {
        return head == NULL;
    }
    
    void reverse() {
        if (head == NULL || head->next == NULL) {
            return;
        }
        Node* before = head->next;
        head->next = NULL;
        head->nextMax = INT_MIN; // garbage
        before->nextMax = head->val;
        Node* nextBefore = before->next;
        before->next = head;
        head = before;
        before = nextBefore;
        while (before != NULL) {
            Node* nextBefore = before->next;
            before->next = head;
            before->nextMax = max(head->val, head->nextMax);
            head = before;
            before = nextBefore;
        }
    }
};


class SlidingDeque {
private:
    MaxStack* popper;
    MaxStack* pusher;

    void checkCapacities() {
        if (popper->empty()) {
            pusher->reverse();
            MaxStack* temp = pusher;
            pusher = popper;
            popper = temp;
        }
    }
    
public: 
    SlidingDeque(std::vector<int>& nums, int k) {
        popper = new MaxStack();
        pusher = new MaxStack();
        for (int i = k-1; i > -1; --i) {
            popper->push(nums[i]);
        }
    }
    
    ~SlidingDeque() {
        delete popper;
        delete pusher;
    }
    
    void push(int x) {
        checkCapacities();
        popper->pop();
        pusher->push(x);
    }
    
    int getMax() {
        return popper->empty() ? pusher->getMax() : 
                pusher->empty() ? popper->getMax() : 
                max(pusher->getMax(), popper->getMax());
    }
};

class Solution {
private:
    std::vector<int> mySolution(std::vector<int>& nums, int k) {
        /*
        Time-Complexity: 
            ==> c1*(N - N/K) + c2*K*(N/K - 1)
                = c1*N + (c2*K - c1)*(N/K) - c2*K
                < c1*N + c2*K*(N/K)
                = c1*N + c2*N
                = (c1+ c2)*N
                = c3*N
            ==> O(N)
            
        Space-Complexity: 
            ==> O(K)
            
        */
        const int N = nums.size();
        if (N == 0) {
            return std::vector<int>();
        }
        SlidingDeque deque = SlidingDeque(nums, k);
        std::vector<int> slidingWindows(N-k+1);
        slidingWindows[0] = deque.getMax();
        for (int i = k; i < N; ++i) {
            deque.push(nums[i]);
            slidingWindows[i-k+1] = deque.getMax();
        }
        
        return slidingWindows;
    }
    
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        return mySolution(nums, k);
    }
};
