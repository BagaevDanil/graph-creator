#include "vertex.h"
#include <QColor>

const int TVertex::FONT_SIZE = 11;
const int TVertex::VERTEX_RADIUS = 30;

TVertex::TVertex(QString name, QObject *parent)
    : QObject{parent}
    , _Name(name)
    , _Rect(QRectF(-VERTEX_RADIUS/2, -VERTEX_RADIUS/2, VERTEX_RADIUS, VERTEX_RADIUS)) {}

TVertex::~TVertex(){}

QRectF TVertex::boundingRect() const {
    return _Rect;
}

void TVertex::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
    painter->setBrush(QBrush(QColor(64, 169, 201)));
    painter->drawEllipse(_Rect);

    painter->setFont(QFont("times", FONT_SIZE));
    int labelSizeX = FONT_SIZE * 4/3 * 3/5 * _Name.length();
    int labelSizeY = FONT_SIZE * 4/3;
    painter->drawText(QPointF(0 - labelSizeX/2, 0 + labelSizeY/2), _Name);
}

void TVertex::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QPointF point = event->pos();
    this->setPos(mapToScene(point));
    QGraphicsItem::mouseMoveEvent(event);
}

void TVertex::mousePressEvent(QGraphicsSceneMouseEvent* /*event*/)
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
}

void TVertex::mouseReleaseEvent(QGraphicsSceneMouseEvent* /*event*/)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
}

const QString& TVertex::Name() const {
    return _Name;
}




