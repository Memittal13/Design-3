//Time O(1)
//Space O(n)
//Leetcode : yes
//issue seen: none

class LRUCache {
public:
    int capacity;
    class ListNode {
    public:
        int key;
        int val;
        ListNode* prev;
        ListNode* next;

        ListNode() {
            key = -1;
            val = -1;
            next = NULL;
            prev = NULL;
        }
    };
    unordered_map<int, ListNode*> mp;
    ListNode* head;
    ListNode* tail;

    void addToHead(ListNode* curr) {
        curr->next = head->next;
        head->next->prev = curr;
        head->next = curr;
        curr->prev = head;
    }
    void removeNode(ListNode* curr) {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
    }

    LRUCache(int capacity) {
        this->capacity = capacity;
        head = new ListNode();
        tail = new ListNode();
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if (mp.find(key) != mp.end()) {
            ListNode* node = mp[key];
            removeNode(node);
            addToHead(node);
            return node->val;
        }
        return -1;
    }

    void put(int key, int value) {
        if (mp.find(key) != mp.end()) {
            removeNode(mp[key]);
            addToHead(mp[key]);
            mp[key]->val = value;
        } else {
            ListNode* newNode = new ListNode();
            newNode->val = value;
            newNode->key = key;
            if (mp.size() == capacity) {
                mp.erase(tail->prev->key);
                removeNode(tail->prev);
            }
            addToHead(newNode);
            mp[key] = newNode;
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
