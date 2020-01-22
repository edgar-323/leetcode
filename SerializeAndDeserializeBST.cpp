/*
Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary search tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary search tree can be serialized to a string and this string can be deserialized to the original tree structure.

The encoded string should be as compact as possible.

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
    int toDigit(const char c) {
        return c - '0';
    }

    bool isDigit(const char c) {
        return '0' <= c and c <= '9';
    }

    bool hasInt(const std::string& data, const int i) {
        return i < data.size();
    }

    int getNextInt(const std::string& data, int& start, const bool advance = false) {
        // Assumes an integer begins at data[start]
        // start + increments is the new position where either another integer starts in the data
        // or the end of data
        int i = start;
        int sign = 1;   
        if (data[i] == '-') {
            sign = -1;
            ++i;
        }
        int end = i+1;
        int powTen = 1;
        while (end < data.size() and isDigit(data[end])) {
            powTen *= 10;
            ++end;
        }
        int val = 0;
        for (; i < end; ++i, powTen /= 10) {
            val += toDigit(data[i]) * powTen;
        }
        i += (i < data.size());
        
        if (advance) {
            start = i;
        }
        
        return sign * val;
    }

    std::string preOrderEncode(TreeNode* node) {
        if (not node) {
            return "";
        }
        auto encoding = std::to_string(node->val);
        const auto left = preOrderEncode(node->left);
        const auto right = preOrderEncode(node->right);

        if (not left.empty()) {
            encoding += "," + left;
        }
        if (not right.empty()) {
            encoding += "," + right;
        }

        return encoding; 
    }

    TreeNode* preOrderDecode(const std::string& data, int& i, const int max_val) {
        if (not hasInt(data, i)) {
            return NULL;
        }
        
        TreeNode* node = new TreeNode(getNextInt(data, i, true));

        if (not hasInt(data, i)) {
            return node;
        }
        
        int next_val = getNextInt(data, i);
        
        if (next_val < node->val) {
            node->left = preOrderDecode(data, i, node->val); 
            if (not hasInt(data, i)) {
                return node;
            }
            next_val = getNextInt(data, i);
        }
        if (next_val < max_val) {
            node->right = preOrderDecode(data, i, max_val);
        }

        return node;
    }
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        // PreOrder Encoding  
        return preOrderEncode(root);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        // PreOrder Decoding
        int i = 0;
        return preOrderDecode(data, i, INT_MAX);  
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
