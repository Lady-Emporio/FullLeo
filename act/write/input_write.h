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
    enum Type{common,random,sortZ_A,sortA_Z};
    QLabel *TrueLabel;
    Word TrueWord;
    explicit InputWrite(QWidget *parent = 0,Type =common);
    Type type_this;
    TableWrite *inputTable;
    std::vector<Word> ListWord;
    std::vector<Word> EverWordList;
    void run();
signals:

public slots:
    void connectNextRound_trigger();
};

class OneTableOneRow: public QTableWidget{
    Q_OBJECT
public:
    QString TrueWord;
    OneTableOneRow(QWidget *parent = 0);
    int beginTableWord;
    void keyPressEvent(QKeyEvent * event);
signals:
    void singal_needNexRound();
};
class OneLongRowTable : public QWidget
{
    Q_OBJECT
public:
    explicit OneLongRowTable(QWidget *parent = 0,InputWrite::Type =InputWrite::Type::common);
    InputWrite::Type type_this;
    QLabel *TrueLabel;
    Word TrueWord;
    OneTableOneRow *inputTable;
    std::vector<Word> ListWord;
    std::vector<Word> EverWordList;
public slots:
    void connectNextRound_trigger();
};
#endif // INPUTWRITE_H
