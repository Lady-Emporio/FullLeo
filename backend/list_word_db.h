#ifndef LISTWORDDB_H
#define LISTWORDDB_H
#include "leo_const.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QString>
#include <QMessageBox>
#include <QLabel>
#include <QTableWidget>
#include <QLineEdit>
class ListWordDB : public QWidget
{
    Q_OBJECT
public:
    explicit ListWordDB(QWidget *parent = 0);
private:
    QLineEdit *findWord;
    QTableWidget *finderTable;
    QTableWidget *listinBD;
    QTableWidget *thenSetList;
signals:

public slots:

private slots:
    void connect_IN_bd_trigger(int, int);
    void connect_FROM_NEW_LISR_trigger(int,int);
    void connect_UpdateTable();
    void connect_TextChanged_FindWord(const QString &currentText);
    void connect_FROM_FINDER_trigger(int, int);
};




#endif // LISTWORDDB_H
