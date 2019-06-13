/*
Шишова Анастасия

Задача: 5_1
Покупатель получает на вход -> время входа и время выхода
Нужно показать пользователям минимум две рекламы, вы вести минимальное количестов рекламы.
*/

#include <iostream>
#include <string.h>

class Buyer {
public:
    int In_time;
    int Out_time;

    Buyer() {};
    ~Buyer() {};

    void Add(int in_time, int out_time) {
        In_time = in_time;
        Out_time = out_time;
    }
};

void Show(Buyer *a, int a_len);

template <class Compare>
int Merge(Buyer *a, int a_len, Buyer *b, int b_len, Buyer *c, const Compare &compare);

template <class Compare>
void MergeSort(Buyer *a, int a_len, const Compare &compare);

void Show(Buyer *a, int a_len);

int Advertising_calculator();


int main(void) {
    std::cout << Advertising_calculator();
    return 0;
}

template <class Compare>
int Merge(Buyer *a, int a_len, Buyer *b, int b_len, Buyer *c, const Compare &compare) {
    int i = 0, j = 0;
    int position = 0;

    while (i < a_len && j < b_len) {
        if (compare(a[i], b[j])) {
            position += b_len - j;
            c[i + j].Add(a[i].In_time, a[i].Out_time);
            i++;
        }
        else {
            c[i + j].Add(b[j].In_time, b[j].Out_time);
            j++;
        }
    }
    if (i >= a_len) {
        for (; j < b_len; j++) {
            c[i + j].Add(b[j].In_time, b[j].Out_time);
        }
    }
    else {
        for (; i < a_len; i++) {
            c[i + j].Add(a[i].In_time, a[i].Out_time);
        }
    }
    return position;
}

template <class Compare>
void MergeSort(Buyer *a, int a_len, const Compare &compare) {
    if (a_len <= 1) {
        return;
    }
    int firstLen = a_len / 2;
    int secondLen = a_len - firstLen;
    MergeSort(a, firstLen, compare);
    MergeSort(a + firstLen, secondLen, compare);
    Buyer *c = new Buyer[a_len];
    Merge(a, firstLen, a + firstLen, secondLen, c, compare);
    memcpy(a, c, sizeof(Buyer) * a_len);
    delete[] c;;
}

void Show(Buyer *a, int a_len) {
    for (int i = 0; i < a_len; i++) {
        std::cout << a[i].In_time << "  " << a[i].Out_time << std::endl;
    }
}

int Advertising_calculator() {
    int n = 0;
    std::cin >> n;

    Buyer *buyers = new Buyer[n];
    for (int i = 0; i < n; i++) {
        int buf1 = 0, buf2 = 0;
        std::cin >> buf1 >> buf2;
        buyers[i].Add(buf1, buf2);
    }

    MergeSort(buyers, n, [](Buyer X, Buyer Y) {return X.Out_time < Y.Out_time; });

    int ad_count = 0;
    int left = -1, right = -1;

    //Show(buyers, n);

    for (int i = 0; i < n; i++) {

        if (buyers[i].In_time > right) {
            ad_count += 2;
            left = buyers[i].Out_time - 1;
            right = buyers[i].Out_time;
        }
        else if (buyers[i].In_time == right) {
            ad_count++;
            left = right;
            right = buyers[i].Out_time;
        }
        else if (buyers[i].In_time > left && buyers[i].In_time < right) {
            ad_count++;
            left = buyers[i].Out_time;
        }
        else if (buyers[i].In_time > left && buyers[i].Out_time > right) {
            ad_count++;
            left = right;
            right = buyers[i].Out_time;
        }
    }

    return ad_count;
}