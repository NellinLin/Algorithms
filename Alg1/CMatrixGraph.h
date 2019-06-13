#ifndef IMATRIXGRAPH_H_
#define IMATRIXGRAPH_H_

#include "IGraph.h"

class MatrixGraph : public IGraph {
public:
    MatrixGraph(int count);
    MatrixGraph(const IGraph& graph);

    ~MatrixGraph();
    virtual void AddEdge(int from, int to) override;
    virtual int VerticesCount() const override;

    virtual std::vector<int> GetNextVertices(int vertex) const override;
    virtual std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<bool>> adjacency_matrix;
};

#endif // IMATRIXGRAPH_H_