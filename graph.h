#ifndef TGRAPH_H
#define TGRAPH_H

#include <QString>
#include <exception>
#include <QGraphicsScene>
#include <QDebug>
#include <vector>
#include "vertex.h"
#include "edge.h"


class TGraph
{
public:
    TGraph(QString pathMatrix);
    TGraph(int numVertex, int numEdge);
    ~TGraph();
    void ArrangeCircle(float radius, int screenWidth, int screenHeight);
    void AddToScene(QGraphicsScene* scene);

private:
    std::vector<TVertex*> _ArrVertex;
    std::vector<TEdge*> _ArrEdge;

};

#endif // TGRAPH_H
