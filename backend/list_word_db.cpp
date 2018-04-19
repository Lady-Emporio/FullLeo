#include "list_word_db.h"
#include <QDebug>
#include <QHeaderView>

ListWordDB::ListWordDB(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    QHBoxLayout *ListBDLayout=new QHBoxLayout();
    findWord=new QLineEdit(this);
    findWord->setMaximumWidth(60);
    setFontToWidget(findWord);
    listinBD=new QTableWidget(this);
    finderTable=new QTableWidget(this);
    setFontToWidget(finderTable);
    finderTable->setRowCount(LeoConst::CONST()->ListWithWordConst.size());
    finderTable->setColumnCount(2);
    finderTable->setHorizontalHeaderLabels((QStringList() << "eng" << "ru"));
    finderTable->horizontalHeader()->setStretchLastSection(true);
    finderTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    setFontToWidget(listinBD);
    listinBD->setRowCount(LeoConst::CONST()->ListWithWordConst.size());
    listinBD->setColumnCount(2);
    listinBD->setHorizontalHeaderLabels((QStringList() << "eng" << "ru"));
    listinBD->horizontalHeader()->setStretchLastSection(true);
    listinBD->setSelectionBehavior(QAbstractItemView::SelectRows);
    for(size_t i=0;i!=LeoConst::CONST()->ListWithWordConst.size();++i){
        QTableWidgetItem *nextEng=new QTableWidgetItem( LeoConst::CONST()->ListWithWordConst[i].eng );
        QTableWidgetItem *nextRu=new QTableWidgetItem( LeoConst::CONST()->ListWithWordConst[i].ru);
        nextEng->setTextAlignment(Qt::AlignVCenter);
        nextEng->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        nextRu->setTextAlignment(Qt::AlignVCenter);
        nextRu->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        listinBD->setItem(i, 0, nextEng);
        listinBD->setItem(i, 1, nextRu);
    }
    thenSetList=new QTableWidget(this);
    setFontToWidget(thenSetList);
    thenSetList->setRowCount(0);
    thenSetList->setColumnCount(2);
    thenSetList->setHorizontalHeaderLabels((QStringList() << "eng" << "ru"));
    thenSetList->resizeColumnsToContents();
    thenSetList->horizontalHeader()->setStretchLastSection(true);
    thenSetList->setSelectionBehavior(QAbstractItemView::SelectRows);
    QPushButton *Update=new QPushButton(this);
    setFontToWidget(Update);
    Update->setText("Accept||Update");
    ListBDLayout->addWidget(listinBD);
    ListBDLayout->addWidget(thenSetList);

    QVBoxLayout *buttonLayout=new QVBoxLayout;
    buttonLayout->addWidget(findWord);
    QPushButton *to_right_Button=new QPushButton(this);
    setFontToWidget(to_right_Button);
    to_right_Button->setText(">>");
    QPushButton *to_left_Button=new QPushButton(this);
    to_left_Button->setText("<<");
    setFontToWidget(to_left_Button);

    QHBoxLayout *StayBDLayout=new QHBoxLayout();
    FromDB=new QLineEdit(this);
    FromDB->setPlaceholderText("from");
    setFontToWidget(FromDB);
    QPushButton *ToDBButton=new QPushButton("from <-|-> to",this);
    setFontToWidget(ToDBButton);

    ToDB=new QLineEdit(this);
    ToDB->setPlaceholderText("to");
    setFontToWidget(ToDB);

    StayBDLayout->addWidget(FromDB);
    StayBDLayout->addWidget(ToDBButton);
    StayBDLayout->addWidget(ToDB);
    buttonLayout->addWidget(to_right_Button);
    buttonLayout->addWidget(to_left_Button);

    ListBDLayout->addLayout(buttonLayout);
    ListBDLayout->addWidget(finderTable);
    mainLayout->addLayout(ListBDLayout);
    mainLayout->addWidget(Update);
    mainLayout->addLayout(StayBDLayout);
    this->setLayout(mainLayout);
    connect(listinBD, SIGNAL(cellDoubleClicked(int , int)), this, SLOT(connect_IN_bd_trigger(int, int)));
    connect(thenSetList, SIGNAL(cellDoubleClicked(int , int)), this, SLOT(connect_FROM_NEW_LISR_trigger(int, int)));
    connect(Update, SIGNAL(clicked()), this, SLOT(connect_UpdateTable()));
    connect(findWord, SIGNAL(textChanged(const QString )), this, SLOT(connect_TextChanged_FindWord(const QString)));
    connect(finderTable, SIGNAL(cellDoubleClicked(int , int)), this, SLOT(connect_FROM_FINDER_trigger(int, int)));
    connect(listinBD->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(connect_SORT_list_db_trigger(int)));
    connect(to_right_Button, SIGNAL(clicked()), this, SLOT(connect_Word_shift_right()));
    connect(to_left_Button, SIGNAL(clicked()), this, SLOT(connect_Word_shift_left()));
    connect(ToDBButton, SIGNAL(clicked()), this, SLOT(connect_NeedReplaceDB()));
}
void ListWordDB::connect_NeedReplaceDB(){
    QMessageBox msgBox;
    if(ToDB->text().size()==0){
        msgBox.setText("Не выбрано имя файла ToDB");
        msgBox.exec();
        return;
    }
    if(FromDB->text().size()==0){
        msgBox.setText("Не выбрано имя файла FromDB");
        msgBox.exec();
        return;
    }
    QString nameToDB=ToDB->text()+".sqlite";
    QString nameFromDB=FromDB->text()+".sqlite";

    QDir nowPath=QDir::current();
    QStringList fileInDir=nowPath.entryList(QStringList("*.sqlite"));
    for(QString x: fileInDir){
        if(x==nameToDB){
            msgBox.setText("nameToDB exist");
            msgBox.exec();
            return;
        }else if(x==nameFromDB){
            msgBox.setText("nameFromDB exist");
            msgBox.exec();
            return;
        }
    }

    {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","FromDB");
    db.setDatabaseName(nameFromDB);//Имя базы.
    if (!db.open()){
        QMessageBox msgBox;
        msgBox.setText(db.lastError().text());
        msgBox.exec();
        db.close();
        db=QSqlDatabase();
        QSqlDatabase::removeDatabase("FromDB");
        return;
    }
    QSqlQuery query(db);
    query.exec("CREATE TABLE MainTable(eng text,ru text); ");
    query.clear();
    for(size_t row=0;row!=listinBD->rowCount();++row){
        QString nextEng=listinBD->item(row,0)->text();
        QString nextRu=listinBD->item(row,1)->text();
        query.prepare("INSERT INTO MainTable VALUES (:eng,:ru);");
        query.bindValue(":eng", nextEng);
        query.bindValue(":ru", nextRu);
        if(!query.exec()){
            msgBox.setText(db.lastError().text()+" | "+query.lastError().text());
            msgBox.exec();
            db.close();
            db=QSqlDatabase();
            QSqlDatabase::removeDatabase("FromDB");
            return;
        }
        query.clear();
    }
    db.commit();
    db.close();
    db=QSqlDatabase();
    QSqlDatabase::removeDatabase("FromDB");
    }

    {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","ToDB");
    db.setDatabaseName(nameToDB);//Имя базы.
    if (!db.open()){
        QMessageBox msgBox;
        msgBox.setText(db.lastError().text());
        msgBox.exec();
        db.close();
        db=QSqlDatabase();
        QSqlDatabase::removeDatabase("ToDB");
        return;
    }
    QSqlQuery query(db);
    query.exec("CREATE TABLE MainTable(eng text,ru text); ");
    query.clear();
    for(size_t row=0;row!=thenSetList->rowCount();++row){
        QString nextEng=thenSetList->item(row,0)->text();
        QString nextRu=thenSetList->item(row,1)->text();
        query.prepare("INSERT INTO MainTable VALUES (:eng,:ru);");
        query.bindValue(":eng", nextEng);
        query.bindValue(":ru", nextRu);
        if(!query.exec()){
            msgBox.setText(db.lastError().text()+" | "+query.lastError().text());
            msgBox.exec();
            db.close();
            db=QSqlDatabase();
            QSqlDatabase::removeDatabase("ToDB");
            return;
        }
        query.clear();
    }
    db.commit();
    db.close();
    db=QSqlDatabase();
    QSqlDatabase::removeDatabase("ToDB");
    }
}

