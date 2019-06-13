/*
ID: 19692846
Шишова Анастасия

Реализовать очередь с помощью двух стеков. »спользовать стек, реализованный с помощью динамического буфера.
обрабатывать команды push back и pop front.
*/

#include <iostream>
#include <assert.h>
#define STACKSIZE 64
#define TOP -1

class Stack {
private:
    int *Mass_stack;
    int Top;
    int Size;

public:
    Stack();
    ~Stack();
    void Push_back( int value);
    void Pop_back();
    void Show();
    bool Is_empty();
    void Pop_all();
    int Get_value(int index);
    int operator[](int index);
    int Get_top_value();
    int Get_top() { return Top; }
    Stack& operator=(Stack stack1);
};

class Queue {
private:
    Stack Stack_in;
    Stack Stack_out;
public:
    Queue() {};
    ~Queue() {};
    void Push_back(int value);
    void Pop_front();
    void Show();
    int Get_top_value();
    int Get_before_pop();
};


int main(void) {
    Queue q;
    int n = 0, a = 0, b = 0, val = 0;
    bool flag = true;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a >> b;
        if (flag == true) {
            switch (a) {
            case 2:
                val = q.Get_before_pop();
                q.Pop_front();
                if (b != val) flag = false;
                break;

            case 3:
                q.Push_back(b);
                val = q.Get_top_value();
                if (b != val) flag = false;
                break;
            }
        }
    }
    if (flag == true) std::cout << "YES";
    else std::cout << "NO";
    return 0;
}

// Методы для Stack
int Stack::operator[](int index) {
    if (Top != (-1) && index <= Top) {
        return Mass_stack[index];
    }
    return TOP;
}

Stack& Stack::operator=(Stack stack1) {
    while (stack1.Top != (-1)) {
        this->Push_back(stack1.Get_value(stack1.Top));
        stack1.Top--;
    }
    return *this;
}

Stack::Stack() {
    Mass_stack = new int[STACKSIZE];
    Size = STACKSIZE;
    Top = -1;
}

Stack::~Stack() {
    if (Mass_stack != NULL)
        delete[]Mass_stack;
}

void Stack::Push_back(int value) {
    Top++;
    if (Size == 0 || Size <= Top) {
        int New_size = Size*2;
        int *Buffer_mass = new int[New_size];
        for (int i = 0; i < Top; i++) {
            Buffer_mass[i] = Mass_stack[i];
        }
        delete[]Mass_stack;
        Mass_stack = Buffer_mass;
        Size = New_size;
    }
    Mass_stack[Top] = value;
}

void Stack::Pop_back() {
    if (Top != (-1)) {
        Top--;
    }
}

void Stack::Show() {
    for (int i = 0; i <= Top; i++) {
        std::cout << Mass_stack[i] << " ";
    }
}

bool Stack::Is_empty() {
    if (Top == -1) return 1;
    else return 0;
}

void Stack::Pop_all() {
    if (Top != -1) Top = -1;
}

int Stack::Get_value(int index) {
    assert(Top != (-1) && index <= Top);
    return Mass_stack[index];
}

int Stack::Get_top_value() {
    assert (Top != (-1));
    return Mass_stack[Top];
}

// Методы для Queue
void Queue::Push_back(int value) {
    Stack_in.Push_back(value);
}

void Queue::Pop_front() {
    if (Stack_out.Is_empty()) {
        int top = Stack_in.Get_top();
        if (top != (-1)) {
            while (top != (-1)) {
                Stack_out.Push_back(Stack_in.Get_value(top));
                top--;
            }
        }
        Stack_in.Pop_all();
        Stack_out.Pop_back();
    }
    else Stack_out.Pop_back();
}

void Queue::Show() {
    Stack_out.Show();
    Stack_in.Show();
}

int Queue::Get_top_value() {
    if (Stack_in.Is_empty() && (!Stack_out.Is_empty())) {
        return Stack_out.Get_value(0);
    }
    else if (!Stack_in.Is_empty()) {
        return Stack_in.Get_top_value();
    }
}

int Queue::Get_before_pop() {
    if (!Stack_out.Is_empty()) {
        return Stack_out.Get_top_value();
    }
    else if (!Stack_in.Is_empty()) {
        return Stack_in.Get_value(0);
    }
}