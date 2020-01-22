/*
Implement FreqStack, a class which simulates the operation of a stack-like data structure.
FreqStack has two functions:
    1) push(int x), which pushes an integer x onto the stack.
    2) pop(), which removes and returns the most frequent element in the stack.
If there is a tie for most frequent element, the element closest to the top of the stack is removed and returned.

Example 1:
Input: 
["FreqStack","push","push","push","push","push","push","pop","pop","pop","pop"],
[[],[5],[7],[5],[7],[4],[5],[],[],[],[]]
Output: [null,null,null,null,null,null,null,5,7,5,4]
Explanation:
After making six .push operations, the stack is [5,7,5,7,4,5] from bottom to top.  Then:
pop() -> returns 5, as 5 is the most frequent.
The stack becomes [5,7,5,7,4].
pop() -> returns 7, as 5 and 7 is the most frequent, but 7 is closest to the top.
The stack becomes [5,7,5,4].
pop() -> returns 5.
The stack becomes [5,7,4].
pop() -> returns 4.
The stack becomes [5,7].

Note:
Calls to FreqStack.push(int x) will be such that 0 <= x <= 10^9.
It is guaranteed that FreqStack.pop() won't be called if the stack has zero elements.
The total number of FreqStack.push calls will not exceed 10000 in a single test case.
The total number of FreqStack.pop calls will not exceed 10000 in a single test case.
The total number of FreqStack.push and FreqStack.pop calls will not exceed 150000 across all test cases.
*/

// Thoughts:
// We need to keep track of frequencies.
// So maybe we can keep frequencies in a hash-map.
// But we also need to know which frequencies are maximal (in fact this is the only thing to know)
// We should have a field (max_fruency)
// Also a list of values (max_frequencies)
// If it wasn't for the fact that we must return any max-frequency value, we'd ve done.
// However, we must return the max-frequency closer to the top.
// One option is to maintain a linked-list of these values and to have have a hash-map of a certain value
// point to a list of indices where the value exists.
// Why would i bring up indices?
// I am proposing to assign an index to each new linked-list node.
// We also maintain a min-index.
// The first index will be 0 and will increase towards infinity.
// Since we remove some nodes the list will fragment but the diffs towards the top will be maintained when
// doing comparisons.
// Say x has highest frequency, and suppose x is cloest to the top, then we decrement frequency of x and 
// we pop the lowest index of x.
// However, what if frequencies change?
// I believe it to be necessary to maintain a frequency map.
// I.e., say freq[x] = f. Them freq_pool[f] = list of values whose frequencies is f.
class Node {
private:

public:
    int val;
    Node* next;
    Node* prev;
    Node(int _val, Node* prev, Node* _next = NULL): val(_val), next(_next) {}
};

class FreqStack {
private:
public:
    FreqStack() {
        
    }
    
    void push(int x) {
        
    }
    
    int pop() {
        
    }
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 */
