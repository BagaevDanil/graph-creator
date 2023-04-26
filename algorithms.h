#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <QVector>
#include <algorithm>

/*
namespace MyAlgorithms {
    TVertex* findMainParent(TVertex* defaultVertex);
    void mergeEdges(TVector<TEdge>& queueEdge, TVector<TEdge>& answerEdge);
    TVector<TEdge> kruskal(TVector<TEdge> arrEdges);
}
*/

/*
struct TVertex {

};

TVertex* findMainParent(TVertex* defaultVertex)
{
    if (defaultVertex->Parent() != nullptr) {
        defaultVertex->Parent() = findMainParent(defaultVertex->Parent());
    }

    if (defaultVertex->Parent()) {
        return defaultVertex->Parent();
    }
    return defaultVertex;
}

template <class Edge, class Vertex>
QVector<Edge> algorithmKruskal(QVector<Edge> arrEdges, QVector<Vertex> arrVertex)
{
    std::sort(arrEdges.begin(), arrEdges.end());
    QVector<Edge> answerEdge;

    for (auto& edge : arrEdges) {
        TVertex* x = findMainParent(&edge.FirstVertex());
        TVertex* y = findMainParent(&edge.SecondVertex());
        if (x != y) {
            x->Parent() = y;
            answerEdge.AddBack(defaultEdge);
        }
    }
    return answerEdge;
}
*/
#endif // ALGORITHMS_H
