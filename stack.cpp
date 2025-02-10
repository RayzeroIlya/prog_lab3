#include "singleLinkedList.cpp"

class Stack {
    private:
        SinglyLinkedList list; 
    
    public:
        // Добавление элемента (push)
        void push(int value) {
            list.push_front(value); 
        }
    
        // Удаление элемента (pop)
        void pop() {
            list.pop_front(); 
        }
    
        
        void print() const {
            list.print();
        }
    };