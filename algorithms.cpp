#include "algorithms.h"

struct TKruskalVertex {
    TKruskalVertex* Parent;
};

struct TKruskalEdge {
    TKruskalVertex* FirstVertex;
    TKruskalVertex* SecondVertex;
    TEdge* origanlEdge;
};

TKruskalVertex* findMainParent(TKruskalVertex* vertex)
{
    if (vertex->Parent != nullptr) {
        vertex->Parent = findMainParent(vertex->Parent);
    }

    if (vertex->Parent) {
        return vertex->Parent;
    }
    return vertex;
}

std::set<TEdge*> MyAlgorithms::algorithmKruskal(const std::vector<TEdge*>& arrEdges)
{
    std::vector<TKruskalEdge> edges;
    std::map<QString, TKruskalVertex> mapVertex;

    for (auto& edge : arrEdges) {
        auto* first = edge->FirstVertex();
        auto* second = edge->SecondVertex();

        if (mapVertex.find(first->Name()) == mapVertex.end()) {
            mapVertex[first->Name()] = TKruskalVertex{nullptr};
        }
        if (mapVertex.find(second->Name()) == mapVertex.end()) {
            mapVertex[second->Name()] = TKruskalVertex{nullptr};
        }
        edges.push_back({&mapVertex[first->Name()], &mapVertex[second->Name()], edge});
    }

    std::sort(edges.begin(), edges.end(), [](TKruskalEdge& a, TKruskalEdge& b){
        return a.origanlEdge->Weight() < b.origanlEdge->Weight();
    });
    QVector<TKruskalEdge> answerEdge;

    for (auto& edge : edges) {
        TKruskalVertex* x = findMainParent(edge.FirstVertex);
        TKruskalVertex* y = findMainParent(edge.SecondVertex);
        if (x != y) {
            x->Parent = y;
            answerEdge.push_back(edge);
        }
    }

    std::set<TEdge*> ans;
    for (auto& edge : answerEdge) {
        ans.insert(edge.origanlEdge);
    }
    return ans;
}
