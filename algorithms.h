#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <QVector>
#include <algorithm>
#include "vertex.h"
#include "edge.h"
#include <set>


namespace MyAlgorithms {
    std::set<TEdge*> algorithmKruskal(const std::vector<TEdge*>& arrEdges);
}

#endif // ALGORITHMS_H
