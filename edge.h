#ifndef TEDGE_H
#define TEDGE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include "vertex.h"
// #include <QCursor>

class TEdge : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    static const int ARROW_ANGLE;
    static const int ARROW_LEN;

public:
    TEdge(TVertex *firstVertex, TVertex *secondVertex, QObject *parent = nullptr);

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    TVertex* _FirstVertex;
    TVertex* _SecondVertex;

public slots:
    void MouseMoveEvent();
};

#endif // TEDGE_H
