#include "edge.h"
#include <QtMath>

const int ARROW_ANGLE = 30;
const int ARROW_LEN = 15;

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
    return QRectF(left - ARROW_LEN, bottom - ARROW_LEN, right - left + 2*ARROW_LEN, up - bottom + 2*ARROW_LEN);
}

void TEdge::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/) {
    const QPointF& pointFirst = _FirstVertex->pos();
    const QPointF& pointSecond = _SecondVertex->pos();
    // painter->setPen(QPen(QBrush(QColor(64, 169, 201)), 3));
    painter->setPen(QPen(Qt::black, 2));
    painter->drawLine(pointFirst.x(), pointFirst.y(), pointSecond.x(), pointSecond.y());

    int w = qAbs(pointFirst.x() - pointSecond.x());
    int h = qAbs(pointFirst.y() - pointSecond.y());
    float angelArow = qDegreesToRadians(ARROW_ANGLE);
    float gamma1 = qAcos(w / qSqrt(h*h + w*w)) - angelArow;
    float gamma2 = qDegreesToRadians(90) - qAcos(w / qSqrt(h*h + w*w)) - angelArow;

    float y1 = ARROW_LEN * qSin(gamma1);
    float x1 = ARROW_LEN * qCos(gamma1);
    float x2 = ARROW_LEN * qSin(gamma2);
    float y2 = ARROW_LEN * qCos(gamma2);

    if (pointFirst.x() > pointSecond.x()) { // left
        if (pointFirst.y() > pointSecond.y()) { // up
            x1 *= 1;
            y1 *= 1;
            x2 *= 1;
            y2 *= 1;
        }
        else { // bottom
            x1 *= 1;
            y1 *= -1;
            x2 *= 1;
            y2 *= -1;
        }
    }
    else { // right
        if (pointFirst.y() > pointSecond.y()) { // up
            x1 *= -1;
            y1 *= 1;
            x2 *= -1;
            y2 *= 1;
        }
        else { // bottom
            x1 *= -1;
            y1 *= -1;
            x2 *= -1;
            y2 *= -1;
        }
    }

    painter->drawLine(pointSecond.x() + x1, pointSecond.y() + y1, pointSecond.x(), pointSecond.y());
    painter->drawLine(pointSecond.x() + x2, pointSecond.y() + y2, pointSecond.x(), pointSecond.y());
}

void TEdge::MouseMoveEvent() {
    this->setPos(this->pos().rx() + 0.0001, this->pos().ry() + 0.0001);
}
