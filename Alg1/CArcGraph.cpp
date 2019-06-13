#include "CArcGraph.h"

ArcGraph::ArcGraph(int count) {
    vertices_count = count;
}

ArcGraph::ArcGraph(const IGraph& graph) {
    vertices_count = graph.VerticesCount();

    for (int i = 0; i < vertices_count; ++i) {
        std::vector<int> vertices = graph.GetNextVertices(i);

        for (int j = 0; j < vertices.size(); ++j) {
            AddEdge(i, vertices[j]);
        }
    }
}

ArcGraph::~ArcGraph() {
    edge_array.clear();
}

void ArcGraph::AddEdge(int from, int to) {
    for (int i = 0; i < edge_array.size(); ++i) {
        if (edge_array[i].from == from && edge_array[i].to == to)
            return;
    }

    Edge edge(from, to);
    edge_array.push_back(edge);
}

int ArcGraph::VerticesCount() const {
    return vertices_count;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    std::vector<int> next_vertices;
    for (int i = 0; i < edge_array.size(); ++i) {
        if (edge_array[i].from == vertex)
            next_vertices.push_back(edge_array[i].to);
    }

    return next_vertices;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prev_vertices;
    for (int i = 0; i < edge_array.size(); ++i) {
        if (edge_array[i].to == vertex)
            prev_vertices.push_back(edge_array[i].from);
    }

    return prev_vertices;
}