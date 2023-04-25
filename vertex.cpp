#include "vertex.h"

TVertex::TVertex(QObject *parent) : QObject{parent}, QGraphicsItem() {}

TVertex::~TVertex(){}

void TVertex::SetRect(QRectF rect) {
    //_Rect = rect;
    //_Rect = QRectF(-30,-30,60,60);
}

QRectF TVertex::boundingRect() const {
    return QRectF(-20, -20, 20, 20);
}

void TVertex::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/) {
    painter->setBrush(Qt::black);
    painter->drawEllipse(QRectF(-20, -20, 20, 20));
}

void TVertex::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // qDebug() << "mouseMoveEvent";
    QPointF point = event->pos();
    this->setPos(mapToScene(point));
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





