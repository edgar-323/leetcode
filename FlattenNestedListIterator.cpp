/*
Given a nested list of integers, implement an iterator to flatten it.

Each element is either an integer, or a list -- whose elements may also be integers or other lists.

Example 1:

Input: [[1,1],2,[1,1]]
Output: [1,1,2,1,1]
Explanation: By calling next repeatedly until hasNext returns false, 
             the order of elements returned by next should be: [1,1,2,1,1].
Example 2:

Input: [1,[4,[6]]]
Output: [1,4,6]
Explanation: By calling next repeatedly until hasNext returns false, 
             the order of elements returned by next should be: [1,4,6].
*/
/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */


class NestedIterator {
private:
    std::stack<NestedInteger> stack;

    void push_list(std::vector<NestedInteger>& nestedList) {
        auto end = nestedList.rend();
		for (auto rit = nestedList.rbegin(); rit != end; ++rit) {
	        stack.push( *rit );	
		}
    }

    void generate_next() {
        /* We will maintain the invariant that, while it is 
         * nonempty, the TOP of the stack will always hold 
         * a NestedInteger that is NOT a list.
         * */
        while ( hasNext() ) {
            NestedInteger next_elem = stack.top();
            if (next_elem.isInteger()) {
                break;
            }
            stack.pop();
            push_list( next_elem.getList() );
        }
    }

public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        push_list( nestedList );
        generate_next();
    }
    
    int next() {
        int next_elem = stack.top().getInteger(); 
        stack.pop();
        generate_next();

        return next_elem;
    }
    
    bool hasNext() {
        return !stack.empty();
    }
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
