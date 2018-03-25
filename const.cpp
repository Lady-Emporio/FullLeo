#include "const.h"
Const * Const::getConst(){
    static Const *s=new Const;
    return s;
}

Const::Const(){
    alg_=fast;
    jump_=false;
    autoCompletion_=false;
    TABLE_ROW_=40;
    TABLE_COL_=40;
    ROWHEIGHT_=20;
    COLUMNWIDTH_=20;
    MARGIN1_=65;
    gridTable=true;
    setStyle(defaults);

}
void Const::setStyle(styleWindow x){
    switch(x){
        case defaults:
            DEFAULTQB=QBrush(QColor(255, 255, 255));
            NOTUSEQB=QBrush(QColor(0, 255, 255));
            TRUEQB=QBrush(QColor(255, 140, 0));
            FALSEQB=QBrush(QColor(219, 112, 147));
            GRIDQB=QBrush(QColor(255, 0, 0));
            ACTIVEINTABLEQB=QBrush(QColor(0, 255, 0));
            ACTIVELISTQB=QBrush(QColor(128, 128, 128));
            break;
        case low:
            DEFAULTQB=QBrush(QColor(255, 255, 255));
            NOTUSEQB=QBrush(QColor(100, 100, 100));
            TRUEQB=QBrush(QColor(120,219,226));
            FALSEQB=QBrush(QColor(229,43,80));
            GRIDQB=QBrush(QColor(100, 100, 100));
            ACTIVEINTABLEQB=QBrush(QColor(204,204,255));
            ACTIVELISTQB=QBrush(QColor(255, 0, 0));
            break;
        case as1C:
            DEFAULTQB=QBrush(QColor(255, 255, 255));
            NOTUSEQB=QBrush(QColor(179,172,134));
            TRUEQB=QBrush(QColor(244,236,197));
            FALSEQB=QBrush(QColor(255,0,0));
            GRIDQB=QBrush(QColor(179,172,134));
            ACTIVEINTABLEQB=QBrush(QColor(255, 250, 217));
            ACTIVELISTQB=QBrush(QColor(245,242,221));
            break;
        case dark:
            DEFAULTQB=QBrush(QColor(255, 255, 255));
            NOTUSEQB=QBrush(QColor(0, 0, 0));
            TRUEQB=QBrush(QColor(0, 0, 255));
            FALSEQB=QBrush(QColor(255, 0, 0));
            GRIDQB=QBrush(QColor(0, 0, 0));
            ACTIVEINTABLEQB=QBrush(QColor(0, 255, 0));
            ACTIVELISTQB=QBrush(QColor(128, 128, 128));
            break;
    };
}
