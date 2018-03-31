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
    button_=4;
    runAudio=false;
    setStyle("defaults");
    TRUE_ANSWER_COLOR="Button {\
            background-color: rgb(0, 200, 0);\
            border: 4px solid red;\
            border-radius: 5px;\
       }";
    FALSE_ANSWER_COLOR="Button {\
            background-color: rgb(255, 0, 0);\
            border: 4px solid red;\
            border-radius: 5px;\
       }";
    DEFAULT_BUTTOM_COLOR="Button:pressed{\
            background-color: rgb(0, 0, 255);\
        }\
        Button {\
             background-color: rgb(170, 170, 127);\
             border: 4px solid red;\
             border-radius: 5px;\
        }";
}
bool Const::setStyle(QString x){
    QStringList NotUseListBadArchitectureAppForRunFunc;
    int r,g,b,sum=0;
    if(getStyle(&NotUseListBadArchitectureAppForRunFunc,x,"DEFAULTQB",&r,&g,&b)==0){
        DEFAULTQB=QBrush(QColor(r, g, b));
    }
    else{
        DEFAULTQB=QBrush(QColor(255, 255, 255));
        ++sum;
    }
    if(getStyle(&NotUseListBadArchitectureAppForRunFunc,x,"NOTUSEQB",&r,&g,&b)==0){
        NOTUSEQB=QBrush(QColor(r, g, b));
    }
    else{
        NOTUSEQB=QBrush(QColor(0, 255, 255));
        ++sum;
    }
    if(getStyle(&NotUseListBadArchitectureAppForRunFunc,x,"TRUEQB",&r,&g,&b)==0){
        TRUEQB=QBrush(QColor(r, g, b));
    }
    else{
        TRUEQB=QBrush(QColor(255, 140, 0));
        ++sum;
    }
    if(getStyle(&NotUseListBadArchitectureAppForRunFunc,x,"FALSEQB",&r,&g,&b)==0){
        FALSEQB=QBrush(QColor(r, g, b));
    }
    else{
        FALSEQB=QBrush(QColor(219, 112, 147));
        ++sum;
    }
    if(getStyle(&NotUseListBadArchitectureAppForRunFunc,x,"GRIDQB",&r,&g,&b)==0){
        GRIDQB=QBrush(QColor(r, g, b));
    }
    else{
        GRIDQB=QBrush(QColor(255, 0, 0));
        ++sum;
    }
    if(getStyle(&NotUseListBadArchitectureAppForRunFunc,x,"ACTIVEINTABLEQB",&r,&g,&b)==0){
        ACTIVEINTABLEQB=QBrush(QColor(r, g, b));
    }
    else{
        ACTIVEINTABLEQB=QBrush(QColor(0, 255, 0));
        ++sum;
    }
    if(getStyle(&NotUseListBadArchitectureAppForRunFunc,x,"ACTIVELISTQB",&r,&g,&b)==0){
        ACTIVELISTQB=QBrush(QColor(r, g, b));
    }
    else{
        ACTIVELISTQB=QBrush(QColor(128, 128, 128));
        ++sum;
    }
    if(sum==0){
    return true;
    }
    else{
        return false;
    }


//    switch(x){
//        case defaults:
//            DEFAULTQB=QBrush(QColor(255, 255, 255));
//            NOTUSEQB=QBrush(QColor(0, 255, 255));
//            TRUEQB=QBrush(QColor(255, 140, 0));
//            FALSEQB=QBrush(QColor(219, 112, 147));
//            GRIDQB=QBrush(QColor(255, 0, 0));
//            ACTIVEINTABLEQB=QBrush(QColor(0, 255, 0));
//            ACTIVELISTQB=QBrush(QColor(128, 128, 128));
//            break;
//        case low:
//            DEFAULTQB=QBrush(QColor(255, 255, 255));
//            NOTUSEQB=QBrush(QColor(100, 100, 100));
//            TRUEQB=QBrush(QColor(120,219,226));
//            FALSEQB=QBrush(QColor(229,43,80));
//            GRIDQB=QBrush(QColor(100, 100, 100));
//            ACTIVEINTABLEQB=QBrush(QColor(204,204,255));
//            ACTIVELISTQB=QBrush(QColor(255, 0, 0));
//            break;
//        case as1C:
//            DEFAULTQB=QBrush(QColor(255, 255, 255));
//            NOTUSEQB=QBrush(QColor(179,172,134));
//            TRUEQB=QBrush(QColor(244,236,197));
//            FALSEQB=QBrush(QColor(255,0,0));
//            GRIDQB=QBrush(QColor(179,172,134));
//            ACTIVEINTABLEQB=QBrush(QColor(255, 250, 217));
//            ACTIVELISTQB=QBrush(QColor(245,242,221));
//            break;
//        case dark:
//            DEFAULTQB=QBrush(QColor(255, 255, 255));
//            NOTUSEQB=QBrush(QColor(0, 0, 0));
//            TRUEQB=QBrush(QColor(0, 0, 255));
//            FALSEQB=QBrush(QColor(255, 0, 0));
//            GRIDQB=QBrush(QColor(0, 0, 0));
//            ACTIVEINTABLEQB=QBrush(QColor(0, 255, 0));
//            ACTIVELISTQB=QBrush(QColor(128, 128, 128));
//            break;
//    };
}


int getStyle(QStringList * ListStyle,QString style,QString subStyl,int *r,int *g,int *b){
    QFile file("style.json");
    if(!file.exists()){
        qDebug()<<"Нет файла со стилями";
        return 1;
    }
    file.open(QIODevice::ReadOnly);
    QJsonDocument document = QJsonDocument::fromJson(file.readAll());
    // Забираем из документа корневой объект
    QJsonObject root = document.object();

    if(!(root.contains("crossword") && root["crossword"].isObject())){
        qDebug()<<"Problem with crossword"<<endl;
        return 1;
    }
    QJsonObject mainStyle=root["crossword"].toObject();
    *ListStyle=mainStyle.keys();
    if(ListStyle->count()==0){
        qDebug()<<"not style"<<endl;
        return 1;
    }


    if(!(mainStyle.contains(style) && mainStyle[style].isObject())){
        qDebug()<<"not have "+style<<endl;
        return 1;
    }
    QJsonObject nameSubStyle=mainStyle[style].toObject();
    //Проверяем есть ли такой

    if(!(nameSubStyle.contains(subStyl) && nameSubStyle[subStyl].isObject())){
        qDebug()<<"not have "+subStyl<<endl;
        return 1;
    }
    QJsonObject nextSubStyle=nameSubStyle[subStyl].toObject();
    if(!(nextSubStyle.contains("red") && nextSubStyle["red"].isString())){
        qDebug()<<"not have red"<<endl;
        return 1;
    }
    if(!(nextSubStyle.contains("green") && nextSubStyle["green"].isString())){
        qDebug()<<"not have green"<<endl;
        return 1;
    }
    if(!(nextSubStyle.contains("blue") && nextSubStyle["blue"].isString())){
        qDebug()<<"not have blue"<<endl;
        return 1;
    }
    *r=nextSubStyle["red"].toString().toInt();
    *g=nextSubStyle["blue"].toString().toInt();
    *b=nextSubStyle["green"].toString().toInt();
    return 0;
}

