#include "edge.h"
#include <QtMath>

const int TEdge::ARROW_ANGLE = 30;
const int TEdge::ARROW_LEN = 15;
const int TEdge::INDENTATION = 15;

TEdge::TEdge(TVertex *firstVertex, TVertex *secondVertex, QObject *parent) : QObject{parent}, _FirstVertex(firstVertex), _SecondVertex(secondVertex)
{
    connect(_FirstVertex, SIGNAL(MoveVertex()), this, SLOT(MouseMoveEvent()));
    connect(_SecondVertex, SIGNAL(MoveVertex()), this, SLOT(MouseMoveEvent()));
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

    painter->setPen(QPen(Qt::black, 1.7));

    int edgeW = qAbs(pointFirst.x() - pointSecond.x());
    int edgeH = qAbs(pointFirst.y() - pointSecond.y());

    float gamma = qAcos(edgeW / qSqrt(edgeH*edgeH + edgeW*edgeW));
    float indentationX = INDENTATION * qCos(gamma);
    float indentationY = INDENTATION * qSin(gamma);
    QPointF pointFirstCorrected = pointFirst;
    QPointF pointSecondCorrected = pointSecond;

    float gamma1 = qAcos(edgeW / qSqrt(edgeH*edgeH + edgeW*edgeW)) - qDegreesToRadians(ARROW_ANGLE);
    float arrowY1 = ARROW_LEN * qSin(gamma1);
    float arrowX1 = ARROW_LEN * qCos(gamma1);

    float gamma2 = qDegreesToRadians(90) - qAcos(edgeW / qSqrt(edgeH*edgeH + edgeW*edgeW)) - qDegreesToRadians(ARROW_ANGLE);
    float arrowX2 = ARROW_LEN * qSin(gamma2);
    float arrowY2 = ARROW_LEN * qCos(gamma2);

    if (pointFirst.x() > pointSecond.x()) {
        if (pointFirst.y() > pointSecond.y()) { // II quarter
            pointFirstCorrected.rx() -= indentationX;
            pointFirstCorrected.ry() -= indentationY;
            pointSecondCorrected.rx() += indentationX;
            pointSecondCorrected.ry() += indentationY;

            arrowX1 *= -1;
            arrowY1 *= -1;
            arrowX2 *= -1;
            arrowY2 *= -1;
        }
        else { // III quarters
            pointFirstCorrected.rx() -= indentationX;
            pointFirstCorrected.ry() += indentationY;
            pointSecondCorrected.rx() += indentationX;
            pointSecondCorrected.ry() -= indentationY;

            arrowX1 *= -1;
            arrowY1 *= 1;
            arrowX2 *= -1;
            arrowY2 *= 1;
        }
    }
    else {
        if (pointFirst.y() > pointSecond.y()) { // I quarters
            pointFirstCorrected.rx() += indentationX;
            pointFirstCorrected.ry() -= indentationY;
            pointSecondCorrected.rx() -= indentationX;
            pointSecondCorrected.ry() += indentationY;

            arrowX1 *= 1;
            arrowY1 *= -1;
            arrowX2 *= 1;
            arrowY2 *= -1;
        }
        else { // IV quarters
            pointFirstCorrected.rx() += indentationX;
            pointFirstCorrected.ry() += indentationY;
            pointSecondCorrected.rx() -= indentationX;
            pointSecondCorrected.ry() -= indentationY;

            arrowX1 *= 1;
            arrowY1 *= 1;
            arrowX2 *= 1;
            arrowY2 *= 1;
        }
    }

    painter->drawLine(pointFirstCorrected.x(), pointFirstCorrected.y(), pointSecondCorrected.x(), pointSecondCorrected.y());
    painter->drawLine(pointFirstCorrected.x() + arrowX1, pointFirstCorrected.y() + arrowY1, pointFirstCorrected.x(), pointFirstCorrected.y());
    painter->drawLine(pointFirstCorrected.x() + arrowX2, pointFirstCorrected.y() + arrowY2, pointFirstCorrected.x(), pointFirstCorrected.y());
}

void TEdge::MouseMoveEvent() {
    /*
     * TODO:
     * 1) Костыль на коленке.
     *    Научиться обновлять(перерисовывать) объект вслед за вершинами.
     */

    this->setPos(this->pos().rx() + 0.0001, this->pos().ry() + 0.0001);
}
