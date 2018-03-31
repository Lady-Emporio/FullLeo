#ifndef CONST_H
#define CONST_H
#include <QColor>
#include <QBrush>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDebug>
#include <string>
#include <QStringList>
enum status{freely,block,wordHere};
enum pos{vertical,horizontal,zero};
enum algTable{fast,full};
#define CONST Const::getConst()
int getStyle(QStringList *,QString ,QString ,int *,int *g,int *b);
class Const{
public:
    int TABLE_ROW(){return TABLE_ROW_;}
    int TABLE_COL(){return TABLE_COL_;}
    int ROWHEIGHT(){return ROWHEIGHT_;}
    int COLUMNWIDTH(){return COLUMNWIDTH_;}
    int MARGIN1(){return MARGIN1_;}
    bool setStyle(QString);
    static Const * getConst();

    void setTABLE_ROW(int x){TABLE_ROW_=x;}
    void setTABLE_COL(int x){TABLE_COL_=x;}
    void setALGORITMH(algTable x){alg_=x;};
    algTable ALGORITMH(){return alg_;};
    void setJUMP(bool x){jump_=x;};
    bool JUMP(){return jump_;};
    void setAUTOCOMPLETION(bool x){autoCompletion_=x;};
    bool AUTOCOMPLETION(){return autoCompletion_;};
    QBrush DEFAULTQB;
    QBrush NOTUSEQB;
    QBrush TRUEQB;
    QBrush FALSEQB;
    QBrush GRIDQB;
    QBrush ACTIVEINTABLEQB;
    QBrush ACTIVELISTQB;
    int COUNT_BUTTOM(){return button_;}
    void setBUTTON(int x){button_=x;}
    void setGRID(bool x){gridTable=x;};
    bool GRID(){return gridTable;};
    bool runAudio;
    QString TRUE_ANSWER_COLOR;
    QString FALSE_ANSWER_COLOR;
    QString DEFAULT_BUTTOM_COLOR;
private:
    bool gridTable;
    int TABLE_ROW_;
    int TABLE_COL_;
    int ROWHEIGHT_;
    int COLUMNWIDTH_;
    int MARGIN1_;
    bool jump_;
    bool autoCompletion_;
    algTable alg_;
    int button_;

    Const();
};
#endif // CONST_H
