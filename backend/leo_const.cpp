#include "leo_const.h"
#include "sqlite3.h"
#include "QMessageBox"
#include <QtSql>


LeoConst::LeoConst()
{
    player=new QMediaPlayer;
    ALGORITMH=fast;
    All_BOOL_PARAMS.insert("JUMP",false);
    All_BOOL_PARAMS.insert("AUTOCOMPLETION",false);
    All_BOOL_PARAMS.insert("GRID",false);
    All_BOOL_PARAMS.insert("runAudio",false);
    All_BOOL_PARAMS.insert("runImage",false);
    All_BOOL_PARAMS.insert("EVER",false);



    AllQBrushdictPARAMS.insert("DEFAULTQB", QBrush(QColor(255, 255, 255)));
    AllQBrushdictPARAMS.insert("NOTUSEQB", QBrush(QColor(255, 255, 255)));
    AllQBrushdictPARAMS.insert("TRUEQB", QBrush(QColor(0, 255, 255)));
    AllQBrushdictPARAMS.insert("FALSEQB", QBrush(QColor(255, 140, 0)));
    AllQBrushdictPARAMS.insert("GRIDQB", QBrush(QColor(219, 112, 147)));
    AllQBrushdictPARAMS.insert("ACTIVEINTABLEQB", QBrush(QColor(255, 0, 0)));
    AllQBrushdictPARAMS.insert("ACTIVELISTQB", QBrush(QColor(0, 255, 0)));
    AllQBrushdictPARAMS.insert("WRITECELL", QBrush(QColor(128, 128, 128)));

    All_INT_PARAMS.insert("getFromDB", 0);
    All_INT_PARAMS.insert("ROWHEIGHT", 20);
    All_INT_PARAMS.insert("COLUMNWIDTH", 20);
    All_INT_PARAMS.insert("MARGIN1", 65);
    All_INT_PARAMS.insert("FONT_SIZE", 10);
    All_INT_PARAMS.insert("TABLE_ROW", 10);
    All_INT_PARAMS.insert("TABLE_COL", 10);
    All_INT_PARAMS.insert("COUNT_BUTTOM", 4);

    All_QString_PARAMS.insert("path_bd","./bd1.sqlite");
    All_QString_PARAMS.insert("fontFamyle","Courier New");
    All_QString_PARAMS.insert("TRUE_ANSWER_COLOR","");
    All_QString_PARAMS.insert("FALSE_ANSWER_COLOR","");
    All_QString_PARAMS.insert("DEFAULT_BUTTOM_COLOR","");
    THIS_IS_ALL_UPDATE_fromfileAndBD();

}
void LeoConst::THIS_IS_ALL_UPDATE_fromfileAndBD(){
    getMainRootJson();
    FromRootString();
    FromRootINT();
    FromRootBOOL();
    fillActiveStyleAndListStyle();
    FromRootQBrush();
    GetFromBD();
}

LeoConst *LeoConst::CONST(){
    static LeoConst*l=new LeoConst;
    return l;
}

void setFontToWidget(QWidget * x){
    QFont font;
    font.setFamily(LeoConst::CONST()->All_QString_PARAMS["fontFamyle"]);
    font.setPointSize(LeoConst::CONST()->All_INT_PARAMS["FONT_SIZE"]);
    x->setFont(font);
}

