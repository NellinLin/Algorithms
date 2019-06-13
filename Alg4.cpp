/*
id: 19815583
Шишова Анастасия

Задача: 4_2
Для сложения чисел используется старый компьютер. Время, затрачиваемое 
на нахождение суммы двух чисел равно их сумме. Таким образом для нахождения 
суммы чисел 1,2,3 может потребоваться разное время, в зависимости от порядка 
вычислений. ((1+2)+3) -> 1+2 + 3+3 = 9 ((1+3)+2) -> 1+3 + 4+2 = 10 ((2+3)+1) 
-> 2+3 + 5+1 = 11 
Требуется написать программу, которая определяет минимальное время, достаточное 
для вычисления суммы заданного набора чисел. Требуемое время работы O(n*log(n)).

*/

#include <iostream>
#define HEAPSIZE 128


class Heap {
private:
    int *Heap_mass;
    int Size;
    int Mem_size;
public:
    Heap();
    ~Heap();
    void Sift_down(int i);
    void Sift_up(int i);
    void Build_heap();
    void Insert(int value);
    int Extract_min();
    bool Is_empty();
    void Show();
    int Calculate_time();
};

int Calculate_heap_time();


int main(void) {
    Calculate_heap_time();
    return 0;
}


int Calculate_heap_time() {
    int n = 0, value = 0;
    Heap h;

    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> value;
        h.Insert(value);
    }

    std::cout << h.Calculate_time();
    return 0;
}

Heap::Heap() {
    Size = 0;
    Heap_mass = new int[HEAPSIZE];
    Mem_size = HEAPSIZE;
}

Heap::~Heap() {
    delete[]Heap_mass;
}

void Heap::Sift_down(int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    int smallest = i;
    if (left < Size && Heap_mass[left] < Heap_mass[i])
        smallest = left;

    if (right < Size && Heap_mass[right] < Heap_mass[smallest])
        smallest = right;

    if (smallest != i) {
        std::swap(Heap_mass[i], Heap_mass[smallest]);
        Sift_down(smallest);
    }
}

void Heap::Sift_up(int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (Heap_mass[i] >= Heap_mass[parent])
            return;
        std::swap(Heap_mass[i], Heap_mass[parent]);
        i = parent;
    }
}
void Heap::Build_heap() {
    for (int i = Size / 2 - 1; i >= 0; i--)
        Sift_down(i);
}

void Heap::Insert(int value) {
    if (Size >= Mem_size) {
        int New_size = Mem_size * 2;
        int *Buffer_mass = new int[New_size];

        for (int i = 0; i < Size; i++) {
            Buffer_mass[i] = Heap_mass[i];
        }
        delete[]Heap_mass;

        Heap_mass = Buffer_mass;
        Mem_size = New_size;
    }
    Heap_mass[Size] = value;
    Size++;
    Sift_up(Size - 1);
}

bool Heap::Is_empty() {
    if (Size == 0)
        return 1;
    return 0;
}

int Heap::Extract_min() {
    int result = 0;
    if (!Is_empty()) {
        result = Heap_mass[0];
        Heap_mass[0] = Heap_mass[Size - 1];
        Size--;
        if (!Is_empty())
            Sift_down(0);
    }
    return result;
}

void Heap::Show() {
    for (int i = 0; i < Size; i++) {
        std::cout << Heap_mass[i] << " ";
    }
}

int Heap::Calculate_time() {
    int sum = 0, buf = 0;
    if (!Is_empty()) {
        if (Size == 1)
            return Heap_mass[0];
        for (int i = Size; i > 1; i--) {
            buf = Extract_min();
            Sift_down(0);
            buf += Heap_mass[0];
            sum += buf;
            Heap_mass[0] = buf;
            Sift_down(0);
            Build_heap();
        }
    }
    return sum;
}
