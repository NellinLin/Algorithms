#ifndef IARCGRAPH_H_
#define IARCGRAPH_H_

#include "IGraph.h"

class ArcGraph : public IGraph {
public:
    ArcGraph(int count);
    ArcGraph(const IGraph& graph);

    ~ArcGraph();
    virtual void AddEdge(int from, int to) override;
    virtual int VerticesCount() const override;

    virtual std::vector<int> GetNextVertices(int vertex) const override;
    virtual std::vector<int> GetPrevVertices(int vertex) const override;

private:
    struct Edge {
        int from;
        int to;

        Edge(int _from, int _to) {
            from = _from;
            to = _to;
        }
    };

    std::vector<Edge> edge_array;
    int vertices_count;
};

#endif // IARCGRAPH_H_