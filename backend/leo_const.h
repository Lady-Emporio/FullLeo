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
enum status{freely,block,wordHere};
enum pos{vertical,horizontal,zero};
enum algTable{fast,full};
void setFontToWidget(QWidget * x);
int getConstParam(QString ,QString &);
int getStyle(QStringList * ListStyle,QString style,QString subStyl,int *r,int *g,int *b,QString &Error);
class LeoConst
{
public:
    static LeoConst *  CONST();//one leo-static leo
    int getFromDB;
    int FONT_SIZE;
    QString fontFamyle;
    QString path_bd;
    std::vector<Word> ListWithWordConst;
    void GetFromBD();
    QBrush DEFAULTQB;
    QBrush NOTUSEQB;
    QBrush TRUEQB;
    QBrush FALSEQB;
    QBrush GRIDQB;
    QBrush ACTIVEINTABLEQB;
    QBrush ACTIVELISTQB;
    QBrush WRITECELL;
    bool setStyle(QString x,QString &);
    int TABLE_ROW;
    int TABLE_COL;
    int ROWHEIGHT;
    int COLUMNWIDTH;
    int MARGIN1;
    algTable ALGORITMH;
    bool JUMP;
    bool AUTOCOMPLETION;
    bool GRID;
    QString TRUE_ANSWER_COLOR;
    QString FALSE_ANSWER_COLOR;
    QString DEFAULT_BUTTOM_COLOR;
    int COUNT_BUTTOM;
    bool runAudio;
    bool runImage;
    static QMediaPlayer * player;
private:
    LeoConst();
};

#endif // LEOCONST_H
