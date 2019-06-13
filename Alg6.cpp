/*
id: 19821526
Шишова Анастасия

Задача: 6_3
Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n. 
Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло 
на позиции с индексом k (0..n-1) в отсортированном массиве. Напишите нерекурсивный алгоритм.

Реализуйте стратегию выбора опорного элемента “случайный элемент”. 
Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.
*/

#include <iostream>

template <typename T, class Compare>
int Partition(T *array, int left, int right, const Compare &compare);

template <typename T, class Compare>
T Find_value_order_statistics(T *array, int array_size, int order_stat_index, const Compare &compare);

int *Create_array(int array_size);


int main(void) {
    int array_size = 0, order_statistics = 0;
    std::cin >> array_size >> order_statistics;

    int *array = Create_array(array_size);

    std::cout << Find_value_order_statistics(array, array_size, order_statistics, [](int x, int y) {return x > y; });
    return 0;
}


template <typename T, class Compare>
int Partition(T *array, int left, int right, const Compare &compare) {
    int rand_ind = left;
    if (left != right)
        rand_ind = rand() % (right - left) + left;

    std::swap(array[rand_ind], array[right]);

    T pivot = array[right];
    int i = left, j = left;

    for (;;) {
        for (; compare(array[j], pivot); j++);
        if (j != right) {
            std::swap(array[j], array[i]);
            j++;
            i++;
        }
        if (j == right)
            break;
    }
    std::swap(array[right], array[i]);
    return i;
}

template <typename T, class Compare>
T Find_value_order_statistics(T *array, int array_size, int order_stat_index, const Compare &compare) {
    int left = 0, right = array_size - 1;
    int partition = 0;

    for (;;) {
        partition = Partition(array, left, right, compare);

        if (partition == order_stat_index)
            return array[partition];

        if (partition > order_stat_index) {
            right = partition - 1;
        }
        else {
            left = partition + 1;
        }
    }
}

int *Create_array(int array_size) {
    int *array = new int[array_size];

    for (size_t i = 0; i < array_size; i++) {
        std::cin >> array[i];
    }
    return array;
}