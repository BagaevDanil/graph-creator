#ifndef TVERTEX_H
#define TVERTEX_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

class TVertex : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit TVertex(QObject *parent = nullptr);
    ~TVertex();

signals:
    void ClickVertex();
    void MoveVertex();

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QRectF _Rect;

};

#endif // TVERTEX_H
