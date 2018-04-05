#include "leo_const.h"
#include "sqlite3.h"
#include "QMessageBox"

QMediaPlayer * LeoConst::player = new QMediaPlayer();//global

LeoConst::LeoConst()
{
    getFromDB=0;
    QString Error="";
    setStyle("default",Error);
    if(Error.size()!=0){
        QMessageBox msgBox;
        msgBox.setText(Error);
        msgBox.exec();
        Error="";
    }
    if(getConstParam(QString("FONT_SIZE"),Error)!=0){
        QMessageBox msgBox;
        msgBox.setText(Error);
        msgBox.exec();
        Error="";
        FONT_SIZE=10;
    }else{
        FONT_SIZE=Error.toInt();
    }
    if(getConstParam(QString("path_bd"),Error)!=0){
        QMessageBox msgBox;
        msgBox.setText(Error);
        msgBox.exec();
        Error="";
        path_bd="./lingualeo.txt";
    }else{
        path_bd=Error;
    }
    GetFromBD();
    if(getConstParam(QString("fontFamyle"),Error)!=0){
        QMessageBox msgBox;
        msgBox.setText(Error);
        msgBox.exec();
        Error="";
        fontFamyle="Courier New";
    }else{
        fontFamyle=Error;
    }
    if(getConstParam(QString("TABLE_ROW"),Error)!=0){
        QMessageBox msgBox;
        msgBox.setText(Error);
        msgBox.exec();
        Error="";
        TABLE_ROW=40;
    }else{
        TABLE_ROW=Error.toInt();
    }
    if(getConstParam(QString("TABLE_COL"),Error)!=0){
        QMessageBox msgBox;
        msgBox.setText(Error);
        msgBox.exec();
        Error="";
        TABLE_COL=40;
    }else{
        TABLE_COL=Error.toInt();
    }
    ROWHEIGHT=20;
    COLUMNWIDTH=20;
    MARGIN1=65;
    ALGORITMH=fast;
    JUMP=false;
    AUTOCOMPLETION=false;
    GRID=true;
    if(getConstParam(QString("TRUE_ANSWER_COLOR"),Error)!=0){
        QMessageBox msgBox;
        msgBox.setText(Error);
        msgBox.exec();
        Error="";
        TRUE_ANSWER_COLOR="";
    }else{
        TRUE_ANSWER_COLOR=Error;
    }
    if(getConstParam(QString("FALSE_ANSWER_COLOR"),Error)!=0){
        QMessageBox msgBox;
        msgBox.setText(Error);
        msgBox.exec();
        Error="";
        FALSE_ANSWER_COLOR="";
    }else{
        FALSE_ANSWER_COLOR=Error;
    }
    if(getConstParam(QString("DEFAULT_BUTTOM_COLOR"),Error)!=0){
        QMessageBox msgBox;
        msgBox.setText(Error);
        msgBox.exec();
        Error="";
        DEFAULT_BUTTOM_COLOR="";
    }else{
        DEFAULT_BUTTOM_COLOR=Error;
    }
    if(getConstParam(QString("COUNT_BUTTOM"),Error)!=0){
        QMessageBox msgBox;
        msgBox.setText(Error);
        msgBox.exec();
        Error="";
        COUNT_BUTTOM=4;
    }else{
        COUNT_BUTTOM=Error.toInt();
    }
    runAudio=false;
    runImage=false;
}

LeoConst *LeoConst::CONST(){
    static LeoConst*l=new LeoConst;
    return l;
}

void setFontToWidget(QWidget * x){
    QFont font;
    font.setFamily(LeoConst::CONST()->fontFamyle);
    font.setPointSize(LeoConst::CONST()->FONT_SIZE);
    x->setFont(font);
}

void LeoConst::GetFromBD(){

    QFile file(this->path_bd);
    if(!file.exists()){
        QMessageBox msgBox;
        msgBox.setText("not file db: "+this->path_bd);
        msgBox.exec();
        return;
    }
    sqlite3 *db;
    sqlite3_stmt * pStmt;
    if (sqlite3_open(path_bd.toStdString().c_str(), &db)){
        sqlite3_close(db);
        QMessageBox msgBox;
        msgBox.setText("Не получается открыть бд");
        msgBox.exec();
        return;

    }
    if (sqlite3_prepare(db, "SELECT * FROM 'MainTable';", -1, &pStmt, NULL)){
        sqlite3_finalize(pStmt);
        sqlite3_close(db);
        QMessageBox msgBox;
        msgBox.setText("Не получается вытащить все из MainTable");
        msgBox.exec();
        return;
    };
    ListWithWordConst.clear();
    int stop=9999;
    if(this->getFromDB!=0){
        stop=getFromDB;
    }
    while((sqlite3_step(pStmt)) == SQLITE_ROW){
        if(stop==0){
            break;
        }
        --stop;
        Word next;
        next.eng=reinterpret_cast<const char *>(sqlite3_column_text(pStmt, 0));
        next.ru=reinterpret_cast<const char *>(sqlite3_column_text(pStmt, 1));
        ListWithWordConst.push_back(next);

    };
    sqlite3_finalize(pStmt);
    sqlite3_close(db);
    if(ListWithWordConst.size()==0){
        QMessageBox msgBox;
        msgBox.setText("Массив пустой. Из бд ничего не достали");
        msgBox.exec();
    }
}

int getStyle(QStringList * ListStyle,QString style,QString subStyl,int *r,int *g,int *b,QString &Error){
    QFile file("style.json");
    if(!file.exists()){
        Error+="Нет файла со стилями";
        return 1;
    }
    file.open(QIODevice::ReadOnly);
    QJsonDocument document = QJsonDocument::fromJson(file.readAll());
    // Забираем из документа корневой объект
    QJsonObject root = document.object();

    if(!(root.contains("crossword") && root["crossword"].isObject())){
        Error+="Problem with crossword";
        return 1;
    }
    QJsonObject mainStyle=root["crossword"].toObject();
    *ListStyle=mainStyle.keys();
    if(ListStyle->count()==0){
        Error+="not style";
        return 1;
    }


    if(!(mainStyle.contains(style) && mainStyle[style].isObject())){
        Error+="not have "+style;
        return 1;
    }
    QJsonObject nameSubStyle=mainStyle[style].toObject();
    //Проверяем есть ли такой

    if(!(nameSubStyle.contains(subStyl) && nameSubStyle[subStyl].isObject())){
        Error+="not have "+subStyl;
        return 1;
    }
    QJsonObject nextSubStyle=nameSubStyle[subStyl].toObject();
    if(!(nextSubStyle.contains("red") && nextSubStyle["red"].isString())){
        Error+="not have red";
        return 1;
    }
    if(!(nextSubStyle.contains("green") && nextSubStyle["green"].isString())){
        Error+="not have green";
        return 1;
    }
    if(!(nextSubStyle.contains("blue") && nextSubStyle["blue"].isString())){
        Error+="not have blue";
        return 1;
    }
    *r=nextSubStyle["red"].toString().toInt();
    *g=nextSubStyle["green"].toString().toInt();
    *b=nextSubStyle["blue"].toString().toInt();
    return 0;
}

int getConstParam(QString param,QString &returnErrorOrParam){
    QFile file("style.json");
    if(!file.exists()){
        returnErrorOrParam+="Нет файла со стилями";
        return 1;
    }
    file.open(QIODevice::ReadOnly);
    QJsonDocument document = QJsonDocument::fromJson(file.readAll());
    // Забираем из документа корневой объект
    QJsonObject root = document.object();

    if(!(root.contains(param) && root[param].isString())){
        returnErrorOrParam+="Problem with: "+param;
        return 1;
    }
    returnErrorOrParam=root.value(param).toString();
    return 0;
}

bool LeoConst::setStyle(QString x,QString &Error){
    QStringList NotUseListBadArchitectureAppForRunFunc;
    int r,g,b,sum=0;
    if(getStyle(&NotUseListBadArchitectureAppForRunFunc,x,"DEFAULTQB",&r,&g,&b,Error)==0){
        DEFAULTQB=QBrush(QColor(r, g, b));
    }
    else{
        DEFAULTQB=QBrush(QColor(255, 255, 255));
        Error+="set DEFAULTQB\n";
        ++sum;
    }
    if(getStyle(&NotUseListBadArchitectureAppForRunFunc,x,"WRITECELL",&r,&g,&b,Error)==0){
        WRITECELL=QBrush(QColor(r, g, b));
    }
    else{
        WRITECELL=QBrush(QColor(255, 255, 255));
        Error+="set WRITECELL\n";
        ++sum;
    }
    if(getStyle(&NotUseListBadArchitectureAppForRunFunc,x,"NOTUSEQB",&r,&g,&b,Error)==0){
        NOTUSEQB=QBrush(QColor(r, g, b));
    }
    else{
        NOTUSEQB=QBrush(QColor(0, 255, 255));
        Error+="set NOTUSEQB\n";
        ++sum;
    }
    if(getStyle(&NotUseListBadArchitectureAppForRunFunc,x,"TRUEQB",&r,&g,&b,Error)==0){
        TRUEQB=QBrush(QColor(r, g, b));
    }
    else{
        TRUEQB=QBrush(QColor(255, 140, 0));
        Error+="set TRUEQB\n";
        ++sum;
    }
    if(getStyle(&NotUseListBadArchitectureAppForRunFunc,x,"FALSEQB",&r,&g,&b,Error)==0){
        FALSEQB=QBrush(QColor(r, g, b));
    }
    else{
        FALSEQB=QBrush(QColor(219, 112, 147));
        Error+="set FALSEQB\n";
        ++sum;
    }
    if(getStyle(&NotUseListBadArchitectureAppForRunFunc,x,"GRIDQB",&r,&g,&b,Error)==0){
        GRIDQB=QBrush(QColor(r, g, b));
    }
    else{
        GRIDQB=QBrush(QColor(255, 0, 0));
        Error+="set GRIDQB\n";
        ++sum;
    }
    if(getStyle(&NotUseListBadArchitectureAppForRunFunc,x,"ACTIVEINTABLEQB",&r,&g,&b,Error)==0){
        ACTIVEINTABLEQB=QBrush(QColor(r, g, b));
    }
    else{
        ACTIVEINTABLEQB=QBrush(QColor(0, 255, 0));
        Error+="set ACTIVEINTABLEQB\n";
        ++sum;
    }
    if(getStyle(&NotUseListBadArchitectureAppForRunFunc,x,"ACTIVELISTQB",&r,&g,&b,Error)==0){
        ACTIVELISTQB=QBrush(QColor(r, g, b));
    }
    else{
        ACTIVELISTQB=QBrush(QColor(128, 128, 128));
        Error+="set ACTIVELISTQB\n";
        ++sum;
    }
    if(sum==0){
    return true;
    }
    else{
        return false;
    }
}











