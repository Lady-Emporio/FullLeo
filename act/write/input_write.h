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
    Word TrueWordWORD;
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
    explicit InputWrite(QWidget *parent = 0,Leo::Type =Leo::common);
    Leo::Type type_this;
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
    Word TrueWordWORD;
    Leo::Type type_this;
    OneTableOneRow(QWidget *parent = 0);
    int beginTableWord;
    void keyPressEvent(QKeyEvent * event);
signals:
    void singal_needNexRound();
    void singal_nextWord();
};

class OneLongRowTable : public QWidget
{
    Q_OBJECT
public:
    explicit OneLongRowTable(QWidget *parent = 0,Leo::Type =Leo::Type::common);
    Leo::Type type_this;
    QLabel *TrueLabel;
    QLabel *RoundLabel;
    QLabel *NomberLabel;
    Word TrueWord;
    OneTableOneRow *inputTable;
    std::vector<Word> ListWord;
    std::vector<Word> EverWordList;
public slots:
    void connectNextRound_trigger();
    void connectNext_Word_trigger();
};
#endif // INPUTWRITE_H
