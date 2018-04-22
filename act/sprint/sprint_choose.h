#ifndef SPRINTCHOOSE_H
#define SPRINTCHOOSE_H

#include <QWidget>
#include "backend/leo_const.h"

class SprintChoose : public QWidget
{
    Q_OBJECT
public:
    explicit SprintChoose(QWidget *parent = 0);

signals:

public slots:
    void onAnimationFinished();
};

#endif // SPRINTCHOOSE_H
