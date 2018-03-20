#ifndef CROSSWORD_H
#define CROSSWORD_H
#include <QTableWidget>
#include <QTableWidgetItem>
#include "const.h"
#include "crossword/table.h"
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QKeyEvent>



class TableGui: public QTableWidget{
    Q_OBJECT
public:
    void keyPressEvent(QKeyEvent * event);
};

class Crossword : public QWidget
{
    Q_OBJECT
public:
    explicit Crossword(QWidget *parent = 0);
    TableGui *MainTable;
    Table *tableWord;
    QLabel *ErrorLabel;
    QListWidget *UsingWordList;
    std::vector<QListWidgetItem *>SecectInUsingWordList;
    std::vector<QTableWidgetItem*>LastSelectInMainTable;
    std::vector<QTableWidgetItem *>InMainSelect;
    void UpdateMainTable();
    void clearToNextPound();
signals:

public slots:
    void slotUpdate();
    void SelectWordRight(int);
private slots:
    void SelectCell();
    void verifyAll();
    void seeAll();
};
#endif // CROSSWORD_H
