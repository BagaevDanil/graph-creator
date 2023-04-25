#include "graph.h"

TGraph::TGraph(QString /*pathMatrix*/)
{
    /*
     * TODO:
     * 1) Реализовать чтение матрицы с текстового файла
     */
}

TGraph::TGraph(int numVertex, int numEdge)
{
    if (numVertex < 0) {
        throw std::logic_error("Incorrect number of vertices");
    }
    if (numEdge < 0 || numEdge > numVertex * (numVertex-1) / 2) {
        throw std::logic_error("Incorrect number of edges");
    }

    for (int i = 0; i < numVertex; ++i) {
        _ArrVertex.push_back(new TVertex(QString::number(i + 1)));
    }

    for (int i = 0; i < numVertex; ++i) {
        int rand1 = std::rand() % _ArrVertex.size();
        int rand2 = std::rand() % _ArrVertex.size();
        while (rand1 == rand2) {
            rand2 = std::rand() % _ArrVertex.size();
        }
        _ArrEdge.push_back(new TEdge(_ArrVertex[rand1], _ArrVertex[rand2]));
    }
}

void TGraph::ArrangeCircle()
{

}
