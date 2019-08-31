/*
Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
getMin() -- Retrieve the minimum element in the stack.

Example:
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> Returns -3.
minStack.pop();
minStack.top();      --> Returns 0.
minStack.getMin();   --> Returns -2.
*/

class Node {
public:
    int val;
    int nextMin;
    Node* next;
    
    Node(int val, Node* next) {
        this->val = val;
        this->next = next;
        if (next != NULL) {
            // Keep track of `nextMin`
            this->nextMin = (next->next != NULL) ? 
                            min(next->val, next->nextMin) : next->val;
        }
    }
};

class MinStack {
public:
    /** initialize your data structure here. */
    Node* head;
    MinStack(): head( NULL ) {}
    
    void push(int x) {
        head = new Node(x, head);
    }
    
    void pop() {
	    // If there is nothing to pop, will get sefault since `head` will be NULL.	
		Node* nextNode = head->next;
		delete head;
		head = nextNode;
    }
    
    int top() {
        // If stack is empty, will get segfault since `head` is NULL.
        return head->val;
    }
    
    int getMin() {
        return (head->next == NULL) ? 
            head->val : min(head->val, head->nextMin);
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */
