#ifndef ERRORCOUNT_H
#define ERRORCOUNT_H
#include "backend/word.h"
#include "backend/leo_const.h"

class ErrorCount : public QWidget
{
    Q_OBJECT
public:
    QTableView *view;
    explicit ErrorCount(QWidget *parent = 0);
    static void addToDB(Word);
    void selectAll();
    std::vector<QMap<QString,QString> > AllErrorString;
    QSqlTableModel *model;
    QSqlDatabase db;
    bool startIf;
signals:

public slots:
    void connectUpdate_trigger();
    void connectAccept_changes_trigger();
    void slotCustomMenuRequested(QPoint);
    void slotRemoveRecord();
};

#endif // ERRORCOUNT_H
