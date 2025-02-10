#include "singleLinkedList.cpp"



class Queue {
    private:
        SinglyLinkedList list; 
    
    public:
        // Добавление элемента (push)
        void push(int value) {
            list.push_back(value); 
        }
    
        // Удаление элемента (pop)
        void pop() {
            list.pop_front(); 
        }
    

        void print() const {
            list.print();
        }
    };