#include "edge.h"
#include <QtMath>

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
    return QRectF(left - 40, bottom - 40, right - left + 40, up - bottom + 40); // ToDo : alias 10 - move to center in Vertex = r
}

void TEdge::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/) {
    const QPointF& pointFirst = _FirstVertex->pos();
    const QPointF& pointSecond = _SecondVertex->pos();
    // painter->setPen(QPen(QBrush(QColor(64, 169, 201)), 3));
    painter->setPen(QPen(Qt::black, 3));
    painter->drawLine(pointFirst.x() - 10, pointFirst.y() - 10, pointSecond.x() - 10, pointSecond.y() - 10);

    int w = qAbs(pointFirst.x() - pointSecond.x());
    int h = qAbs(pointFirst.y() - pointSecond.y());
    float angelArow = qDegreesToRadians(30);
    float gamma1 = qAcos(w / qSqrt(h*h + w*w)) - angelArow;
    float gamma2 = qDegreesToRadians(90) - qAcos(w / qSqrt(h*h + w*w)) - angelArow;

    float y1 = 20 * qSin(gamma1);
    float x1 = 20 * qCos(gamma1);
    float x2 = 20 * qSin(gamma2);
    float y2 = 20 * qCos(gamma2);

    if (pointFirst.x() > pointSecond.x()) { // left
        if (pointFirst.y() > pointSecond.y()) { // up
            painter->drawLine(pointSecond.x() - 10 + x1, pointSecond.y() - 10 + y1, pointSecond.x() - 10, pointSecond.y() - 10);
            painter->drawLine(pointSecond.x() - 10 + x2, pointSecond.y() - 10 + y2, pointSecond.x() - 10, pointSecond.y() - 10);
        }
        else { // bottom
            painter->drawLine(pointSecond.x() - 10 + x1, pointSecond.y() - 10 - y1, pointSecond.x() - 10, pointSecond.y() - 10);
            painter->drawLine(pointSecond.x() - 10 + x2, pointSecond.y() - 10 - y2, pointSecond.x() - 10, pointSecond.y() - 10);
        }
    }
    else { // right
        if (pointFirst.y() > pointSecond.y()) { // up
            painter->drawLine(pointSecond.x() - 10 - x1, pointSecond.y() - 10 + y1, pointSecond.x() - 10, pointSecond.y() - 10);
            painter->drawLine(pointSecond.x() - 10 - x2, pointSecond.y() - 10 + y2, pointSecond.x() - 10, pointSecond.y() - 10);
        }
        else { // bottom
            painter->drawLine(pointSecond.x() - 10 - x1, pointSecond.y() - 10 - y1, pointSecond.x() - 10, pointSecond.y() - 10);
            painter->drawLine(pointSecond.x() - 10 - x2, pointSecond.y() - 10 - y2, pointSecond.x() - 10, pointSecond.y() - 10);
        }
    }
}

void TEdge::MouseMoveEvent() {
    this->setPos(this->pos().rx() + 0.0001, this->pos().ry() + 0.0001);
}
