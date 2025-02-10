#include <iostream>
#include <stdexcept>

class DoublyLinkedList {
    private:
        struct Node {
            int data;
            Node* next;
            Node* prev;
        };
        Node* head;
        Node* tail;
    
    public:
        DoublyLinkedList() : head(nullptr), tail(nullptr) {}
    
        // Добавление элемента в голову
        void push_front(int value) {
            Node* newNode = new Node{value, head, nullptr};
            if (head == nullptr) {
                head = newNode;
                tail = newNode;
            } else {
                head->prev = newNode;
                newNode->next = head;
                head = newNode;
            }
        }
    
        // Добавление элемента в хвост
        void push_back(int value) {
            Node* newNode = new Node{value, nullptr, tail};
            if (tail == nullptr) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        }
    
        // Удаление элемента с головы
        void pop_front() {
            if (head == nullptr) return;
    
            Node* temp = head;
            head = head->next;
    
            if (head != nullptr)
                head->prev = nullptr;
            else
                tail = nullptr; //Список стал пустым
    
            delete temp;
        }
    
        // Удаление элемента с хвоста
        void pop_back() {
            if (tail == nullptr) return;
    
            Node* temp = tail;
            tail = tail->prev;
    
            if (tail != nullptr)
                tail->next = nullptr;
            else
                head = nullptr; //Список стал пустым
    
            delete temp;
    
        }
    
        // Удаление элемента по значению (удаляет первое вхождение)
        void remove(int value) {
            if (head == nullptr) return;
    
            Node* current = head;
            while (current != nullptr && current->data != value) {
                current = current->next;
            }
    
            if (current != nullptr) {
                if (current->prev != nullptr) {
                    current->prev->next = current->next;
                } else {
                    head = current->next;
                }
    
                if (current->next != nullptr) {
                    current->next->prev = current->prev;
                } else {
                    tail = current->prev;
                }
    
                delete current;
            }
        }
    
        // Поиск элемента по значению (возвращает true, если найден)
        bool contains(int value) const {
            Node* current = head;
            while (current != nullptr) {
                if (current->data == value) {
                    return true;
                }
                current = current->next;
            }
            return false;
        }
    
        // Чтение (вывод на экран)
        void print() const {
            Node* current = head;
            while (current != nullptr) {
                std::cout << current->data << " ";
                current = current->next;
            }
            std::cout << std::endl;
        }
    
        ~DoublyLinkedList() {
            while (head != nullptr) {
                pop_front();
            }
        }
    };