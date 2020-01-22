/*
Design and implement a data structure for Least Frequently Used (LFU) cache.
It should support the following operations: get and put.

get(key) - 
Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.

put(key, value) - 
Set or insert the value if the key is not already present.
When the cache reaches its capacity, it should invalidate the least frequently used item before inserting a new item.
For the purpose of this problem, when there is a tie (i.e., two or more keys that have the same frequency), the least recently used key would be evicted.

Note that the number of times an item is used is the number of calls to the get and put functions for that item since it was inserted.
This number is set to zero when the item is removed.

Follow up:
Could you do both operations in O(1) time complexity?

Example:
LFUCache cache = new LFUCache( 2 ); // capacity
cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.get(3);       // returns 3.
cache.put(4, 4);    // evicts key 1.
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4
*/

class Node {
public:
    int key;
    int val;
    Node* prev;
    Node* next;

    Node(const int _key, const int _val, Node* _prev, Node* _next):
        key(_key), val(_val), prev(_prev), next(_next) {}
};

class FrequencyNode {
private:
    Node* head;
    Node* tail;
    std::unordered_map<int,Node*> node_map;
public:
    FrequencyNode* prev;
    FrequencyNode* next;
    int frequency;

    FrequencyNode(const int _frequency, FrequencyNode* _prev, FrequencyNode* _next):
        frequency(_frequency), head(nullptr), tail(nullptr), prev(_prev), next(_next) {}

    bool empty() const {
        return node_map.empty();
    }

    int pop() {
        // Will remove head since it is the oldest (key,val) in this node 
        const auto key = head->key;
        auto old_head = head;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete old_head;
        node_map.erase(key);
        return key;
    }

    void push(Node* node) {
        node->next = node->prev = nullptr;
        if (head == nullptr) {
            head = tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
        node_map[node->key] = node;
    }

    Node* remove(const int key) {
        auto node = node_map[key];
        if (node == head and node == tail) {
            head = tail = nullptr;
        } else if (node == head) {
            head = head->next;
            head->prev = nullptr;
        } else if (node == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            auto next = node->next;
            auto prev = node->prev;
            next->prev = prev;
            prev->next = next;
        }
        node_map.erase(node->key);
        node->prev = node->next = nullptr;
        return node;
    }

    void set_value(const int key, const int val) {
        auto node = remove(key);
        node->val = val;
        push(node);
    }

    Node* top() {
        return tail;
    }
};

class LFUCache {
private:
    FrequencyNode* head;
    FrequencyNode* tail;
    std::unordered_map<int,FrequencyNode*> freq_map;
    int capacity;

    bool in_cache(const int key) {
        return freq_map.count(key);
    }

    bool reached_capacity() {
        return freq_map.size() == capacity;
    }

    void make_lru_eviction() {
        freq_map.erase(head->pop());
        if (head->empty()) {
            auto node = head;
            if (head == tail) {
                head = tail = nullptr;
            } else {
                head = head->next;
                head->prev = nullptr;
            }
            delete node;
        }
    }

    Node* get_node(const int key) {
      	auto node = freq_map[key];
        if (not node->next or node->next->frequency != node->frequency + 1) {
            auto new_node = new FrequencyNode(node->frequency + 1, node, node->next);
            if (tail == node) {
                tail = new_node;
            } else {
                node->next->prev = new_node;
            }
            node->next = new_node;
        }
        auto next = node->next;
        next->push(node->remove(key));
        freq_map[key] = next;
        if (node->empty()) {
            if (node == head) {
                head = next;
                head->prev = nullptr;
            } else {
                auto prev = node->prev;
                next->prev = prev;
                prev->next = next;
            }
            delete node;
        }
        return next->top();
    }
public:
    LFUCache(int capacity) {
        this->capacity = capacity;
        head = tail = nullptr;
    }
    
    int get(int key) { 
        if (not capacity or not in_cache(key)) {
            return -1;
        }
        return get_node(key)->val;
    }
    
    void put(int key, int value) {
        if (not capacity) { 
            return;
        }
        if (in_cache(key)) {
            get_node(key)->val = value;
            return;
        }
        if (reached_capacity()) {
            make_lru_eviction();
        }
        if (not head) {
            head = tail = new FrequencyNode(1, nullptr, nullptr);
        } else if (head->frequency != 1) {
            head = new FrequencyNode(1, nullptr, head);
            head->next->prev = head;
        }
        head->push(new Node(key, value, nullptr, nullptr));
        freq_map[key] = head;
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
