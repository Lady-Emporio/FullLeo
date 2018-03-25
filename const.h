#ifndef CONST_H
#define CONST_H
#include <QColor>
#include <QBrush>
enum status{freely,block,wordHere};
enum pos{vertical,horizontal,zero};
enum algTable{fast,full};
enum styleWindow{defaults,as1C,low,dark};
#define CONST Const::getConst()
class Const{
public:
    int TABLE_ROW(){return TABLE_ROW_;}
    int TABLE_COL(){return TABLE_COL_;}
    int ROWHEIGHT(){return ROWHEIGHT_;}
    int COLUMNWIDTH(){return COLUMNWIDTH_;}
    int MARGIN1(){return MARGIN1_;}
    void setStyle(styleWindow);
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

    void setGRID(bool x){gridTable=x;};
    bool GRID(){return gridTable;};
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

    Const();
};
#endif // CONST_H
