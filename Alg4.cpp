/*
RunID: 20246632

Ўишова јнастаси€
«адача: 4_2

ƒано число N и N строк.  ажда€ строка содержащит команду добавлени€ или удалени€ натуральных чисел, 
а также запрос на получение k-ой пор€дковой статистики.  оманда добавлени€ числа A задаетс€ положительным 
числом A, команда удалени€ числа A задаетс€ отрицательным числом У-AФ. «апрос на получение k-ой пор€дковой 
статистики задаетс€ числом k. “ребуема€ скорость выполнени€ запроса - O(log n).
*/


#include <iostream>
#include <vector>

using namespace std;


vector<int> v;

class AVL {
private:
    struct Node {
        int key;
        int height;
        Node* left;
        Node* right;

        Node(int _key) : key(_key), left(nullptr), right(nullptr), height(1) {}
    };

    int count;
    Node *root;

    Node* insert(int value, Node *node);
    Node* remove(int value, Node * node);

    Node* rotateRight(Node* p);
    Node* rotateLeft(Node* q);

    Node* balance(Node* p);
    Node* findMin(Node* p);
    Node* removeMin(Node* p);

public:
    AVL() :root(nullptr), count(0) {};
    ~AVL() { clear(root); }

    void insert(int value) { root = insert(value, root); }
    void remove(int value) { root = remove(value, root); }

    int getHeight(Node* p);
    Node* getRoot();

    int bfactor(Node* p);
    void fixHeight(Node* p);
    void clear(Node *root);

    int statistic(int stat);
    void inOrderTravers(Node* root);
};


int main(void) {
    int n, value, stat;
    AVL tree;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> value >> stat;

        if (value >= 0) {
            tree.insert(value);
        }
        else {
            tree.remove(abs(value));
        }
        cout << tree.statistic(stat) << " ";
    }

    return 0;
}


AVL::Node* AVL::insert(int value, Node *node) {
    if (!node)
        node = new Node(value);
    else if (value < node->key) {
        node->left = insert(value, node->left);
    }
    else if (value > node->key) {
        node->right = insert(value, node->right);
    }

    return balance(node);
}

AVL::Node* AVL::remove(int value, Node * node) {
    Node *temp;

    if (!node)
        return nullptr;

    else if (value < node->key)
        node->left = remove(value, node->left);
    else if (value > node->key)
        node->right = remove(value, node->right);

    else if (node->left && node->right) {
        temp = findMin(node->right);
        node->key = temp->key;
        node->right = remove(node->key, node->right);
    }
    else {
        temp = node;
        if (!node->left)
            node = node->right;
        else if (!node->right)
            node = node->left;
        delete temp;
    }

    if (!node)
        return node;

    return balance(node);
}

int AVL::getHeight(Node* p) {
    return p ? p->height : 0;
}

int AVL::bfactor(Node* p) {
    return getHeight(p->right) - getHeight(p->left);
}

void AVL::fixHeight(Node* p) {
    unsigned char hl = getHeight(p->left);
    unsigned char hr = getHeight(p->right);
    p->height = (hl>hr ? hl : hr) + 1;
}

AVL::Node* AVL::rotateRight(Node* p) {
    Node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixHeight(p);
    fixHeight(q);
    return q;
}

AVL::Node* AVL::rotateLeft(Node* q) {
    Node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixHeight(q);
    fixHeight(p);
    return p;
}

AVL::Node* AVL::balance(Node* p) {
    if (p) {
        fixHeight(p);
        if (bfactor(p) == 2)
        {
            if (bfactor(p->right) < 0)
                p->right = rotateRight(p->right);
            return rotateLeft(p);
        }
        if (bfactor(p) == -2)
        {
            if (bfactor(p->left) > 0)
                p->left = rotateLeft(p->left);
            return rotateRight(p);
        }
    }
    return p;
}

AVL::Node* AVL::findMin(Node* p) {
    if (!p) return nullptr;
    return p->left ? findMin(p->left) : p;
}

AVL::Node* AVL::removeMin(Node* p) {
    if (p->left == 0)
        return p->right;
    p->left = removeMin(p->left);
    return balance(p);
}

void AVL::inOrderTravers(Node* root) {
    if (root) {
        inOrderTravers(root->left);
        v.push_back(root->key);
        inOrderTravers(root->right);
    }
}

AVL::Node* AVL::getRoot() {
    return root;
}

int AVL::statistic(int stat) {
    if (!root) return 0;
    v.clear();
    inOrderTravers(root);

    return v[stat];
}

void AVL::clear(Node *root) {
    if (root == nullptr) return;
    clear(root->left);
    clear(root->right);
    delete root;
}


