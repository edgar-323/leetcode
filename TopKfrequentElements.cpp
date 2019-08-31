/*
Given a non-empty array of integers, return the k most frequent elements.

Example 1:

Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]
Example 2:

Input: nums = [1], k = 1
Output: [1]
Note:

You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
*/

class Node {
private:
    int key;
    int val;
    
public: 
    Node(int key, int val) {
        this->key = key;
        this->val = val;
    }
    
    int getKey() {
        int k = this->key;
        return k;
    }
    
    int getVal() {
        int k = this->val;
        return k;
    }
    
    bool operator < (const Node& other) const {
        return this->val > other.val;
    }
};

class Solution {
private:
    std::vector<int> solution1(std::vector<int>& nums, int k) {
        /*
        Time-Complexity:    
            ==> N + N*lg(K) + K*lg(K)
            ==> (N+1)*lg(K) + K*lg(K)
            ==> (N+K+1)*lg(K)
            ==> O((N+K+1)*lg(K))
            ==> O(2*N*lg(K))
            ==> O(N*lg(K))
        Space-Complexity:
            ==> N + K
            ==> O(N+K)
            ==> O(2*N)
            ==> O(N)
        */
        
        const int N = nums.size();
        std::unordered_map<int, int> frequencies;
        std::unordered_map<int, int>::iterator it;
        for (int num : nums) {
            it = frequencies.find(num);
            if (it != frequencies.end()) {
                ++(it->second);
            } else {
                frequencies.emplace(num, 1);
            }
        }
        
        std::priority_queue<Node> PQ;
        for (auto const& [key, val] : frequencies) {
            PQ.push(Node(key, val));
            if (PQ.size() > k) {
                PQ.pop();
            }
        }
        
        std::vector<int> mostFrequent = std::vector<int>(k, 0);
        for (int i = 0; i < k; ++i, PQ.pop()) {
            Node node = PQ.top();
            mostFrequent[i] = node.getKey();
        }
        
        return mostFrequent;
    }
    
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        return solution1(nums, k);
    }
};
