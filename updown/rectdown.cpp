#include "rectdown.h"

RectDown::RectDown()
{
        this->setRect(0,0,20,60);
//       this->setFlag(QGraphicsItem::ItemIsFocusable); //https://doc.qt.io/qt-5.10/qgraphicsitem.html#GraphicsItemFlag-enum
//       this->setFocus();
       this->setBrush(QBrush(QColor(10, 100, 10)));
//       QTimer * timer = new QTimer();
//       connect(timer,SIGNAL(timeout()),this,SLOT(move()));
//       timer->start( (ONE_SEC_ms/FPS));
        m_text="We are";
}

void RectDown::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                        QWidget *widget)
{
  QPointF pos = QPointF(rect().x() + 10, rect().y() + 20);
  painter->drawText(pos, m_text.c_str());
  painter->setPen(QPen(Qt::black, 1));
  painter->drawRoundRect(rect());
}
