/*
Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and put.
get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.
The cache is initialized with a positive capacity.

Follow up:
Could you do both operations in O(1) time complexity?

Example:

LRUCache cache = new LRUCache( 2 );

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.put(4, 4);    // evicts key 1
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
    
    Node(int key, int value, Node* prevNode, Node* nextNode) {
        this->key = key;
        val = value;
        prev = prevNode;
        next = nextNode;
    }
};

class LRUCache {
private:
    int capacity;
    std::unordered_map<int, Node*> map;
    Node* head;
    Node* tail;
    
    void makeHead(Node* node) {
        if (node != head) {
            tail = (tail != node) ? tail :
                ((node->next != NULL) ? 
                 node->next : node->prev);
            node->prev->next = node->next;
            if (node->next != NULL) {
                node->next->prev = node->prev;
            }
            node->prev = NULL;
            head->prev = node;
            node->next = head;
            head = node;
        }
    }
    
    void evictTail(void) {
        map.erase(tail->key);
        Node* temp = tail;
        tail = tail->prev;
        if (tail == NULL) {
            head = NULL;
        } else {
            tail->next = NULL;
        }
        delete temp;
    }
    
    void addNewKey(int key, int val) {
        Node* newNode = new Node(key, val, NULL, head);
        if (tail == NULL) {
            tail = newNode;
        } else {
            head->prev = newNode;
        }
        head = newNode;
        map.emplace(key, newNode);
    }
    
    bool contains(int key) {
        return map.count(key);
    }
    
    bool reachedCapacity() {
        return map.size() >= capacity;
    }
    
    void checkCapacity() {
        if (reachedCapacity()) {
            evictTail();
        }
    }
    
    int getValue(int key) {
        Node* node = map.at(key);
        int val = node->val;
        makeHead(node);
        return val;
    }
    
    void setValue(int key, int newValue) {
        Node* node = map.at(key);
        node->val = newValue;
        makeHead(node);
    }
    
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        head = NULL;
        tail = NULL;
    }
    
    int get(int key) {
        return contains(key) ? getValue(key) : -1;
    }
        
    void put(int key, int value) {
        if (capacity <= 0) {
            return;
        } else if (contains(key)) {
            setValue(key, value);
        } else {
            checkCapacity();
            addNewKey(key, value);
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */
