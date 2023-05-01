#include "graph.h"
#include <unordered_set>
#include <set>
#include <algorithms.h>

TGraph::TGraph(QVector<QVector<double>> matrix)
{
    int n = matrix.size();
    for (int i = 0; i < n; i++) {
        _ArrVertex.push_back(new TVertex(QString::number(i)));
    }

    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            if (matrix[y][x] > 0) {
                _ArrEdge.push_back(new TEdge(_ArrVertex[y], _ArrVertex[x], matrix[y][x]));
            }
        }
    }
}

TGraph::TGraph(int numVertex, int numEdge)
{
    if (numVertex <= 0) {
        throw std::logic_error("Incorrect number of vertices");
    }
    if (numEdge < 0 || numEdge > numVertex * (numVertex-1)) {
        throw std::logic_error("Incorrect number of edges");
    }

    for (int i = 0; i < numVertex; ++i) {
        _ArrVertex.push_back(new TVertex(QString::number(i)));
    }

    std::set<std::pair<int, int>> usedEdges;
    for (int i = 0; i < numEdge; ++i) {
        int rand1 = std::rand() % _ArrVertex.size();
        int rand2 = std::rand() % _ArrVertex.size();
        while (rand1 == rand2 || usedEdges.find({rand1, rand2}) != usedEdges.end()) {
            rand1 = std::rand() % _ArrVertex.size();
            rand2 = std::rand() % _ArrVertex.size();
        }
        usedEdges.insert({rand1, rand2});
        _ArrEdge.push_back(new TEdge(_ArrVertex[rand1], _ArrVertex[rand2]));
    }
}

TGraph::~TGraph()
{
    for (auto& vertex : _ArrVertex) {
        delete vertex;
    }
    for (auto& edge : _ArrEdge) {
        delete edge;
    }
}

void TGraph::AddToScene(QGraphicsScene* scene) {
    for (auto& vertex : _ArrVertex) {
        scene->addItem(vertex);
    }
    for (auto& edge : _ArrEdge) {
        scene->addItem(edge);
    }
}

void TGraph::UseKruskal()
{
    std::set<TEdge*> newArrEdge = MyAlgorithms::algorithmKruskal(_ArrEdge);
    std::vector<TEdge*> res;

    for (auto it = _ArrEdge.begin(); it != _ArrEdge.end(); it++) {
        if (newArrEdge.find(*it) == newArrEdge.end()) {
            delete *it;
            continue;
        }
        res.push_back(*it);
    }

    _ArrEdge = res;
}

void TGraph::ArrangeCircle(float radius, int screenWidth, int screenHeight)
{
    float angelStep = 360.0 / _ArrVertex.size();
    float angel = 0;
    int quarter = 0;
    for (int i = 0; i < (int)_ArrVertex.size(); i++) {
        while (angel >= 90) {
            angel -= 90;
            quarter++;
        }

        int curAngel = angel;
        int xSign = 1, ySign = 1;
        if (quarter == 0) {
            xSign *= -1;
        }
        if (quarter == 1) {
            ySign *= -1;
            xSign *= -1;
            curAngel = 90 - curAngel;
        }
        if (quarter == 2) {
            ySign *= -1;
        }
        if (quarter == 3) {
            curAngel = 90 - curAngel;
        }
        float x = xSign * radius * qSin(qDegreesToRadians(curAngel)) + screenWidth/2;
        float y = ySign * radius * qCos(qDegreesToRadians(curAngel)) + screenHeight/2;
        _ArrVertex[i]->setPos(x, y);

        angel += angelStep;
    }
}
