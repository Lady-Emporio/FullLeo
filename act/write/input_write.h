#ifndef INPUTWRITE_H
#define INPUTWRITE_H
#include <QMediaPlayer>
#include <QWidget>
#include <QTableWidget>
#include "backend/word.h"
#include "backend/leo_const.h"
#include <QLabel>
class TableWrite: public QTableWidget{
    Q_OBJECT
public:
    QString TrueWord;
    TableWrite(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent * event);
    void resizeEvent(QResizeEvent *event);
signals:
    void singal_needNexRound();
};

class InputWrite : public QWidget
{
    Q_OBJECT
public:
    QLabel *TrueLabel;
    Word TrueWord;
    explicit InputWrite(QWidget *parent = 0);
    TableWrite *inputTable;
    std::vector<Word> ListWord;
    static QMediaPlayer *player;
    void run();
signals:

public slots:
    void connectNextRound_trigger();
};

#endif // INPUTWRITE_H