void ListWordDB::connect_Word_shift_right(){
    for(size_t row=0;row!=listinBD->rowCount();++row){
        thenSetList->insertRow(0);
        QTableWidgetItem *nextEng=new QTableWidgetItem(*(listinBD->item(row,0)));
        QTableWidgetItem *nextRu=new QTableWidgetItem( *(listinBD->item(row,1)));
        thenSetList->setItem(0, 0, nextEng);
        thenSetList->setItem(0, 1, nextRu);
    }
    listinBD->clearContents();
    listinBD->setRowCount(0);
}

void ListWordDB::connect_Word_shift_left(){
    for(size_t row=0;row!=thenSetList->rowCount();++row){
        listinBD->insertRow(0);
        QTableWidgetItem *nextEng=new QTableWidgetItem(*(thenSetList->item(row,0)));
        QTableWidgetItem *nextRu=new QTableWidgetItem( *(thenSetList->item(row,1)));
        listinBD->setItem(0, 0, nextEng);
        listinBD->setItem(0, 1, nextRu);
    }
    thenSetList->clearContents();
    thenSetList->setRowCount(0);
}


void ListWordDB::connect_SORT_list_db_trigger(int logicalIndex){
    listinBD->sortByColumn(logicalIndex);
}

void ListWordDB::connect_TextChanged_FindWord(const QString &currentText){
    QList<QTableWidgetItem*> finder=listinBD->findItems(currentText,Qt::MatchContains);
    finderTable->clearContents();
    finderTable->setRowCount(0);
    for(QTableWidgetItem* x:finder){
        int row=listinBD->row(x);
        QTableWidgetItem *nextEng=new QTableWidgetItem(*(listinBD->item(row,0)));
        QTableWidgetItem *nextRu=new QTableWidgetItem( *(listinBD->item(row,1)));
        finderTable->insertRow(0);
        finderTable->setItem(0, 0, nextEng);
        finderTable->setItem(0, 1, nextRu);
    }
}
void ListWordDB::connect_FROM_FINDER_trigger(int row, int column){
    thenSetList->insertRow(0);
    QTableWidgetItem *nextEng=new QTableWidgetItem(*(finderTable->item(row,0)));
    QTableWidgetItem *nextRu=new QTableWidgetItem( *(finderTable->item(row,1)));
    thenSetList->setItem(0, 0, nextEng);
    thenSetList->setItem(0, 1, nextRu);
}

