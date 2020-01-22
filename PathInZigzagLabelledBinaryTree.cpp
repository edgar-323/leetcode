/*
In an infinite binary tree where every node has two children, the nodes are labelled in row order.
In the odd numbered rows (ie., the first, third, fifth,...), the labelling is left to right, while in the even numbered rows (second, fourth, sixth,...), the labelling is right to left.
Given the label of a node in this tree, return the labels in the path from the root of the tree to the node with that label.

Example 1:
Input: label = 14
Output: [1,3,4,14]

Example 2:
Input: label = 26
Output: [1,2,6,10,26]

Constraints:
1 <= label <= 10^6
*/

class Solution {
private:
	std::vector<int> solution1(int label) {
        /* Time-Complexity:     O(log(label))
         * Space-Complexity:    O(1)
         */
		/*
		Intuition
		If the tree is numbered left-to-right (not zigzag), the parent's label can be always determined as label / 2. For zigzag, we need to "invert" the parent label.
		Solution
		Determine the tree level where our value is located. The maximum label in the level is 1 << level - 1, and minimum is 1 << (level - 1). We will use this fact to "invert" the parent label.
		*/
        // Determine level
	    int level = 0;	
    	while (1 << level <= label) ++level;
        // Our answer will be of length level
	  	vector<int> res(level);
        //  
		for(; label >= 1; label /= 2, --level) {
            // res[level-1] = current_label
			res[level - 1] = label;
            // Invert parent
			label = (1 << level) - 1 - label + (1 << (level - 1));
            
		}
		return res;   
	}
public:
    vector<int> pathInZigZagTree(int label) {
		return solution1(label);        
    }
};
