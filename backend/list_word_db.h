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

class ListWordDB : public QWidget
{
    Q_OBJECT
public:
    explicit ListWordDB(QWidget *parent = 0);
private:
    QTableWidget *listinBD;
    QTableWidget *thenSetList;
signals:

public slots:

private slots:
    void connect_IN_bd_trigger(int, int);
    void connect_FROM_NEW_LISR_trigger(int,int);
    void connect_UpdateTable();
};




#endif // LISTWORDDB_H
