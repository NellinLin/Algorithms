#include "CMatrixGraph.h"

MatrixGraph::MatrixGraph(int count) {
    adjacency_matrix.resize(count);
    for (int i = 0; i < adjacency_matrix.size(); ++i) {
        adjacency_matrix[i].resize(count, 0);
    }
}

MatrixGraph::MatrixGraph(const IGraph& graph) {
    adjacency_matrix.resize(graph.VerticesCount());

    for (int i = 0; i < adjacency_matrix.size(); ++i) {
        adjacency_matrix[i].resize(graph.VerticesCount(), 0);

        std::vector<int> vertices = graph.GetNextVertices(i);
        for (int j = 0; j < vertices.size(); ++j) {
            AddEdge(i, vertices[j]);
        }
    }
}

MatrixGraph::~MatrixGraph() {
    adjacency_matrix.clear();
}

void MatrixGraph::AddEdge(int from, int to) {
    adjacency_matrix[from][to] = 1;
}

int MatrixGraph::VerticesCount() const {
    return adjacency_matrix.size();
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    std::vector<int> next_vertices;
    for (int i = 0; i < adjacency_matrix.size(); ++i) {
        if (adjacency_matrix[vertex][i] == 1)
            next_vertices.push_back(i);
    }
    return next_vertices;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prev_vertices;
    for (int i = 0; i < adjacency_matrix.size(); ++i) {
        if (adjacency_matrix[i][vertex] == 1)
            prev_vertices.push_back(i);
    }
    return prev_vertices;
}
