/*
Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.
Design an algorithm to serialize and deserialize a binary tree. 
There is no restriction on how your serialization/deserialization algorithm should work. 
You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

Example: 
You may serialize the following tree:
    1
   / \
  2   3
     / \
    4   5
as "[1,2,3,null,null,4,5]"

Clarification: The above format is the same as how LeetCode serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.
Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
private:
    int toDigit(char c) {
        return (c - '0');
    }
    
    bool isDigit(char c) {
        return (c >= '0') && (c <= '9');
    }
    
    int toInt(std::string& encoded, int& i) {
        int sign = 1;
        if (encoded[i] == '-') {
            sign = -1;
            i++;
        }
        int end = i+1;
        int powTen = 1;
        while (isDigit(encoded[end])) {
            powTen *= 10;
            ++end;
        }
        int val = 0;
        for (; i < end; ++i, powTen /= 10) {
            val += toDigit(encoded[i]) * powTen;
        } 
        ++i;
        return sign * val;
    }
    
    void preOrderEncode(TreeNode* node, std::string& encoded) {
        if (node == NULL) {
            encoded += "$,";
        } else {
            encoded += (std::to_string(node->val) + ",");
            preOrderEncode(node->left, encoded);
            preOrderEncode(node->right, encoded);
        }
    }
    
    TreeNode* preOrderDecode(std::string encoded, int& i) {
        if (encoded[i] == '$') {
            i += 2;
            return NULL;
        }
        TreeNode* node = new TreeNode(toInt(encoded, i));
        node->left = preOrderDecode(encoded, i);
        node->right = preOrderDecode(encoded, i);
        return node;
    }
    
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        std::string encoded = "";
        preOrderEncode(root, encoded);
        return encoded;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int i = 0;
        return preOrderDecode(data, i);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
