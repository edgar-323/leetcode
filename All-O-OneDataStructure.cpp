/*
Implement a data structure supporting the following operations:

Inc(Key) - Inserts a new key with value 1. Or increments an existing key by 1. Key is guaranteed to be a non-empty string.
Dec(Key) - If Key's value is 1, remove it from the data structure. Otherwise decrements an existing key by 1. If the key does not exist, this function does nothing. Key is guaranteed to be a non-empty string.
GetMaxKey() - Returns one of the keys with maximal value. If no element exists, return an empty string "".
GetMinKey() - Returns one of the keys with minimal value. If no element exists, return an empty string "".
Challenge: Perform all these in O(1) time complexity.
*/
class Node {
public:
    int freq_val;
    std::unordered_set<std::string> set;
    Node* prev;
    Node* next;

    Node(int _freq_val, Node* _prev, Node* _next):
        freq_val(_freq_val), prev(_prev), next(_next)
    {}

    void set_prev(Node* prev) {
        this->prev = prev;
    }

    void set_next(Node* next) {
        this->next = next;
    }

    bool empty() const {
        return set.empty();
    }

    void remove(const std::string& key) {
        set.erase(key);
    }

    void add(const std::string& key) {
        set.insert(key);
    }

    bool has_freq(const int val) {
        return freq_val == val;
    }
    
    bool has_next() const {
        return next;
    }

    bool has_prev() const {
        return prev;
    }

    std::string get_element() {
        return *set.begin();
    }
};

class AllOne {
private:
    std::unordered_map<std::string,int> freq;
    std::unordered_map<int,Node*> freq_node;
    Node* head; // Minimum Frequency Values
    Node* tail; // Maximum Frequency Values
public:
    /** Initialize your data structure here. */
    AllOne() {
        head = tail = NULL; 
    }
    
    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key) {
        const auto prev_freq = freq[key]++;
        if (prev_freq) {
            auto prev_node = freq_node[prev_freq];
            if (not prev_node->has_next() or not prev_node->next->has_freq(prev_freq+1)) {
                auto new_node = new Node(prev_freq+1, prev_node, prev_node->next);
                if (prev_node->has_next()) {
                    prev_node->next->set_prev(new_node);
                }
                prev_node->set_next(new_node);
                if (prev_node == tail) {
                    tail = new_node;
                }
                freq_node[prev_freq+1] = new_node;
            }
            auto next_node = freq_node[prev_freq+1];
            next_node->add(key);
            prev_node->remove(key);
            if (prev_node->empty()) {
                if (prev_node->has_prev()) {
                    prev_node->prev->set_next(next_node);
                } else {
                    head = next_node;
                }
                next_node->set_prev(prev_node->prev); 
                freq_node.erase(prev_freq);
                delete prev_node;
            }
        } else {
            if (not head) {
                head = tail = new Node(1, NULL, NULL);
            } else if (not head->has_freq(1)) {
                head = new Node(1, NULL, head);
                head->next->set_prev(head);
            }
            freq_node[1] = head;
            head->add(key);
        }
    }
    
    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key) {
        if (not freq.count(key)) {
            return;
        }
        const auto next_freq = freq[key]--;
        auto next_node = freq_node[next_freq];
        if (not freq[key]) {
            freq.erase(key);
        }    
        if (next_freq == 1) {
            next_node->remove(key);
            if (next_node->empty()) {
                if (next_node->has_next()) {
                    head = next_node->next;
                    head->set_prev(NULL);
                } else {
                    head = tail = NULL;
                }
                freq_node.erase(1);
                delete next_node;
            }
            return;
        }
        
        if (not next_node->has_prev() or not next_node->prev->has_freq(next_freq-1)) {
            auto new_node = new Node(next_freq-1, next_node->prev, next_node);
            if (next_node->has_prev()) {
                next_node->prev->set_next(new_node);
            }
            next_node->set_prev(new_node);     
            if (head == next_node) {
                head = new_node;
            }
            freq_node[next_freq-1] = new_node;
        }
        auto prev_node = freq_node[next_freq-1];
        prev_node->add(key);
        next_node->remove(key);
        if (next_node->empty()) {
            if (next_node->has_next()) {
                next_node->next->set_prev(prev_node);
            } else {
                tail = prev_node;
            }
            prev_node->set_next(next_node->next);
            freq_node.erase(next_freq);
            delete next_node;
        }
    }
    
    /** Returns one of the keys with maximal value. */
    string getMaxKey() {
        return tail ? tail->get_element() : "";
    }
    
    /** Returns one of the keys with Minimal value. */
    string getMinKey() {
        return head ? head->get_element() : "";
    }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */

