#include "crossword.h"
#include <QBrush>

#include <QString>
#include <QDebug>
Crossword::Crossword(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *MainLayout=new QHBoxLayout(this);
    QVBoxLayout *SettingLauout=new QVBoxLayout;
    ErrorLabel=new QLabel("Все в порядке");
    QPushButton *buttomVerify=new QPushButton("verify");
    QPushButton *buttomSeeAll=new QPushButton("Look,see all");
    QPushButton *buttomUpdate=new QPushButton("update");
    MainTable=new QTableWidget(TABLE_ROW,TABLE_COL);
    UsingWordList=new QListWidget;
    UsingWordList-> setFixedSize(QSize(100, (TABLE_COL*COLUMNWIDTH)+MARGIN1));
    for(int i=0;i!=TABLE_ROW;++i){
        MainTable->setColumnWidth(i,20);
        MainTable->setRowHeight(i,20);
    };

    this->resize(TABLE_ROW*ROWHEIGHT+(MARGIN1*3)+UsingWordList->width(),(TABLE_COL*COLUMNWIDTH)+MARGIN1);

    MainLayout->addLayout(SettingLauout);
    SettingLauout->addWidget(ErrorLabel);
    SettingLauout->addWidget(buttomUpdate);
    SettingLauout->addWidget(buttomVerify);
    SettingLauout->addWidget(buttomSeeAll);
    MainLayout->addWidget(MainTable);
    MainLayout->addWidget(UsingWordList);
    this->setLayout(MainLayout);

    connect(buttomUpdate, SIGNAL(clicked()), this, SLOT(slotUpdate()));
    connect(buttomSeeAll, SIGNAL(clicked()), this, SLOT(seeAll()));
    connect(buttomVerify, SIGNAL(clicked()), this, SLOT(verifyAll()));

    connect(UsingWordList, SIGNAL(currentRowChanged(int)), this, SLOT(SelectWordRight(int)));
    connect(MainTable, SIGNAL(itemSelectionChanged()), this, SLOT(SelectCell()));

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
            QString engFirstWord=MyCelectFirstWord.ru.c_str();
            QString engSecondWord=MyCelectSecondWord.ru.c_str();
            if(selected==engFirstWord || selected==engSecondWord){
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
            QTableWidgetItem *item = new QTableWidgetItem; // выделяем память под ячейку
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
                item->setText("");
            }
            MainTable->setItem(row, column, item);
        };
    };
    for(int i=0;i!=tableWord.Using_Word.size();++i){
        new QListWidgetItem(tableWord.Using_Word[i].ru.c_str(), UsingWordList);
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
    UsingWordList=new QListWidget;
    Table *newTable=new Table;
    tableWord=*newTable;
    UsingWordList->clear();
    SecectInUsingWordList.clear();
    LastSelectInMainTable.clear();
    InMainSelect.clear();

    for(int row = 0; row != MainTable->rowCount(); ++row){
        for(int column = 0; column !=MainTable->columnCount(); ++column){
            delete MainTable->item(row,column);
        };
    };
}

void Crossword::seeAll(){
    for(int row = 0; row != MainTable->rowCount(); ++row){
        for(int column = 0; column !=MainTable->columnCount(); ++column){
                char word=tableWord.table[row][column].Value();
                if(word=='#' || word=='@'){continue;}
                QTableWidgetItem *item =MainTable->item(row,column);
                if(item->text()!=QString(word)){
                    item->setBackground(QBrush(QColor(89, 0, 7)));
                    item->setText(QString(word));
                }
                else{
                    item->setBackground(QBrush(QColor(238, 255, 0)));
                }
        };
    };
}

void Crossword::verifyAll(){
    for(int row = 0; row != MainTable->rowCount(); ++row){
        for(int column = 0; column !=MainTable->columnCount(); ++column){
                char word=tableWord.table[row][column].Value();
                if(word=='#' || word=='@'){continue;}
                QTableWidgetItem *item =MainTable->item(row,column);
                if(item->text()!=QString(word)){
                    item->setBackground(QBrush(QColor(89, 0, 7)));
                }
                else{
                    item->setBackground(QBrush(QColor(238, 255, 0)));
                }
        };
    };
}

void Crossword::SelectCell(){
    for(int i=0;i!=SecectInUsingWordList.size();++i){
        SecectInUsingWordList[i]->setBackground(QBrush(QColor(255, 255, 255)));
    };
    SecectInUsingWordList.clear();
    for(int i=0;i!=InMainSelect.size();++i){
        InMainSelect[i]->setBackground(QBrush(QColor(255, 255, 255)));
    };
    InMainSelect.clear();
    QList<QTableWidgetItem *> SelectItem=MainTable->selectedItems();
    if(SelectItem.isEmpty()){
        return;
    }
    QTableWidgetItem *item=SelectItem[0];
    int row=MainTable->row(item);
    int col=MainTable->column(item);
    Word selectFirstWord=tableWord.table[row][col].FirstWord();
    for(int row = 0; row != MainTable->rowCount(); ++row){
        for(int column = 0; column !=MainTable->columnCount(); ++column){
            if(tableWord.table[row][column].FirstWord().eng==selectFirstWord.eng || tableWord.table[row][column].SecondWord().eng==selectFirstWord.eng){
                QTableWidgetItem *goodItem=MainTable->item(row,column);
                goodItem->setBackground(QBrush(QColor(150, 150, 150)));
                InMainSelect.push_back(goodItem);
            }
        }
    };
    for(int i=0;i!=UsingWordList->count();++i){
        QListWidgetItem * QListItem=UsingWordList->item(i);
        if(QListItem->text()==QString(selectFirstWord.ru.c_str())){
            QListItem->setBackground(QBrush(QColor(150, 150, 150)));
            SecectInUsingWordList.push_back(UsingWordList->item(i));
        }
    };
}
