/*
RunID: 20133683

Шишова Анастасия
Задача: 3_1

Дано число N < 106 и последовательность пар целых чисел из [-231, 231] длиной N.
Построить декартово дерево из N узлов, характеризующихся парами чисел (Xi, Yi). Каждая пара чисел (Xi, Yi) определяет ключ Xi и приоритет Yi в декартовом дереве.
Добавление узла в декартово дерево выполняйте следующим образом: При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим приоритетом. Затем разбейте 
найденное поддерево по ключу x так, чтобы в первом поддереве все ключи меньше x, а во втором больше или равны x. Получившиеся два дерева сделайте дочерними для нового узла (x, y). Новый узел вставьте на место узла P.
Построить также наивное дерево поиска по ключам Xi.
Т.е., при добавлении очередного числа K в наивное дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.

Вычислить разницу глубин наивного дерева поиска и декартового дерева. Разница может быть отрицательна, необходимо вывести модуль разности.

*/

#include <iostream>
#include <stack>

using namespace std;

template <class T>
class CartesianTree {
private:
    struct CNode {
        T key;
        int priority;
        CNode *left;
        CNode *right;
        CNode *parent;

        CNode();
        CNode(T& _key, int _priority, CNode *_left, CNode *_right, CNode * _parent);
    };

    CNode *root;
    int count;

    void split(CNode *current, T& key, CNode *&_left, CNode *&_right);
    CNode* merge(CNode *_left, CNode *_right) {
        if (_left == 0 || _right == 0) {
            return (_left == 0) ? _right : _left;
        }
        if (_left->priority > _right->priority) {
            _left->right = merge(_left->right, _right);
            return _left;
        }
        else {
            _right->left = merge(_left, _right->left);
            return _right;
        }
    }

public:
    CartesianTree();
    ~CartesianTree();

    void insert(T& value, int _priority);
    void clear();
    int getCount();
    int getHeight();
    CNode* getRoot() { return root; }
};


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
    int getCount();
    int getHeight();
    Node* getRoot() { return root; }
};


int main(void) {
    int n, value, priority;
    BinaryTree<int> b_tree;
    CartesianTree<int> c_tree;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> value >> priority;
        b_tree.insert(value);
        c_tree.insert(value, priority);
    }

    cout << (b_tree.getHeight() - c_tree.getHeight());

    return 0;
}



// Конструкторы CartesianTree::Node ******************************************

template <class T>
CartesianTree<T>::CNode::CNode() {
    key = 0;
    priority = 0;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

template <class T>
CartesianTree<T>::CNode::CNode(T& _key, int _priority, CNode *_left, CNode *_right, CNode * _parent) {
    key = _key;
    priority = _priority;
    left = _left;
    right = _right;
    parent = _parent;
}

// Методы CartesianTree ******************************************************

template <class T>
CartesianTree<T>::CartesianTree() {
    root = nullptr;
    count = 0;
}

template <class T>
CartesianTree<T>::~CartesianTree() {
    clear();
}

template <class T>
int CartesianTree<T>::getCount() {
    return count;
}

template <class T>
void CartesianTree<T>::clear(){
    if (root == nullptr) return;

    CNode *ptr = root;
    CNode *lastptr = nullptr;

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
void CartesianTree<T>::split(CNode *current, T& _key, CNode *&_left, CNode *&_right) {
    if (current == 0) {
        _left = 0;
        _right = 0;
    }
    else if (current->key <= _key) {
        split(current->right, _key, current->right, _right);
        _left = current;
    }
    else {
        split(current->left, _key, _left, current->left);
        _right = current;
    }
}

//template <class T>
//CartesianTree<T>::CNode* CartesianTree<T>::merge(CNode *_left, CNode *_right) {
//    if (_left == 0 || _right == 0) {
//        return (_left == 0) ? _right : _left;
//    }
//    if (_left->priority > _right->priority) {
//        _left->right = merge(_left->right, _right);
//        return _left;
//    }
//    else {
//        _right->left = merge(_left, _right->left);
//        return _right;
//    }
//}

template <class T>
void CartesianTree<T>::insert(T& value, int _priority) {
    CNode *parent = nullptr;
    CNode *temp = root;

    while (temp != nullptr && temp->priority >= _priority) {
        parent = temp;
        if (temp->key < value) {
            temp = temp->right;
        }
        else {
            temp = temp->left;
        }
    }

    CNode *_left, *_right;
    split(temp, value, _left, _right);
    CNode *new_node = new CNode(value, _priority, _left, _right, parent);

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
int CartesianTree<T>::getHeight() {
    int height = 0;
    stack<CNode*> lr_nodes;
    stack<CNode*> path;

    if (root == nullptr)
        return 0;

    CNode *temp = root;
    lr_nodes.push(temp);
    while (!lr_nodes.empty()) {
        temp = lr_nodes.top();

        if (!path.empty() && temp == path.top()) {
            if (path.size() > height)
                height = path.size();

            path.pop();
            lr_nodes.pop();
        }
        else {
            path.push(temp);

            if (temp->left != nullptr)
                lr_nodes.push(temp->left);

            if (temp->right != nullptr)
                lr_nodes.push(temp->right);
        }
    }
    return height;
}

// Конструкторы BinaryTree::Node *********************************************

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

// Конструкторы и методы BinaryTree *****************************************

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
int BinaryTree<T>::getHeight() {
    int height = 0;
    stack<Node*> lr_nodes;
    stack<Node*> path;

    if (root == nullptr)
        return 0;
    
    Node *temp = root;
    lr_nodes.push(temp);
    while (!lr_nodes.empty()) {
        temp = lr_nodes.top();

        if (!path.empty() && temp == path.top()) {
            if (path.size() > height)
                height = path.size();

            path.pop();
            lr_nodes.pop();
        }
        else {
            path.push(temp);

            if (temp->left != nullptr)
                lr_nodes.push(temp->left);

            if (temp->right != nullptr)
                lr_nodes.push(temp->right);
        }
    }
    return height;
}
