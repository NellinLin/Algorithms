//Необходимо написать несколько реализаций интерфейса :
//CListGraph, хранящий граф в виде массива списков смежности,
//CMatrixGraph, хранящий граф в виде матрицы смежности,
//CSetGraph, хранящий граф в виде массива хэш - таблиц,
//CArcGraph, хранящий граф в виде одного массива пар{ from, to }.

#include <iostream>
#include <vector>
#include <queue>

#include "CListGraph.h"
#include "CMatrixGraph.h"
#include "CArcGraph.h"
#include "CSetGraph.h"

void BFS(const IGraph& graph, int vertex, void(*visit)(int));

int main() {
    ListGraph l_gr(4);
    l_gr.AddEdge(0, 1);
    l_gr.AddEdge(0, 2);
    l_gr.AddEdge(1, 2);
    l_gr.AddEdge(1, 3);
    l_gr.AddEdge(2, 3);
    BFS(l_gr, 0, [](int vertex) { std::cout << vertex << " "; });
    std::vector<int> nv = l_gr.GetNextVertices(2);
    std::vector<int> pv = l_gr.GetPrevVertices(1);

    MatrixGraph m_gr(l_gr);
    BFS(m_gr, 0, [](int vertex) { std::cout << vertex << " "; });

    ArcGraph a_gr(l_gr);
    BFS(a_gr, 0, [](int vertex) { std::cout << vertex << " "; });

    SetGraph s_gr(l_gr);
    nv = s_gr.GetNextVertices(2);
    pv = s_gr.GetPrevVertices(1);
    BFS(a_gr, 0, [](int vertex) { std::cout << vertex << " "; });

    return 0;
}


void BFS(const IGraph& graph, int vertex, void(*visit)(int)) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    std::queue<int> qu;

    qu.push(vertex);
    visited[vertex] = true;

    while (qu.size() != 0) {
        int current = qu.front();
        qu.pop();
        visit(current);
        std::vector<int> adjacentVertices = graph.GetNextVertices(current);
        for (int i = 0; i < adjacentVertices.size(); ++i) {
            if (!visited[adjacentVertices[i]]) {
                qu.push(adjacentVertices[i]);
                visited[adjacentVertices[i]] = true;
            }
        }
    }
}