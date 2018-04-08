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
enum status{freely,block,wordHere};
enum pos{vertical,horizontal,zero};
enum algTable{fast,full};
void setFontToWidget(QWidget * x);

class LeoConst
{
public:
    static LeoConst *  CONST();//one leo-static leo
    std::vector<Word> ListWithWordConst;
    void GetFromBD();
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
    QString ActiveStyle;
private:
    LeoConst();
};

#endif // LEOCONST_H
