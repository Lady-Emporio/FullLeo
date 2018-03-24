#include "const.h"
Const * Const::getConst(){
    static Const *s=new Const;
    return s;
}

Const::Const(){
    alg_=fast;
    jump_=false;
    autoCompletion_=false;
    this->setSize();

}
void Const::setSize(styleWindow x){
    switch(x){
        case defaults:
            TABLE_ROW_=40;
            TABLE_COL_=40;
            ROWHEIGHT_=20;
            COLUMNWIDTH_=20;
            MARGIN1_=65;
            break;
        case low:
            TABLE_ROW_=10;
            TABLE_COL_=10;
            ROWHEIGHT_=20;
            COLUMNWIDTH_=20;
            MARGIN1_=65;
            break;
    };
}
