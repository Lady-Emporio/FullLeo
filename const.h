#ifndef CONST_H
#define CONST_H
#include <QColor>
#include <QBrush>
enum styleWindow{defaults,as1C,low};
#define CONST Const::getConst()
class Const{
public:
    int TABLE_ROW(){return TABLE_ROW_;}
    int TABLE_COL(){return TABLE_COL_;}
    int ROWHEIGHT(){return ROWHEIGHT_;}
    int COLUMNWIDTH(){return COLUMNWIDTH_;}
    int MARGIN1(){return MARGIN1_;}
    void setSize(styleWindow x=defaults);
    void setStyle();
    static Const * getConst();
private:
    int TABLE_ROW_;
    int TABLE_COL_;
    int ROWHEIGHT_;
    int COLUMNWIDTH_;
    int MARGIN1_;
    QBrush const DEFAULTQB;
    QBrush const NOTUSEQB;
    QBrush const TRUEQB;
    QBrush const FALSEQB;
    QBrush const GRIDQB;
    QBrush const ACTIVEINTABLEQB;
    QBrush const ACTIVELISTQB;
    Const();
};
enum status{freely,block,wordHere};
enum pos{vertical,horizontal,zero};


QBrush const DEFAULTQB=QBrush(QColor(255, 255, 255));
QBrush const NOTUSEQB=QBrush(QColor(0, 255, 255));
QBrush const TRUEQB=QBrush(QColor(255, 140, 0));
QBrush const FALSEQB=QBrush(QColor(219, 112, 147));
QBrush const GRIDQB=QBrush(QColor(255, 0, 0));
QBrush const ACTIVEINTABLEQB=QBrush(QColor(0, 255, 0));
QBrush const ACTIVELISTQB=QBrush(QColor(128, 128, 128));
#endif // CONST_H
