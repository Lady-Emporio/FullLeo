#include "crossword.h"
#include <QBrush>

#include <QString>
#include <QDebug>
Crossword::Crossword(QWidget *parent) : QWidget(parent)
{
//    tableWord=new Table;


    QHBoxLayout *MainLayout=new QHBoxLayout(this);
    QVBoxLayout *SettingLauout=new QVBoxLayout;
    ErrorLabel=new QLabel("Все в порядке");
    QPushButton *buttom1=new QPushButton("We are");
    QPushButton *buttom2=new QPushButton("update");
    MainTable=new QTableWidget(TABLE_ROW,TABLE_COL);
//    UsingWordList=new QListWidget;
    UsingWordList=new QListWidget;
    UsingWordList-> setFixedSize(QSize(100, (TABLE_COL*COLUMNWIDTH)+MARGIN1));
    for(int i=0;i!=TABLE_ROW;++i){
        MainTable->setColumnWidth(i,20);
        MainTable->setRowHeight(i,20);
    };

    this->resize(TABLE_ROW*ROWHEIGHT+(MARGIN1*3)+UsingWordList->width(),(TABLE_COL*COLUMNWIDTH)+MARGIN1);

    MainLayout->addLayout(SettingLauout);
    SettingLauout->addWidget(ErrorLabel);
    SettingLauout->addWidget(buttom1);
    SettingLauout->addWidget(buttom2);
    MainLayout->addWidget(MainTable);
    MainLayout->addWidget(UsingWordList);
    this->setLayout(MainLayout);

    connect(buttom2, SIGNAL(clicked()), this, SLOT(slotUpdate()));

    connect(UsingWordList, SIGNAL(currentRowChanged(int)), this, SLOT(SelectWordRight(int)));
}
void Crossword::SelectWordRight(int x){
    for(int i=0;i!=LastSelectInMainTable.size();++i){
        LastSelectInMainTable[i]->setBackground(QBrush(QColor(255, 255, 255)));
    };
    LastSelectInMainTable.clear();


    QString selected=UsingWordList->item(x)->text();
    ErrorLabel->setText(selected);
    for(int row = 0; row != MainTable->rowCount(); row++){
        for(int column = 0; column !=MainTable->columnCount(); column++){
            Word MyCelectFirstWord=tableWord.table[row][column].FirstWord();
            Word MyCelectSecondWord=tableWord.table[row][column].SecondWord();
            QString engFirstWord=MyCelectFirstWord.eng.c_str();
            QString engSecondWord=MyCelectSecondWord.eng.c_str();
            if(selected==engFirstWord || selected==engSecondWord){
//                    qDebug()<<MyCelect.ru.c_str();
                    QTableWidgetItem *itemNow=MainTable->item(row,column);
                    itemNow->setBackground(QBrush(QColor(0, 255, 17)));
                    LastSelectInMainTable.push_back(itemNow);
            }
        };
    };
}

void Crossword::UpdateMainTable(){
    for(int row = 0; row != MainTable->rowCount(); row++){
        for(int column = 0; column !=MainTable->columnCount(); column++){
            QTableWidgetItem *item = new QTableWidgetItem(); // выделяем память под ячейку
            char word=tableWord.table[row][column].Value();
            if(word=='@'){
                item->setText(" ");
                item->setFlags(Qt::NoItemFlags);
                item->setBackground(QBrush(QColor(74, 247, 239)));
            }
            else if(word=='#'){
                item->setFlags(Qt::NoItemFlags);
                item->setText(QString(word));
                item->setBackground(QBrush(QColor(255, 0, 0)));
            }
            else{
                item->setText(QString(word));
            }
            MainTable->setItem(row, column, item);
        };
    };
    for(int i=0;i!=tableWord.Using_Word.size();++i){
        new QListWidgetItem(tableWord.Using_Word[i].eng.c_str(), UsingWordList);
    };
}


void Crossword::slotUpdate(){
    clearToNextPound();
    std::string error;
    if(!tableWord.run(&error)){
        ErrorLabel->setText(error.c_str());
    }
    UpdateMainTable();
}
void Crossword::clearToNextPound(){
    Table *newTable=new Table;
    tableWord=*newTable;
    UsingWordList->clear();
}
