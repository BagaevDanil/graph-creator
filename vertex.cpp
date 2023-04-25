#include "vertex.h"
#include <QColor>

const int FONT_SIZE = 10;

TVertex::TVertex(QString name, QObject *parent) : QObject{parent}, _Name(name), _Rect(QRectF(-10, -10, 20, 20)) {}

TVertex::~TVertex(){}

QRectF TVertex::boundingRect() const {
    return _Rect;
}

void TVertex::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/) {
    painter->setBrush(QBrush(QColor(64, 169, 201)));
    painter->drawEllipse(_Rect);
    painter->setFont(QFont("times", FONT_SIZE));
    // painter->drawText(QPointF((_Rect.left() + _Rect.center().x())/2, (_Rect.bottom() + _Rect.center().y())/2), "25");
    painter->drawText(_Rect, _Name);
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





