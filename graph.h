#ifndef TGRAPH_H
#define TGRAPH_H

#include <QString>
#include <exception>
#include "vertex.h"
#include "edge.h"


class TGraph
{
public:
    TGraph(QString pathMatrix);
    TGraph(int numVertex, int numEdge);
    void ArrangeCircle();

private:
    std::vector<TVertex*> _ArrVertex;
    std::vector<TEdge*> _ArrEdge;

};

#endif // TGRAPH_H