void LeoConst::GetFromBD(){

    QFile file(this->All_QString_PARAMS["path_bd"]);
    if(!file.exists()){
        QMessageBox msgBox;
        msgBox.setText("not file db: "+this->All_QString_PARAMS["path_bd"]);
        msgBox.exec();
        return;
    }
    sqlite3 *db;
    sqlite3_stmt * pStmt;
    if (sqlite3_open(All_QString_PARAMS["path_bd"].toStdString().c_str(), &db)){
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
    if(this->All_INT_PARAMS["getFromDB"]!=0){
        stop=All_INT_PARAMS["getFromDB"];
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

void LeoConst::getMainRootJson(){
    QFile file("style.json");
    if(!file.exists()){
        QMessageBox msgBox;
        msgBox.setText("Нет файла со стилями");
        msgBox.exec();
        return;
    }
    file.open(QIODevice::ReadOnly);
    QJsonDocument document = QJsonDocument::fromJson(file.readAll());
    root=document.object();
}


void LeoConst::fillActiveStyleAndListStyle(){
    QMessageBox msgBox;
    if(!(root.contains("crossword") && root["crossword"].isObject())){
        msgBox.setText("Нет файла со crossword");
        msgBox.exec();
        return;
    }
    QJsonObject mainStyle=root["crossword"].toObject();
    ListStyle=mainStyle.keys();
    if(ListStyle.count()==0){
        msgBox.setText("not style crossword");
        msgBox.exec();
        return;
    }


    auto findDef=std::find(ListStyle.begin(),ListStyle.end(),"default");
    if (findDef!=ListStyle.end()){
        ActiveStyle="default";
    }else{
        msgBox.setText("default style not found, set pandom style");
        msgBox.exec();
        ActiveStyle=ListStyle[0];
    }
}


void LeoConst::FromRootQBrush(){
    QMessageBox msgBox;
    if(!(root.contains("crossword") && root["crossword"].isObject())){
        msgBox.setText("Нет файла со crossword");
        msgBox.exec();
        return;
    }
    QJsonObject mainStyle=root["crossword"].toObject();
    if(!(mainStyle.contains(ActiveStyle) && mainStyle[ActiveStyle].isObject())){
        msgBox.setText("not have: "+ ActiveStyle);
        msgBox.exec();
        return;
    }
    for(QString style:ListStyle){
        QJsonObject nameSubStyle=mainStyle[style].toObject();
        QMap<QString,QBrush> nextMap;
        for(QMap<QString,QBrush>::iterator it = AllQBrushdictPARAMS.begin();it != AllQBrushdictPARAMS.end(); ++it){
            QJsonObject nextSubStyle=nameSubStyle[it.key()].toObject();
            if(!(nextSubStyle.contains("red") && nextSubStyle["red"].isDouble())){
                msgBox.setText("not have red");
                msgBox.exec();
                return;
            }
            if(!(nextSubStyle.contains("green") && nextSubStyle["green"].isDouble())){
                msgBox.setText("not have green");
                msgBox.exec();
                return;
            }
            if(!(nextSubStyle.contains("blue") && nextSubStyle["blue"].isDouble())){
                msgBox.setText("not have blue");
                msgBox.exec();
                return;
            }
            int r=nextSubStyle["red"].toInt();
            int g=nextSubStyle["green"].toInt();
            int b=nextSubStyle["blue"].toInt();
            nextMap.insert(it.key(),QBrush(QColor(r, g, b)));
        }
        AllStyleMap[style]=nextMap;
    }
}

void LeoConst::FromRootINT(){
    QMessageBox msgBox;
    for(QMap<QString,int>::iterator it = All_INT_PARAMS.begin();it != All_INT_PARAMS.end(); ++it){
    QString param=it.key();
    if(!(root.contains(param) && root[param].isDouble())){
        msgBox.setText("Problem with: "+it.key());
        msgBox.exec();
        return;
    }
    All_INT_PARAMS[param]=root.value(param).toInt();
    }
}
void LeoConst::FromRootBOOL(){
    QMessageBox msgBox;
    for(QMap<QString,bool>::iterator it = All_BOOL_PARAMS.begin();it != All_BOOL_PARAMS.end(); ++it){
    QString param=it.key();
    if(!(root.contains(param) && root[param].isBool())){
        msgBox.setText("Problem with: "+it.key());
        msgBox.exec();
        return;
    }
    All_BOOL_PARAMS[param]=root.value(param).toBool();
    }
}

void LeoConst::FromRootString(){
    QMessageBox msgBox;
    for(QMap<QString,QString>::iterator it = All_QString_PARAMS.begin();it != All_QString_PARAMS.end(); ++it){
    QString param=it.key();
    if(!(root.contains(param) && root[param].isString())){
        msgBox.setText("Problem with: "+it.key());
        msgBox.exec();
        return;
    }
    All_QString_PARAMS[param]=root.value(param).toString();
    }
}

void LeoConst::setStyle(QString x){
    ActiveStyle=x;
    for(auto x=AllQBrushdictPARAMS.begin();x!=AllQBrushdictPARAMS.end();++x){
        AllQBrushdictPARAMS[x.key()]=AllStyleMap[ActiveStyle][x.key()];
    }
}


void LeoConst::printAllWordInBD(QString path){
    QMessageBox msgBox;
    sqlite3 *db;
    sqlite3_stmt *stmt;
    path+=".sqlite";
    if( sqlite3_open(path.toStdString().c_str(), &db) ){
        sqlite3_close(db);
        msgBox.setText("Can't open database.");
        msgBox.exec();
        return;
    }
    std::string create="CREATE TABLE IF NOT EXISTS MainTable(eng text,ru text); ";
    if( sqlite3_exec(db, create.c_str(), 0, 0, 0)!=SQLITE_OK ){
        sqlite3_close(db);
        msgBox.setText("Can't create MainTable: ");
        msgBox.exec();
        return;
    }
    for (Word x:ListWithWordConst){
        std::string eng_std=x.eng.toStdString();//else not do it visibly
        std::string ru_std=x.ru.toStdString();//error:  x.ru.toStdString().c_str() not work
        sqlite3_prepare( db, "insert into 'MainTable' values(?,?);", -1, &stmt, 0);
        sqlite3_bind_text( stmt, 1, eng_std.c_str(),  -1, 0 );
        sqlite3_bind_text( stmt, 2, ru_std.c_str(), -1, 0 );
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
    sqlite3_close(db);
}

void LeoConst::fallbackAllWordInBD(QString path){
    path+=".sqlite";
    QMessageBox msgBox;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QSqlQuery query;
    db.setDatabaseName(path);//Имя базы.
    if (!db.open()){
        msgBox.setText(db.lastError().text());
        msgBox.exec();
        return;
    }
    query=db.exec( QString( "CREATE TABLE IF NOT EXISTS MainTable(eng text,ru text); "));
    for(Word x:ListWithWordConst){
        query.prepare("INSERT INTO MainTable VALUES (:eng, :ru)");
        query.bindValue(":eng", x.eng);
        query.bindValue(":ru", x.ru);
        if(!query.exec()){
            msgBox.setText(db.lastError().text()+" "+query.lastError().text());
            msgBox.exec();
            return;
        }
    }
    db.commit();
    db.close();
}




