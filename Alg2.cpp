/*
RunID: 20119906

Шишова Анастасия
Задача: 2_2

Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N. 
Требуется построить бинарное дерево, заданное наивным порядком вставки. Т.е., 
при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, 
то узел K добавляется в правое поддерево root; иначе в левое поддерево root. Выведите 
элементы в порядке pre-order (сверху вниз).

Рекурсия запрещена.

PreOrder:
in:
    10
    1 5 10 2 4 3 8 9 7 6
out:
    1 5 2 4 3 10 8 7 6 9 
*/

#include <iostream>
#include <vector>

using namespace std;

template <class T>
class BinaryTree {
private:
    struct Node {
        T key;
        Node *left;
        Node *right;
        Node *parent;

        Node();
        Node(T& _key, Node *_left, Node *_right, Node * _parent);
    };

    Node *root;
    int count;

public:
    BinaryTree();
    ~BinaryTree();

    void insert(T& value);
    void clear();
    vector<T> printPreOrder();
    int getCount();
    Node* getRoot() { return root; }
};


int main(void) {
    int n, value;
    BinaryTree<int> tree;
    vector<int> pre_order;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> value;
        tree.insert(value);
    }

    pre_order = tree.printPreOrder();
    for (vector<int>::iterator it = pre_order.begin(); it != pre_order.end(); it++) {
        cout << *it << " ";
    }

    return 0;
}


// Конструкторы Node

template <class T>
BinaryTree<T>::Node::Node() {
    key = 0;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

template <class T>
BinaryTree<T>::Node::Node(T& _key, Node *_left, Node *_right, Node * _parent) {
    key = _key;
    left = _left;
    right = _right;
    parent = _parent;
}


// Конструкторы и методы BinaryTree

template <class T>
BinaryTree<T>::BinaryTree() {
    root = nullptr;
    count = 0;
}

template <class T>
BinaryTree<T>::~BinaryTree() {
    clear();
}

template <class T>
void BinaryTree<T>::clear() {
    if (root == nullptr) return;

    Node *ptr = root;
    Node *lastptr = nullptr;

    while (root != nullptr)
    {
        if (ptr->left != nullptr)
        {
            ptr = ptr->left;
            lastptr = ptr;
            continue;
        }
        if (ptr->right != nullptr)
        {
            ptr = ptr->right;
            lastptr = ptr;
            continue;
        }
        if (ptr->parent != nullptr)
        {
            ptr = ptr->parent;
            if (ptr->left == lastptr)
            {
                lastptr = ptr;
                delete ptr->left;
                ptr->left = nullptr;
            }
            if (ptr->right == lastptr)
            {
                lastptr = ptr;
                delete ptr->right;
                ptr->right = nullptr;
            }
        }
        else
        {
            delete ptr;
            root = nullptr;
        }
    }
}

template <class T>
void BinaryTree<T>::insert(T& value) {
    Node *parent = nullptr;
    Node *temp = root;

    while (temp != nullptr) {
        parent = temp;
        if (temp->key <= value) {
            temp = temp->right;
        }
        else {
            temp = temp->left;
        }
    }

    Node *new_node = new Node(value, nullptr, nullptr, parent);

    if (parent == nullptr) {
        root = new_node;
    }
    else if (parent->key <= new_node->key) {
        parent->right = new_node;
    }
    else {
        parent->left = new_node;
    }

    count++;
}

template <class T>
int BinaryTree<T>::getCount() {
    return count;
}

template <class T>
vector<T> BinaryTree<T>::printPreOrder() {
    Node *ptr = root;
    Node *lastptr = nullptr;
    vector<T> pre_order;

    if (root == nullptr)
        return pre_order;

    pre_order.push_back(ptr->key);

    while (true)
    {
        if (ptr->left != nullptr)
        {
            ptr = ptr->left;
            pre_order.push_back(ptr->key);
            continue;
        }
        if (ptr->right != nullptr)
        {
            ptr = ptr->right;
            lastptr = ptr;
            pre_order.push_back(ptr->key);
            continue;
        }
        if (ptr->parent != nullptr)
        {
            ptr = ptr->parent;
            if (ptr->right != nullptr && ptr->right != lastptr)
            {
                ptr = ptr->right;
                pre_order.push_back(ptr->key);
                lastptr = ptr;
            }
            else
            {
                while (ptr->parent != nullptr && (ptr->right == nullptr || ptr->right == lastptr))
                {
                    lastptr = ptr;
                    ptr = ptr->parent;
                }
                if (ptr->right != lastptr)
                {
                    ptr = ptr->right;
                    pre_order.push_back(ptr->key);
                    lastptr = ptr;
                }
                if (ptr->parent == nullptr)
                {
                    return pre_order;
                }
            }
        }
    }

}
