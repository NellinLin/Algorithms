/*
RunID: 20224174

Шишова Анастасия
Задача: 1_2

Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
Хранимые строки непустые и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае,
когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и
проверки принадлежности данной строки множеству.

Для разрешения коллизий используйте двойное хеширование.
*/


#include <iostream>
#include <string>
#include <vector>
#define TSIZE 8
#define A1 23
#define A2 17

using namespace std;

template <class Type>
struct HashTableNode {
    Type key;
    bool is_delete;

    HashTableNode(const Type &_key) : key(_key), is_delete(false) {}
};

template <class Type>
class HashTable {
private:
    int count;
    vector<HashTableNode<Type>*> table;

    int hashFunc1(const Type &str, int tablesize);
    int hashFunc2(const Type &str, int tablesize);
    int hashFunction(int hash1, int hash2, int i, int tablesize);

public:
    HashTable() : table(TSIZE, NULL), count(0) {}

    bool insert(const Type &_key);
    bool remove(const Type &_key);
    bool has(const Type &_key);
    void reHash();
};

int main() {
    HashTable<string> table;
    char activity;
    string value;

    while (cin >> activity >> value) {

        switch (activity) {
        case '+':
            if (table.insert(value))
                cout << "OK" << endl;
            else
                cout << "FAIL" << endl;
            break;

        case '-':
            if (table.remove(value))
                cout << "OK" << endl;
            else
                cout << "FAIL" << endl;
            break;

        case '?':
            if (table.has(value))
                cout << "OK" << endl;
            else
                cout << "FAIL" << endl;
            break;

        default:
            continue;
        }

    }
    return 0;
}

// Методы HashTable ****************************************************

template <typename Type>
bool HashTable<Type>::insert(const Type &_key) {
    if ((double)count / (double)table.size() >= 0.75) {
        reHash();
    }

    int hash1 = hashFunc1(_key, table.size());
    int hash2 = hashFunc2(_key, table.size());
    int hash = hashFunction(hash1, hash2, 0, table.size());

    for (int i = 0; i < table.size() && table[hash] != NULL; i++) {
        if (table[hash]->is_delete == false && table[hash]->key == _key)
            return false;

        if (table[hash]->is_delete == true) {
            table[hash]->key = _key;
            table[hash]->is_delete = false;
            count++;
            return true;
        }
        hash = hashFunction(hash1, hash2, i + 1, table.size());
    }

    table[hash] = new HashTableNode<Type>(_key);
    count++;

    return true;
}

template <typename Type>
bool HashTable<Type>::remove(const Type &_key) {
    int hash1 = hashFunc1(_key, table.size());
    int hash2 = hashFunc2(_key, table.size());
    int hash = hashFunction(hash1, hash2, 0, table.size());

    for (int i = 0; i < table.size(); i++) {
        if (table[hash] == NULL) {
            return false;
        }
        if (table[hash]->key == _key && table[hash]->is_delete == false) {
            table[hash]->is_delete = true;
            count--;
            return true;
        }
        hash = hashFunction(hash1, hash2, i + 1, table.size());
    }
}

template <typename Type>
bool HashTable<Type>::has(const Type &_key) {
    int hash1 = hashFunc1(_key, table.size());
    int hash2 = hashFunc2(_key, table.size());
    int hash = hashFunction(hash1, hash2, 0, table.size());

    for (int i = 0; i < table.size() && table[hash] != NULL; i++) {
        if (table[hash]->key == _key && table[hash]->is_delete == false) {
            return true;
        }
        hash = hashFunction(hash1, hash2, i + 1, table.size());
    }
    return false;
}

template <typename Type>
void HashTable<Type>::reHash() {
    int hash = 0;
    int buffer_size = table.size() * 2;
    vector<HashTableNode<Type>*> buffer_table(buffer_size, NULL);

    for (int i = 0; i < table.size(); i++) {
        if (table[i] != NULL) {
            if (table[i]->is_delete == false) {
                hash = hashFunction(hashFunc1(table[i]->key, buffer_size), hashFunc2(table[i]->key, buffer_size), 0, buffer_size);

                for (int j = 0; j < buffer_size && buffer_table[hash] != NULL; j++) {
                    hash = hashFunction(hashFunc1(table[i]->key, buffer_size), hashFunc2(table[i]->key, buffer_size), j, buffer_size);
                }

                buffer_table[hash] = table[i];
            }
        }
    }
    table = buffer_table;
}

// Hash функции ********************************************************
template <typename Type>
int HashTable<Type>::hashFunc1(const Type &str, int tablesize) {
    int hash = 0;
    for (int i = 0; i < str.size(); i++) {
        hash = (hash * A1 + str[i]) % tablesize;
    }
    return hash;
}

template <typename Type>
int HashTable<Type>::hashFunc2(const Type &str, int tablesize) {
    int hash = 0;
    for (int i = 0; i < str.size(); i++) {
        hash = (hash * A2 + str[i]) % tablesize;
    }
    hash = (hash * 2 + 1) % tablesize; // hash2 взфимнопростой с tablesize
    return hash;
}

template <typename Type>
int HashTable<Type>::hashFunction(int hash1, int hash2, int i, int tablesize) {
    if (tablesize == 0) {
        return 0;
    }
    return (hash1 + hash2 * i) % tablesize;
}