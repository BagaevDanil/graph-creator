#include "edge.h"

TEdge::TEdge(TVertex *firstVertex, TVertex *secondVertex, QObject *parent) : QObject{parent}, _FirstVertex(firstVertex), _SecondVertex(secondVertex)
{
    connect(_FirstVertex,SIGNAL(MoveVertex()),this,SLOT(MouseMoveEvent()));
    connect(_SecondVertex,SIGNAL(MoveVertex()),this,SLOT(MouseMoveEvent()));
}

QRectF TEdge::boundingRect() const {
    int left = fmin(_FirstVertex->pos().x(), _SecondVertex->pos().x());
    int right = fmax(_FirstVertex->pos().x(), _SecondVertex->pos().x());
    int bottom = fmin(_FirstVertex->pos().y(), _SecondVertex->pos().y());
    int up = fmax(_FirstVertex->pos().y(), _SecondVertex->pos().y());
    return QRectF(left - 10, bottom - 10, right - left + 10, up - bottom + 10); // ToDo : alias 10 - move to center in Vertex = r
}

void TEdge::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/) {
    const QPointF& pointFirst = _FirstVertex->pos();
    const QPointF& pointSecond = _SecondVertex->pos();
    // painter->setPen(QPen(QBrush(QColor(64, 169, 201)), 3));
    painter->setPen(QPen(Qt::black, 3));
    painter->drawLine(pointFirst.x() - 10, pointFirst.y() - 10, pointSecond.x() - 10, pointSecond.y() - 10);
}

void TEdge::MouseMoveEvent() {
    this->setPos(this->pos().rx() + 0.0001, this->pos().ry() + 0.0001);
}
