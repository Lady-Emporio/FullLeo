#ifndef RECTDOWN_H
#define RECTDOWN_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QtWidgets>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QPushButton>
#include <QDebug>
#include <string>
class RectDown :public QObject,public QGraphicsRectItem
{
    Q_OBJECT

public:
    std::string m_text;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
          QWidget *widget = 0);
    RectDown();
};

#endif // RECTDOWN_H
