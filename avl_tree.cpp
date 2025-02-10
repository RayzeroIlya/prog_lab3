#include <iostream>
#include <string>
#include <algorithm>    

class AVLTree {
    private:
        struct Node {
            int key;
            int height;
            Node* left;
            Node* right;
    
            Node(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
        };
    
        Node* root;
    
        // Получение высоты узла
        int height(Node* node) const {
            return (node == nullptr) ? 0 : node->height;
        }
    
        // Обновление высоты узла
        void updateHeight(Node* node) {
            node->height = 1 + std::max(height(node->left), height(node->right));
        }
    
        // Получение фактора баланса узла
        int getBalance(Node* node) const {
            return (node == nullptr) ? 0 : height(node->left) - height(node->right);
        }
    
        // Правый поворот
        Node* rightRotate(Node* y) {
            Node* x = y->left;
            Node* T2 = x->right;
    
            // Поворот
            x->right = y;
            y->left = T2;
    
            // Обновление высот
            updateHeight(y);
            updateHeight(x);
    
            // Возвращаем новый корень
            return x;
        }
    
        // Левый поворот
        Node* leftRotate(Node* x) {
            Node* y = x->right;
            Node* T2 = y->left;
    
            // Поворот
            y->left = x;
            x->right = T2;
    
            // Обновление высот
            updateHeight(x);
            updateHeight(y);
    
            // Возвращаем новый корень
            return y;
        }
    
        // Добавление элемента (рекурсивная функция)
        Node* insert(Node* node, int key) {
            if (node == nullptr) {
                return new Node(key);
            }
    
            if (key < node->key) {
                node->left = insert(node->left, key);
            } else if (key > node->key) {
                node->right = insert(node->right, key);
            } else {
                // Дубликаты не допускаются
                return node;
            }
    
            updateHeight(node);
    
            int balance = getBalance(node);
    
            // Левый случай
            if (balance > 1 && key < node->left->key) {
                return rightRotate(node);
            }
    
            // Правый случай
            if (balance < -1 && key > node->right->key) {
                return leftRotate(node);
            }
    
            // Левый-правый случай
            if (balance > 1 && key > node->left->key) {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
    
            // Правый-левый случай
            if (balance < -1 && key < node->right->key) {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
    
            return node;
        }
    
        // Поиск элемента (рекурсивная функция)
        Node* search(Node* node, int key) const {
            if (node == nullptr) {
                return nullptr; // Не найдено
            }
    
            if (key == node->key) {
                return node; // Найдено
            } else if (key < node->key) {
                return search(node->left, key);
            } else {
                return search(node->right, key);
            }
        }
    
        // Поиск минимального узла в поддереве
        Node* minValueNode(Node* node) {
            Node* current = node;
            while (current->left != nullptr) {
                current = current->left;
            }
            return current;
        }
    
        // Удаление элемента (рекурсивная функция)
        Node* remove(Node* node, int key) {
            if (node == nullptr) {
                return nullptr; // Не найдено
            }
    
            if (key < node->key) {
                node->left = remove(node->left, key);
            } else if (key > node->key) {
                node->right = remove(node->right, key);
            } else {
                // Узел с одним или нулем потомков
                if (node->left == nullptr || node->right == nullptr) {
                    Node* temp = node->left ? node->left : node->right;
    
                    // Случай без потомков
                    if (temp == nullptr) {
                        temp = node;
                        node = nullptr;
                    } else {
                        // Случай с одним потомком
                        *node = *temp; // Копируем содержимое потомка
                    }
                    delete temp;
                } else {
                    // Узел с двумя потомками
                    Node* temp = minValueNode(node->right);
                    node->key = temp->key;
                    node->right = remove(node->right, temp->key);
                }
            }
    
            if (node == nullptr) {
                return nullptr; // Если дерево стало пустым
            }
    
            updateHeight(node);
    
            int balance = getBalance(node);
    
            // Левый случай
            if (balance > 1 && getBalance(node->left) >= 0) {
                return rightRotate(node);
            }
    
            // Левый-правый случай
            if (balance > 1 && getBalance(node->left) < 0) {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
    
            // Правый случай
            if (balance < -1 && getBalance(node->right) <= 0) {
                return leftRotate(node);
            }
    
            // Правый-левый случай
            if (balance < -1 && getBalance(node->right) > 0) {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
    
            return node;
        }
    
        // Чтение (Inorder traversal)
        void inorder(Node* node) const {
            if (node != nullptr) {
                inorder(node->left);
                std::cout << node->key << " ";
                inorder(node->right);
            }
        }
    
    public:
        AVLTree() : root(nullptr) {}
    
        // Добавление элемента
        void insert(int key) {
            root = insert(root, key);
        }
    
        // Поиск элемента
        bool search(int key) const {
            return search(root, key) != nullptr;
        }
    
        // Удаление элемента
        void remove(int key) {
            root = remove(root, key);
        }
    
        // Чтение
        void print() const {
            inorder(root);
            std::cout << std::endl;
        }
    
         ~AVLTree() {
            // 
        }
    };