#include "crossword.h"
#include <QBrush>
#include <QString>
#include <QDebug>
#include <QRegExpValidator>
Crossword::Crossword(QWidget *parent) : QWidget(parent)
{
    tableWord=new Table;
    QHBoxLayout *MainLayout=new QHBoxLayout(this);
    QVBoxLayout *SettingLauout=new QVBoxLayout;
    ErrorLabel=new QLabel("Все в порядке");
    QPushButton *buttomVerify=new QPushButton("verify");
    QPushButton *buttomSeeAll=new QPushButton("Look,see all");
    QPushButton *buttomUpdate=new QPushButton("update");

    MainTable=new TableGui;
    MainTable->setColumnCount(CONST->TABLE_COL());
    MainTable->setRowCount(CONST->TABLE_ROW());
    UsingWordList=new QListWidget;
    UsingWordList->setMaximumWidth(100);

    for(int i=0;i!=CONST->TABLE_ROW();++i){
        MainTable->setColumnWidth(i,20);
        MainTable->setRowHeight(i,20);
    };

    this->resize(CONST->TABLE_ROW()*CONST->ROWHEIGHT()+(CONST->MARGIN1()*3)+UsingWordList->width(),(CONST->TABLE_COL()*CONST->COLUMNWIDTH())+CONST->MARGIN1());

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

    MainTable->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    MainTable->setSelectionMode(QAbstractItemView::SingleSelection);//выделяем только один элемент
}

void Crossword::SelectWordRight(int x){
    if(x==-1){
        LastSelectInMainTable.clear();
        InMainSelect.clear();
        return;
    }
    for(int i=0;i!=InMainSelect.size();++i){
        InMainSelect[i]->setBackground(DEFAULTQB);
    };
    InMainSelect.clear();
    for(int i=0;i!=LastSelectInMainTable.size();++i){
        LastSelectInMainTable[i]->setBackground(DEFAULTQB);
    };
    LastSelectInMainTable.clear();

    QString selected=UsingWordList->item(x)->text();
    ErrorLabel->setText(selected);
    for(int row = 0; row != MainTable->rowCount(); row++){
        for(int column = 0; column !=MainTable->columnCount(); column++){
            Word MyCelectFirstWord=tableWord->table[row][column].FirstWord();
            Word MyCelectSecondWord=tableWord->table[row][column].SecondWord();
            QString engFirstWord=MyCelectFirstWord.ru.c_str();
            QString engSecondWord=MyCelectSecondWord.ru.c_str();
            if(selected==engFirstWord || selected==engSecondWord){
                    QTableWidgetItem *itemNow=MainTable->item(row,column);
                    itemNow->setBackground(ACTIVEINTABLEQB);
                    LastSelectInMainTable.push_back(itemNow);
            }
        };
    };
}

void Crossword::UpdateMainTable(){
    for(int row = 0; row != CONST->TABLE_ROW(); ++row){
        for(int column = 0; column !=CONST->TABLE_COL(); ++column){
            QTableWidgetItem *item = new QTableWidgetItem; // выделяем память под ячейку
            char word=tableWord->table[row][column].Value();
            if(word=='@'){
                item->setText(" ");
                item->setFlags(Qt::NoItemFlags);
                item->setBackground(NOTUSEQB);
            }
            else if(word=='#'){
                item->setFlags(Qt::NoItemFlags);
                item->setText(QString(word));
                item->setBackground(GRIDQB);
            }
            else{
                item->setText("");
            }
            MainTable->setItem(row, column, item);
        };
    };
    for(int i=0;i!=tableWord->Using_Word.size();++i){
        new QListWidgetItem(tableWord->Using_Word[i].ru.c_str(), UsingWordList);
    };
}

void Crossword::slotUpdate(){
    clearToNextPound();
    std::string error;
    if(!tableWord->run(&error)){
        ErrorLabel->setText(error.c_str());
    }
    UpdateMainTable();
}

void Crossword::clearToNextPound(){
    delete tableWord;
    tableWord=new Table;
    MainTable->clear();
    UsingWordList->clear();
    SecectInUsingWordList.clear();
}

