#include "up_down.h"

UpDown::UpDown(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *mainLayout=new QHBoxLayout(this);
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(400,600);
    RectDown*downWord=new RectDown;
//    downWord->setPos(view->width()/2,0);
    downWord->setPos(0,0);
    scene->addItem(downWord);
    mainLayout->addWidget(view);
    this->setLayout(mainLayout);
}
