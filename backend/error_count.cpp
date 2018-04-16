#include "error_count.h"
ErrorCount::ErrorCount(QWidget *parent) : QWidget(parent)
{
    static int counter=0;
    ++counter;
    QString ThisName="ErrorCount"+QString("").setNum(counter);
    this->setObjectName(ThisName);
    this->setWindowTitle(ThisName);
    db = QSqlDatabase::addDatabase("QSQLITE",ThisName);
    startIf=true;
    static bool createDB=true;
    if(createDB){
        db.setDatabaseName("Error.sqlite");//Имя базы.
        if (!db.open()){
            QMessageBox msgBox;
            msgBox.setText(db.lastError().text());
            msgBox.exec();
            db.close();
            db=QSqlDatabase();
            QSqlDatabase::removeDatabase("ErrorTable");
            return;
        }
    }
    model = new QSqlTableModel(this,db);

    QPushButton *Update=new QPushButton("Update",this);
    QPushButton *acceptError=new QPushButton("Accept changes",this);
    view=new QTableView(this);
    QGridLayout *mainLayout=new QGridLayout(this);
    mainLayout->addWidget(view,0,0);
    mainLayout->addWidget(Update,1,0);
    mainLayout->addWidget(acceptError,2,0);
    this->setLayout(mainLayout);
    connect(Update, SIGNAL(clicked()), this, SLOT(connectUpdate_trigger()));
    connect(acceptError, SIGNAL(clicked()), this, SLOT(connectAccept_changes_trigger()));
}

void ErrorCount::connectAccept_changes_trigger(){
    model->submitAll();
}

void ErrorCount::connectUpdate_trigger(){
    selectAll();
}

void ErrorCount::addToDB(Word word){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","AddWord");
    db.setDatabaseName("Error.sqlite");//Имя базы.
    if (!db.open()){
        QMessageBox msgBox;
        msgBox.setText(db.lastError().text());
        msgBox.exec();
        db.close();
        db=QSqlDatabase();
        QSqlDatabase::removeDatabase("AddWord");
        return;
    }
    QMessageBox msgBox;
    QSqlQuery query(db);
    query.exec("CREATE TABLE IF NOT EXISTS MainTable(eng text,ru text,count INTEGER ); ");
    query.clear();

    query.prepare("SELECT EXISTS(SELECT 1 FROM MainTable WHERE eng =:eng)");
    query.bindValue(":eng", word.eng);
    if(!query.exec()){
        msgBox.setText(db.lastError().text()+" | "+query.lastError().text());
        msgBox.exec();
        return;
    }
    query.first();
    int RowExist=query.value(0).toInt();
    query.clear();
    if(RowExist==1){

        query.prepare("Select count from MainTable where eng=?");
        query.addBindValue(word.eng);
        if(!query.exec()){
            msgBox.setText(db.lastError().text()+" | "+query.lastError().text());
            msgBox.exec();
            return;
        }
        query.first();
        int PlusOne=query.value(0).toInt();
        query.clear();

        query.prepare("UPDATE MainTable SET count = :PlusOne Where eng=:eng");
        query.bindValue(":PlusOne", PlusOne+1);
        query.bindValue(":eng", word.eng);
        if(!query.exec()){
            msgBox.setText(db.lastError().text()+" | "+query.lastError().text());
            msgBox.exec();
            return;
        }
    }else{
        query.prepare("INSERT INTO MainTable VALUES (:eng,:ru,:PlusOne);");
        query.bindValue(":PlusOne", 1);
        query.bindValue(":eng", word.eng);
        query.bindValue(":ru", word.ru);
        if(!query.exec()){
            msgBox.setText(db.lastError().text()+" | "+query.lastError().text());
            msgBox.exec();
            return;
        }
    }
    db.commit();
    db.close();
    db=QSqlDatabase();
    QSqlDatabase::removeDatabase("AddWord");
}

void ErrorCount::selectAll(){
    QMessageBox msgBox;
    if(startIf){
        model->setTable("MainTable");
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->select();
        view->setModel(model);
        startIf=false;
    }else{
        model->revertAll();
        model->select();
    }
}
