#include <functional>
//implementacion hash chaining
template <typename K, typename V>
struct Node {
    K key;
    V value;
    Node* next;

    Node(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
};

template <typename K, typename V>
class HashTable {
    Node<K,V>** table;
    int size;
    int count;
    int hash(const K& key) {
        return std::hash<K>{}(key) % size;
    }
    void resize() {
        int newCapacity = size * 2;
        Node<K, V>** newTable = new Node<K, V>*[newCapacity];

        for (int i = 0; i < newCapacity; ++i) {
            newTable[i] = nullptr;
        }

        for (int i = 0; i < size; ++i) {
            Node<K, V>* current = table[i];
            while (current) {
                Node<K, V>* nextNode = current->next;
                int newIdx = std::hash<K>{}(current->key) % newCapacity;
                current->next = newTable[newIdx];
                newTable[newIdx] = current;

                current = nextNode;
            }
        }

        delete[] table;

        table = newTable;
        size = newCapacity;
    }
public:
    HashTable(int size = 10) : size(size), count(0) {
        table = new Node<K, V>*[size];
        for (int i = 0; i < size; ++i) {
            table[i] = nullptr;
        }
    }

    ~HashTable() {
        for (int i = 0; i < size; ++i) {
            Node<K, V>* current = table[i];
            while (current != nullptr) {
                Node<K, V>* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
    }

    void insert(const K& key, const V& value) {
        if (static_cast<double>(count) / size >= 0.75) {
            resize();
        }
        int index = hash(key);
        Node<K, V>* current = table[index];

        while (current != nullptr) {
            if (current->key == key) {
                current->value = value;
                return;
            }
            current = current->next;
        }

        Node<K, V>* newNode = new Node<K, V>(key, value);
        newNode->next = table[index];
        table[index] = newNode;
        count++;
    }

    V* search(const K& key) {
        int idx = hash(key);
        Node<K, V>* current = table[idx];
        while (current!=nullptr) {
            if (current->key == key) {
                return &current->value;
            }
            current = current->next;
        }
        return nullptr;
    }

    void remove(const K& key) {
        int index = hash(key);
        Node<K, V>* current = table[index];
        Node<K, V>* prev = nullptr;

        while (current!=nullptr && current->key != key) {
            prev = current;
            current = current->next;
        }

        if (current!=nullptr) {
            if (prev!=nullptr) {
                prev->next = current->next;
            } else {
                table[index] = current->next;
            }
            delete current;
            count--;
        }
    }
    bool empty() {
        return count == 0;
    }
};
