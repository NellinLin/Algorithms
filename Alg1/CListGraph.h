#ifndef ILISTGRAPH_H_
#define ILISTGRAPH_H_

#include "IGraph.h"

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

#endif // ILISTGRAPH_H_