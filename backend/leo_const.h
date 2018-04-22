#ifndef LEOCONST_H
#define LEOCONST_H
#include <QString>
#include "vector"
#include "word.h"
#include <QColor>
#include <QBrush>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMediaPlayer>
#include <QDir>
#include <QMap>
#include <QObject>
#include <QMessageBox>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
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
#include <QMainWindow>
#include <QMdiArea>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include "QMdiSubWindow"
enum status{freely,block,wordHere};
namespace Leo{
enum pos{vertical,horizontal,zero};
enum Type{common,random,sortZ_A,sortA_Z,contra_Vice_versa};
}
enum algTable{fast,full};
void setFontToWidget(QWidget * x);

class LeoConst
{
public:
    static LeoConst *  CONST();//one leo-static leo
    std::vector<Word> ListWithWordConst;
    void GetFromBD();
    void printAllWordInBD(QString);
    void fallbackAllWordInBD(QString);
    QMap<QString,QMap<QString,QBrush> > AllStyleMap;
    QMap<QString,QBrush> AllQBrushdictPARAMS;
    QMap<QString,int> All_INT_PARAMS;
    QMap<QString,QString> All_QString_PARAMS;
    QMap<QString,bool> All_BOOL_PARAMS;
    void setStyle(QString);

    algTable ALGORITMH;
    QMediaPlayer * player;

    void getMainRootJson();
    void FromRootQBrush();
    void FromRootINT();
    void FromRootBOOL();
    void fillActiveStyleAndListStyle();
    void FromRootString();
    void THIS_IS_ALL_UPDATE_fromfileAndBD();
    QJsonObject root;
    QStringList ListStyle;
private:
    LeoConst();
};

#endif // LEOCONST_H
