#include "vertex.h"
#include <QColor>

TVertex::TVertex(QObject *parent) : QObject{parent}, QGraphicsItem(), _Rect(QRectF(-10, -10, 20, 20)) {}

TVertex::~TVertex(){}

QRectF TVertex::boundingRect() const {
    return _Rect;
}

void TVertex::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/) {
    painter->setBrush(QBrush(QColor(64, 169, 201)));
    painter->drawEllipse(_Rect);
}

void TVertex::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    emit MoveVertex();
    QPointF point = event->pos();
    this->setPos(mapToScene(point));
    QGraphicsItem::mouseMoveEvent(event);
}

void TVertex::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void TVertex::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}