void ListWordDB::connect_IN_bd_trigger(int row, int column){
    thenSetList->insertRow(0);
    QTableWidgetItem *nextEng=new QTableWidgetItem(*(listinBD->item(row,0)));
    QTableWidgetItem *nextRu=new QTableWidgetItem( *(listinBD->item(row,1)));
    thenSetList->setItem(0, 0, nextEng);
    thenSetList->setItem(0, 1, nextRu);
    listinBD->removeRow(row);
}

void ListWordDB::connect_FROM_NEW_LISR_trigger(int row, int column){
    listinBD->insertRow(0);
    QTableWidgetItem *nextEng=new QTableWidgetItem(*(thenSetList->item(row,0)));
    QTableWidgetItem *nextRu=new QTableWidgetItem( *(thenSetList->item(row,1)));
    listinBD->setItem(0, 0, nextEng);
    listinBD->setItem(0, 1, nextRu);
    thenSetList->removeRow(row);
}
void ListWordDB::connect_UpdateTable(){
    std::vector<Word> NewListWord;
    std::vector<Word> ListWithWordConst=LeoConst::CONST()->ListWithWordConst;
    for(size_t i=0;i!=thenSetList->rowCount();++i){
        QString eng=thenSetList->item(i,0)->text();
        QString ru=thenSetList->item(i,1)->text();
        for(size_t i_list=0;i_list!=ListWithWordConst.size();++i_list){
            Word nextWord=ListWithWordConst[i_list];
            if(nextWord.eng==eng && nextWord.ru==ru){
                NewListWord.push_back(nextWord);
                break;
            }
        }
    }
    LeoConst::CONST()->ListWithWordConst=NewListWord;
}
