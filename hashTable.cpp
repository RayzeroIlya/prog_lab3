#include <iostream>
#include <string>
#include <algorithm> 


class SinglyLinkedList {
    private:
        struct Node {
            std::string key; 
            int value;         
            Node* next;
        };
        Node* head;
        Node* tail;
        size_t size;
    
    public:
        SinglyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    
        // Добавление элемента в конец списка
        void push_back(const std::string& key, int value) {
            Node* newNode = new Node{key, value, nullptr};
            if (tail == nullptr) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
            size++;
        }
    
        // Удаление элемента по ключу
        void remove(const std::string& key) {
            if (head == nullptr) return;
    
            if (head->key == key) {
                Node* temp = head;
                head = head->next;
                if (head == nullptr) {
                    tail = nullptr;
                }
                delete temp;
                size--;
                return;
            }
    
            Node* current = head;
            while (current->next != nullptr && current->next->key != key) {
                current = current->next;
            }
    
            if (current->next != nullptr) {
                Node* temp = current->next;
                current->next = current->next->next;
                if (current->next == nullptr) {
                    tail = current;
                }
                delete temp;
                size--;
            }
        }
    
        // Получение значения элемента по ключу
        int get(const std::string& key) const {
            Node* current = head;
            while (current != nullptr) {
                if (current->key == key) {
                    return current->value;
                }
                current = current->next;
            }
            throw std::out_of_range("Key not found");
        }
    
        bool isEmpty() const {
            return size == 0;
        }
    
        size_t getSize() const {
            return size;
        }
    
    
        
        void print() const {
            Node* current = head;
            while (current != nullptr) {
                std::cout << "(" << current->key << ", " << current->value << ") ";
                current = current->next;
            }
            std::cout << std::endl;
        }
    
        ~SinglyLinkedList() {
            Node* current = head;
            while (current != nullptr) {
                Node* next = current->next;
                delete current;
                current = next;
            }
        }
    };
    
    

    class HashTable {
    private:
        size_t capacity;
        SinglyLinkedList* table; // Массив списков (цепочки)
    
        // Хеш-функция
        size_t hashFunction(const std::string& key) const {
            size_t hash = 0;
            for (char c : key) {
                hash = (hash * 31) + c;
            }
            return hash % capacity;
        }
    
    public:
   
        HashTable(size_t capacity) : capacity(capacity) {
            table = new SinglyLinkedList[capacity];
        }
    
    
        ~HashTable() {
            delete[] table;
        }
    
        // Добавление элемента (ключ-значение)
        void insert(const std::string& key, int value) {
            size_t index = hashFunction(key);
            table[index].push_back(key, value);
        }
    
        // Получение значения элемента по ключу
        int get(const std::string& key) const {
            size_t index = hashFunction(key);
            return table[index].get(key);
        }
    
        // Удаление элемента по ключу
        void remove(const std::string& key) {
            size_t index = hashFunction(key);
            table[index].remove(key);
        }
    
        
        void print() const {
            for (size_t i = 0; i < capacity; ++i) {
                std::cout << "Bucket " << i << ": ";
                table[i].print();
            }
        }
    };  