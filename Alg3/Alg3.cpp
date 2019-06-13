#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <set>
#include <fstream>

using namespace std;
const int MAX = numeric_limits<int>::max();

struct IGraph {
    virtual ~IGraph() {}

    virtual void AddEdge(int from, int to, int length) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<std::pair<int, int>> GetNextVertices(int vertex) const = 0;
    virtual std::vector<std::pair<int, int>> GetPrevVertices(int vertex) const = 0;
};

class ArcGraph : public IGraph {
public:
    ArcGraph(int count);

    ~ArcGraph();
    virtual void AddEdge(int from, int to, int length) override;
    virtual int VerticesCount() const override;

    virtual std::vector<std::pair<int, int>> GetNextVertices(int vertex) const override;
    virtual std::vector<std::pair<int, int>> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<std::pair<int,int>>> edge_array;
    int vertices_count;
};

int DFS(const IGraph& graph, int vertex_to, int vertex_from);


int main() {
    int V, E;
    int v_from, v_to;
    ifstream fin("input1.txt");
    fin >> V >> E;
    ArcGraph graph(V);

    int vertex1, vertex2, len;
    for (int i = 0; i < E; i++) {
        fin >> vertex1 >> vertex2 >> len;
        graph.AddEdge(vertex1, vertex2, len);
    }
    fin >> v_from >> v_to;
    cout << DFS(graph, v_to, v_from);

    return 0;
}

// Graph *******************************************************************

ArcGraph::ArcGraph(int count) {
    vertices_count = count;
    edge_array.resize(count);
}

ArcGraph::~ArcGraph() {
    edge_array.clear();
}

void ArcGraph::AddEdge(int from, int to, int length) {
    edge_array[from].push_back(make_pair(to, length));
    edge_array[to].push_back(make_pair(from, length));
}

int ArcGraph::VerticesCount() const {
    return vertices_count;
}

std::vector<std::pair<int, int>> ArcGraph::GetNextVertices(int vertex) const {
    std::vector<std::pair<int, int>> next_vertices;
    next_vertices.resize(edge_array[vertex].size());
    for (int i = 0; i < edge_array[vertex].size(); ++i) {
        next_vertices.push_back(edge_array[vertex][i]);
    }

    return next_vertices;
}

std::vector<std::pair<int, int>> ArcGraph::GetPrevVertices(int vertex) const {
    std::vector<std::pair<int, int>> prev_vertices;
    prev_vertices.resize(edge_array[vertex].size());
    for (int i = 0; i < edge_array[vertex].size(); ++i) {
        prev_vertices.push_back(edge_array[vertex][i]);
    }

    return prev_vertices;
}

// Functions *******************************************************************

class Comparator {
public:
    bool operator()(const pair<int, int> &left, const pair<int, int> &right) const {
        return left.second <= right.second;
    }
};

int DFS(const IGraph& graph, int vertex_to, int vertex_from) {
    vector<bool> visited(graph.VerticesCount(), false);
    vector<int> min_ways(graph.VerticesCount(), MAX);
    set<pair<int, int>, Comparator> q;

    q.emplace(make_pair(vertex_from, 0));
    visited[vertex_from] = true;
    min_ways[vertex_from] = 0;

    while (!q.empty()) {
        int vertex = (q.begin())->first;
        q.erase(q.begin());
        visited[vertex] = true;

        std::vector<pair<int,int>> adjacentVertices = graph.GetNextVertices(vertex);

        for (pair<int,int> v_edge : adjacentVertices) {
            int new_way = min_ways[vertex] + v_edge.second;
            if (min_ways[v_edge.first] == MAX) {
                min_ways[v_edge.first] = min_ways[vertex] + v_edge.second;
                q.emplace(make_pair(v_edge.first, min_ways[v_edge.first]));
            }
            else {
                if (min_ways[v_edge.first] > new_way) {
                    q.erase(std::make_pair(v_edge.first, min_ways[v_edge.first]));
                    min_ways[v_edge.first] = new_way;
                    q.emplace(std::make_pair(v_edge.first, min_ways[v_edge.first]));
                }
            }
        }
    }
    if (min_ways[vertex_to] != MAX) return min_ways[vertex_to];
    return -1;
}