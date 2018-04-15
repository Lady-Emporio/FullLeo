#ifndef ERRORCOUNT_H
#define ERRORCOUNT_H
#include <QComboBox>
#include <QWidget>
#include <QLabel>
#include <QEvent>
#include <QCloseEvent>
#include <QLineEdit>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDebug>
#include <QStringList>
#include <QPushButton>
#include <QRadioButton>
#include <QGroupBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QListWidget>
#include "backend/word.h"
#include "backend/leo_const.h"
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QString>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTableWidget>
#include <QLineEdit>
#include <QSqlError>
#include <QHeaderView>
#include <QSqlTableModel>
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
    static QSqlDatabase db;
    bool startIf;
signals:

public slots:
    void connectUpdate_trigger();
    void connectAccept_changes_trigger();
};

#endif // ERRORCOUNT_H
