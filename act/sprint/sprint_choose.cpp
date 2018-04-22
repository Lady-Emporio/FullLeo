#include "sprint_choose.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimeLine>
#include <QGraphicsItemAnimation>
#include <QGraphicsRectItem>

SprintChoose::SprintChoose(QWidget *parent) : QWidget(parent)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    QHBoxLayout *mainLayout=new QHBoxLayout(this);
    QGraphicsView *view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(40,300);
    scene->setSceneRect(0,0,40,300);
    mainLayout->addWidget(view);

    QGraphicsRectItem *zeroItemToGoodPosAndVisibleEnemyThisIsHideNotUse=new QGraphicsRectItem;
    scene->addItem(zeroItemToGoodPosAndVisibleEnemyThisIsHideNotUse);
//    zeroItemToGoodPosAndVisibleEnemyThisIsHideNotUse->setRect(0,0,20,20);
//    zeroItemToGoodPosAndVisibleEnemyThisIsHideNotUse->setBrush(QBrush(QColor(255, 0, 0)));
//    zeroItemToGoodPosAndVisibleEnemyThisIsHideNotUse->setPos(0,100);

    QGraphicsRectItem *m_actor=new QGraphicsRectItem;
    scene->addItem(m_actor);
    m_actor->setRect(0,0,20,20);
    m_actor->setBrush(QBrush(QColor(0, 255, 0)));
    m_actor->setPos(0,0);

    QPointF eventPos(0,scene->height()-m_actor->rect().height());
    QTimeLine *timer = new QTimeLine(5000, this);
    QGraphicsItemAnimation *animation = new QGraphicsItemAnimation(timer);

    animation->setItem(m_actor);
    animation->setTimeLine(timer);
    animation->setPosAt(1.0, eventPos);
    timer->start();
    connect(timer, SIGNAL(finished()), SLOT(onAnimationFinished()));
}
void SprintChoose::onAnimationFinished(){
    sender()->deleteLater();
}
