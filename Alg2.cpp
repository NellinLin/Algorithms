/*
RunID: 20485138

Шишова Анастасия
Задача: 2

Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами. Найдите количество различных кратчайших путей между заданными вершинами. Требуемая сложность O(V+E).
Формат ввода.
v: кол-во вершин (макс. 50000),
n: кол-во ребер (макс. 200000),
n пар реберных вершин,
пара вершин u, w для запроса.
Формат вывода.
Количество кратчайших путей от u к w.
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;


struct IGraph {
    virtual ~IGraph() {}

    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

class ListGraph : public IGraph {
public:
    ListGraph(int count);
    ListGraph(const IGraph& graph);

    ~ListGraph();
    virtual void AddEdge(int from, int to) override;
    virtual int VerticesCount() const override;

    virtual std::vector<int> GetNextVertices(int vertex) const override;
    virtual std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<int>> adjacency_lists;
};

int DFS(const IGraph& graph, int vertex_to, int vertex_from, int V);

struct Ways {
    int min_way;
    int count;

    Ways() {
        min_way = 0;
    }
    void setWaysCounts(int _way, int _count){
        min_way = _way;
        count = _count;
    }
};



int main() {
    int V, E;
    int v_from, v_to;

    cin >> V >> E;
    ListGraph graph(V);

    int vertex1, vertex2;
    for (int i = 0; i < E; i++) {
        cin >> vertex1 >> vertex2;
        graph.AddEdge(vertex1, vertex2);
    }
    cin >> v_from >> v_to;
    cout << DFS(graph, v_to, v_from, V);

    return 0;
}


// Graph *******************************************************************

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

// Functions *******************************************************************

int DFS(const IGraph& graph, int vertex_to, int vertex_from, int V) {
    vector<bool> visited(V, false);
    vector<Ways> ways(visited.size());
    queue<int> q;

    q.push(vertex_from);
    visited[vertex_from] = true;
    ways[vertex_from].setWaysCounts(0, 1);

    while (!q.empty()) {
        int vertex = q.front();
        q.pop();

        std::vector<int> adjacentVertices = graph.GetNextVertices(vertex);
        for (int i = 0; i < adjacentVertices.size(); i++) {
            if (!visited[adjacentVertices[i]]) {
                ways[adjacentVertices[i]].setWaysCounts(ways[vertex].min_way + 1, ways[vertex].count);
                visited[adjacentVertices[i]] = true;
                q.push(adjacentVertices[i]);
            }
            else {
                if ((ways[vertex].min_way + 1) < ways[adjacentVertices[i]].min_way) {
                    ways[adjacentVertices[i]].setWaysCounts(ways[vertex].min_way, 1);
                }
                else if ((ways[vertex].min_way + 1) == ways[adjacentVertices[i]].min_way) {
                    ways[adjacentVertices[i]].count += ways[vertex].count;
                }
            }
        }
    }

    return ways[vertex_to].count;
}