#include <iostream>
#include <stdexcept>

class SinglyLinkedList {
    private:
        struct Node {
            int data;
            Node* next;
        };
        Node* head;
        Node* tail;
    
    public:
        SinglyLinkedList() : head(nullptr), tail(nullptr) {}
    
        // Добавление элемента в голову
        void push_front(int value) {
            Node* newNode = new Node{value, head};
            head = newNode;
            if (tail == nullptr) {
                tail = newNode;
            }
        }
    
        // Добавление элемента в хвост
        void push_back(int value) {
            Node* newNode = new Node{value, nullptr};
            if (tail == nullptr) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
        }
    
        // Удаление элемента с головы
        void pop_front() {
            if (head == nullptr) {
                return;  
            }
            Node* temp = head;
            head = head->next;
            delete temp;
            if (head == nullptr) {
                tail = nullptr; 
            }
        }
    
        // Удаление элемента с хвоста (требует прохода по списку)
        void pop_back() {
            if (head == nullptr) {
                return; // Или выбросить исключение
            }
            if (head == tail) {
                delete head;
                head = nullptr;
                tail = nullptr;
                return;
            }
            Node* current = head;
            while (current->next != tail) {
                current = current->next;
            }
            delete tail;
            tail = current;
            tail->next = nullptr;
        }
    
        // Удаление элемента по значению (удаляет первое вхождение)
        void remove(int value) {
            if (head == nullptr) return;
    
            if (head->data == value) {
                pop_front();
                return;
            }
    
            Node* current = head;
            while (current->next != nullptr && current->next->data != value) {
                current = current->next;
            }
    
            if (current->next != nullptr) {
                Node* temp = current->next;
                current->next = current->next->next;
    
                if(temp == tail)
                   tail = current;
    
                delete temp;
    
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
    

        void print() const {
            Node* current = head;
            while (current != nullptr) {
                std::cout << current->data << " ";
                current = current->next;
            }
            std::cout << std::endl;
        }
    
        ~SinglyLinkedList() {
            while (head != nullptr) {
                pop_front();
            }
        }
    };