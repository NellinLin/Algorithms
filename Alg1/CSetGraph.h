#ifndef ISETGRAPH_H_
#define ISETGRAPH_H_

#include "IGraph.h"

class SetGraph : public IGraph {
public:
    SetGraph(int count);
    SetGraph(const IGraph& graph);

    ~SetGraph();
    virtual void AddEdge(int from, int to) override;
    virtual int VerticesCount() const override;

    virtual std::vector<int> GetNextVertices(int vertex) const override;
    virtual std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::unordered_set<int>> set_vertices_from;
    std::vector<std::unordered_set<int>> set_vertices_to;
    int vertices_count;
};

#endif // ISETGRAPH_H_