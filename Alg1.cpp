/*
ID: 19637526
Шишова Анастасия 

Вычислить площадь выпуклого n-угольника, заданного координатами своих вершин.
В начале вводитс€ количество вершин, затем последовательно целочисленные 
координаты всех вершин в пор€дке обхода против часовой стрелки.

Указание:
Дл€ вычислени€ площади n-угольника посчитать сумму ориентированных площадей
трапеций под каждой стороной многоугольника.
*/

#include <iostream>
#define POINTS_SIZE 2
#define ERR 1

void Delete_points_memory(int **points, int points_num);
int **Read_points(int points_num);
float Area_calculation(int **points, int points_num);
float Area_abs(float area);

int main(void) {
    int points_num = 0, Error = 0;
    float area_of_poligon = 0;
    int **points = NULL;

    std::cin >> points_num;
    if (!(int)points_num) {
        Error = ERR;
    }

    if (Error != ERR) {
        points = Read_points(points_num);
    }
    if ((Error == ERR) || (points == NULL)) {
        std::cout << "[error]" << std::endl;
        return 0;
    }

    area_of_poligon = Area_calculation(points, points_num);
    std::cout << area_of_poligon;
    Delete_points_memory(points, points_num);
    return 0;
}

void Delete_points_memory(int **points, int points_num) {
    for (int i = 0; i<points_num; i++) delete(points[i]);
    delete[] points;
}

float Area_abs(float area) {
    if (area<0) {
        area = area * (-1);
    }
    return area;
}

int **Read_points(int points_num) {
    int **points;
    if (!(points = new int*[points_num])) {
        return NULL;
    }
    for (int i = 0; i < points_num; i++) {
        points[i] = new int[POINTS_SIZE];
    }
    for (int i = 0; i < points_num; i++) {
        std::cin >> points[i][0] >> points[i][1];
    }

    return points;
}

float Area_calculation(int **points, int points_num) {
    float area_of_poligon = 0;
    for (int i = 0; i < points_num - 1; i++) {
        area_of_poligon += (points[i + 1][1] + points[i][1])*(points[i + 1][0] - points[i][0]);
    }
    area_of_poligon += (points[0][1] + points[points_num - 1][1])*(points[0][0] - points[points_num - 1][0]);
    area_of_poligon = (float)area_of_poligon / 2;
    return Area_abs(area_of_poligon);
}
