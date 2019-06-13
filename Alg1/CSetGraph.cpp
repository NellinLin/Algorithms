#include "CSetGraph.h"

SetGraph::SetGraph(int count) {
    vertices_count = count;
    set_vertices_from.resize(count);
    set_vertices_to.resize(count);
}

SetGraph::SetGraph(const IGraph& graph) {
    vertices_count = graph.VerticesCount();
    set_vertices_from.resize(vertices_count);
    set_vertices_to.resize(vertices_count);

    for (int i = 0; i < vertices_count; ++i) {
        std::vector<int> vertices = graph.GetNextVertices(i);

        for (int j = 0; j < vertices.size(); ++j) {
            AddEdge(i, vertices[j]);
        }
    }
}

SetGraph::~SetGraph() {
    set_vertices_from.clear();
    set_vertices_to.clear();
}

void SetGraph::AddEdge(int from, int to) {
    set_vertices_from[from].insert(to);
    set_vertices_to[to].insert(from);
}

int SetGraph::VerticesCount() const {
    return vertices_count;
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    std::vector<int> next_vertices;
    for (auto it = set_vertices_from[vertex].begin(); it != set_vertices_from[vertex].end(); ++it) {
        next_vertices.push_back(*it);
    }

    return next_vertices;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prev_vertices;
    for (auto it = set_vertices_to[vertex].begin(); it != set_vertices_to[vertex].end(); ++it) {
        prev_vertices.push_back(*it);
    }

    return prev_vertices;
}