void Crossword::seeAll(){
    for(int row = 0; row != MainTable->rowCount(); ++row){
        for(int column = 0; column !=MainTable->columnCount(); ++column){
                char word=tableWord->table[row][column].Value();
                if(word=='#' || word=='@'){continue;}
                QTableWidgetItem *item =MainTable->item(row,column);
                if(item->text()!=QString(word)){
                    item->setBackground(FALSEQB);
                    item->setText(QString(word));
                }
                else{
                    item->setBackground(TRUEQB);
                }
        };
    };
}

void Crossword::verifyAll(){
    for(int row = 0; row != MainTable->rowCount(); ++row){
        for(int column = 0; column !=MainTable->columnCount(); ++column){
                char word=tableWord->table[row][column].Value();
                if(word=='#' || word=='@'){continue;}
                QTableWidgetItem *item =MainTable->item(row,column);
                if(item->text()!=QString(word)){
                    item->setBackground(FALSEQB);
                }
                else{
                    item->setBackground(TRUEQB);
                }
        };
    };
}

void Crossword::SelectCell(){
    for(int i=0;i!=SecectInUsingWordList.size();++i){
        SecectInUsingWordList[i]->setBackground(DEFAULTQB);
    };
    SecectInUsingWordList.clear();
    for(int i=0;i!=InMainSelect.size();++i){
        InMainSelect[i]->setBackground(DEFAULTQB);
    };
    InMainSelect.clear();
    for(int i=0;i!=LastSelectInMainTable.size();++i){
        LastSelectInMainTable[i]->setBackground(DEFAULTQB);
    };
    LastSelectInMainTable.clear();
    QList<QTableWidgetItem *> SelectItem=MainTable->selectedItems();
    if(SelectItem.isEmpty()){
        return;
    }
    QTableWidgetItem *item=SelectItem[0];
    int row=MainTable->row(item);
    int col=MainTable->column(item);
    Word selectFirstWord=tableWord->table[row][col].FirstWord();
    for(int row = 0; row != MainTable->rowCount(); ++row){
        for(int column = 0; column !=MainTable->columnCount(); ++column){
            if(tableWord->table[row][column].FirstWord().eng==selectFirstWord.eng || tableWord->table[row][column].SecondWord().eng==selectFirstWord.eng){
                QTableWidgetItem *goodItem=MainTable->item(row,column);
                goodItem->setBackground(ACTIVEINTABLEQB);
                InMainSelect.push_back(goodItem);
            }
        }
    };
    for(int i=0;i!=UsingWordList->count();++i){
        QListWidgetItem * QListItem=UsingWordList->item(i);
        if(QListItem->text()==QString(selectFirstWord.ru.c_str())){
            QListItem->setBackground(ACTIVELISTQB);
            SecectInUsingWordList.push_back(UsingWordList->item(i));
            UsingWordList->scrollToItem(UsingWordList->item(i),QAbstractItemView::PositionAtCenter );
        }
    };
}

void TableGui::keyPressEvent(QKeyEvent * event){
    if(event->type()==QEvent::KeyPress){
        QString text=event->text();
        QList<QTableWidgetItem *> IselectItem=this->selectedItems();
        if(IselectItem.size()!=0){
            QTableWidgetItem * item=IselectItem[0];
            if(text.count()!=0){
                QRegExpValidator r(QRegExp ("[a-z]"), 0);
                int pos = 0;
                if(r.validate(text,pos)==QValidator::Acceptable){
                    item->setText(text);
                }
            }
            int column=this->column(item);
            int row=this->row(item);
            switch(event->key()){
                case Qt::Key_Left:{
                    int left=column-1;
                    if(NotInTableIndexError(left)){break;}
//                    if(this->item(row,column-1)->flags()==Qt::NoItemFlags){
//                        qDebug()<<item->flags();
//                    }
                    this->setCurrentIndex(this->model()->index(row,left));
                    break;
                }case Qt::Key_Right:{
                    int right=column+1;
                    if(NotInTableIndexError(right)){break;}
                    this->setCurrentIndex(this->model()->index(row,right));
                    break;
                }case Qt::Key_Up:{
                    int up=row-1;
                    if(NotInTableIndexError(up)){break;}
                    this->setCurrentIndex(this->model()->index(up,column));
                    break;
                }case Qt::Key_Down:{
                    int down=row+1;
                    if(NotInTableIndexError(down)){break;}
                    this->setCurrentIndex(this->model()->index(down,column));
                    break;}
            }
        }
    }
}
