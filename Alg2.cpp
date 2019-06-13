/*
ID: 19660779
Шишова Анастасия

Дан отсортированный массив целых чисел A[0..n - 1] и массив целых чисел B[0..m - 1].
Для каждого элемента массива B[i] найдите минимальный индекс k минимального элемента массива A, 
равного или превосходящего B[i]: A[k] >= B[i].Если такого элемента нет, выведите n.Время работы 
поиска k для каждого элемента B[i] : O(log(k)).
n, m ≤ 10000.
Формат входных данных.
В первой строчке записаны числа n и m.Во второй и третьей массивы A и B соответственно.
*/

#include <iostream>

int* Read_mass(int num);
void Delete_mass_memory(int *mass1, int *mass2);
int Binary_search(int *A, int value, int left, int right);
int Find_the_smallest_index(int *A, int value, int n);
void Find_index(int *A, int *B, int n, int m);

int main(void) {
    int n = 0, m = 0;
    std::cin >> n >> m;

    int *A = Read_mass(n);
    int *B = Read_mass(m);

    if (A == NULL || B == NULL) {
        std::cout << "[error]";
        return 0;
    }
    
    Find_index(A, B, n, m);

    Delete_mass_memory(A, B);
    return 0;
}

void Find_index(int *A, int *B, int n, int m) {
    int index = 0;
    for (int i = 0; i < m; i++) {
        if (i == m - 1) {
            std::cout << Find_the_smallest_index(A, B[i], n) << std::endl;
        }
        else std::cout << Find_the_smallest_index(A, B[i], n) << " ";
    }
}

int* Read_mass(int num) {
    int *mass = NULL;
    if (!(mass = new int[num])) {
        return NULL;
    }
    for (int i = 0; i < num; i++) {
        std::cin >> mass[i];
    }
    return mass;
}

void Delete_mass_memory(int *mass1, int *mass2) {
    delete[]mass1;
    delete[]mass2;
}

int Binary_search(int *A, int value, int left, int right) {
    bool flag = false;
    int middle_ind = 0;

    while ((left <= right) && (flag != true)) {
        middle_ind = (left + right) / 2;
        if (A[middle_ind] == value) flag = true;
        if (A[middle_ind] > value&&A[middle_ind - 1] < value) flag = true;
        else if (A[middle_ind] > value) right = middle_ind - 1;
        else left = middle_ind + 1;
    }

    return middle_ind;
}

int Find_the_smallest_index(int *A, int value, int n) {
    if (value > A[n - 1]) {
        return n;
    }

    int power1 = 0, power2 = 0;
    int index = 0;

    for (int i = 1; i < n; i *= 2) {
        if (((A[power1] <= value) && (value <= A[i])) || (value<A[0])) {
            power2 = i;
            break;
        }
        power1 = i;
    }
    if (power2 == 0) {
        power2 = n - 1;
    }

    index = Binary_search(A, value, power1, power2);
    return index;
}