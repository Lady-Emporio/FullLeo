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

class Crossword : public QWidget
{
    Q_OBJECT
public:
    explicit Crossword(QWidget *parent = 0);
    QTableWidget *MainTable;
    Table tableWord;
    QLabel *ErrorLabel;
    QListWidget *UsingWordList;
    std::vector<QTableWidgetItem*>LastSelectInMainTable;
    void UpdateMainTable();
    void clearToNextPound();
signals:

public slots:
    void slotUpdate();
private slots:
    void SelectWordRight(int);
};

#endif // CROSSWORD_H
