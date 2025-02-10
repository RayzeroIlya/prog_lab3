#include <iostream>
#include <stdexcept>  


class Array {
private:
    int* data;         
    size_t current_size; 
    size_t max_size;     

public:

    Array(size_t size) : max_size(size), current_size(0) {
        data = new int[max_size]; 
        if (data == nullptr) {
            throw std::bad_alloc(); // Выбросить исключение, если не удалось выделить память
        }
    }


    ~Array() {
        delete[] data; // Освобождение выделенной памяти
        data = nullptr; //  Предотвращение висячих указателей
    }

    // Конструктор копирования
    Array(const Array& other) : max_size(other.max_size), current_size(other.current_size) {
        data = new int[max_size];
        if (data == nullptr) {
            throw std::bad_alloc();
        }
        for (size_t i = 0; i < current_size; ++i) {
            data[i] = other.data[i];
        }
    }

    // Оператор присваивания копированием
    Array& operator=(const Array& other) {
        if (this != &other) { // Проверка на самоприсваивание
            // 1. Освобождаем старую память
            delete[] data;

            // 2. Выделяем новую память
            max_size = other.max_size;
            current_size = other.current_size;
            data = new int[max_size];
            if (data == nullptr) {
                throw std::bad_alloc();
            }

            // 3. Копируем данные
            for (size_t i = 0; i < current_size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }


    // Конструктор перемещения
    Array(Array&& other) : data(other.data), current_size(other.current_size), max_size(other.max_size) {
        other.data = nullptr;
        other.current_size = 0;
        other.max_size = 0;
    }

    // Оператор присваивания перемещением
    Array& operator=(Array&& other) {
        if (this != &other) {
            delete[] data;

            data = other.data;
            current_size = other.current_size;
            max_size = other.max_size;

            other.data = nullptr;
            other.current_size = 0;
            other.max_size = 0;
        }
        return *this;
    }


    void push_back(int value) {
        if (current_size == max_size) {
            resize(max_size * 2); 
        }
        data[current_size] = value;
        current_size++;
    }

    void insert(size_t index, int value) {
        if (index > current_size) {
            throw std::out_of_range("Index out of range");
        }

        if (current_size == max_size) {
            resize(max_size * 2);
        }

        // Сдвигаем элементы вправо от позиции вставки
        for (size_t i = current_size; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        current_size++;
    }


    int get(size_t index) const {
        if (index >= current_size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Удаление элемента по индексу
    void remove(size_t index) {
        if (index >= current_size) {
            throw std::out_of_range("Index out of range");
        }
        // Сдвигаем элементы влево после позиции удаления
        for (size_t i = index; i < current_size - 1; ++i) {
            data[i] = data[i + 1];
        }
        current_size--;
    }

    // Замена элемента по индексу
    void set(size_t index, int value) {
        if (index >= current_size) {
            throw std::out_of_range("Index out of range");
        }
        data[index] = value;
    }


    size_t size() const {
        return current_size;
    }

    void print() const {
        for (size_t i = 0; i < current_size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

private:
    // Вспомогательная функция для изменения размера массива
    void resize(size_t new_size) {
        if (new_size < current_size) {
            throw std::invalid_argument("New size cannot be smaller than current size.");
        }

        int* new_data = new int[new_size];
        if (new_data == nullptr) {
            throw std::bad_alloc();
        }

        // Копируем старые данные в новый массив
        for (size_t i = 0; i < current_size; ++i) {
            new_data[i] = data[i];
        }


        delete[] data;

        // Обновляем указатель и размер
        data = new_data;
        max_size = new_size;
    }
};