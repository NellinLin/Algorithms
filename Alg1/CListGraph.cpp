#include "CListGraph.h"

ListGraph::ListGraph(int count) {
    adjacency_lists.resize(count);
}

ListGraph::ListGraph(const IGraph& graph) {
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        adjacency_lists.push_back(graph.GetNextVertices(i));
    }
}

ListGraph::~ListGraph() {
    adjacency_lists.clear();
}

void ListGraph::AddEdge(int from, int to) {
    adjacency_lists[from].push_back(to);
}

int ListGraph::VerticesCount() const {
    return adjacency_lists.size();
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    std::vector<int> next;
    for (int i = 0; i < adjacency_lists[vertex].size(); ++i) {
        next.push_back(adjacency_lists[vertex][i]);
    }
    return next;
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prev;
    for (int i = 0; i < adjacency_lists.size(); ++i) {
        for (int j = 0; j < adjacency_lists[i].size(); ++j) {
            if (adjacency_lists[i][j] == vertex) {
                prev.push_back(i);
            }
        }
    }
    return prev;
}