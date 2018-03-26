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
    inCrosswordTableRowMax=CONST->TABLE_ROW();
    inCrosswordTableColMax=CONST->TABLE_COL();
    MainTable->setColumnCount(inCrosswordTableColMax);
    MainTable->setRowCount(inCrosswordTableRowMax);
    UsingWordList=new QListWidget;
    UsingWordList->setMaximumWidth(100);

    for(int i=0;i!=inCrosswordTableRowMax;++i){
        MainTable->setRowHeight(i,20);
    }
    for(int i=0;i!=inCrosswordTableColMax;++i){
        MainTable->setColumnWidth(i,20);
    };
    this->resize(inCrosswordTableRowMax*CONST->ROWHEIGHT()+(CONST->MARGIN1()*3)+UsingWordList->width(),(inCrosswordTableColMax*CONST->COLUMNWIDTH())+CONST->MARGIN1());

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
        InMainSelect[i]->setBackground(CONST->DEFAULTQB);
    };
    InMainSelect.clear();
    for(int i=0;i!=LastSelectInMainTable.size();++i){
        LastSelectInMainTable[i]->setBackground(CONST->DEFAULTQB);
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
                    itemNow->setBackground(CONST->ACTIVEINTABLEQB);
                    LastSelectInMainTable.push_back(itemNow);
            }
        };
    };
}

void Crossword::UpdateMainTable(){
    for(int row = 0; row != inCrosswordTableRowMax; ++row){
        for(int column = 0; column !=inCrosswordTableColMax; ++column){
            QTableWidgetItem *item = new QTableWidgetItem; // выделяем память под ячейку
            char word=tableWord->table[row][column].Value();
            if(word=='@'){
                item->setText(" ");
                item->setFlags(Qt::NoItemFlags);
                item->setBackground(CONST->NOTUSEQB);
            }
            else if(word=='#'){
                item->setFlags(Qt::NoItemFlags);
                if(CONST->GRID()){
                    item->setText(QString(word));
                }else{
                    item->setText(" ");
                }
                item->setBackground(CONST->GRIDQB);
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
    inCrosswordTableColMax=CONST->TABLE_COL();
    inCrosswordTableRowMax=CONST->TABLE_ROW();
    clearToNextPound();
    std::string error;
    if(!tableWord->run(&error,CONST->ALGORITMH())){
        ErrorLabel->setText(error.c_str());
    }
    UpdateMainTable();
}

void Crossword::clearToNextPound(){
    delete tableWord;
    tableWord=new Table;
    MainTable->clear();
    MainTable->tableForQKeyEvent=tableWord;
    if(MainTable->columnCount()!=inCrosswordTableColMax){
        MainTable->setColumnCount(inCrosswordTableColMax);
    }
    for(int i=0;i!=inCrosswordTableColMax;++i){
        MainTable->setColumnWidth(i,20);
    };
    if(MainTable->rowCount()!=inCrosswordTableRowMax){
        MainTable->setRowCount(inCrosswordTableRowMax);
    }
    for(int i=0;i!=inCrosswordTableRowMax;++i){
        MainTable->setRowHeight(i,20);
    }
    UsingWordList->clear();
    SecectInUsingWordList.clear();

}

void Crossword::seeAll(){
    MainTable->selectionModel()->clearSelection();//clear background now focus element
    for(int row = 0; row != MainTable->rowCount(); ++row){
        for(int column = 0; column !=MainTable->columnCount(); ++column){
                char word=tableWord->table[row][column].Value();
                if(word=='#' || word=='@'){continue;}
                QTableWidgetItem *item =MainTable->item(row,column);
                if(item->text()!=QString(word)){
                    item->setBackground(CONST->FALSEQB);
                    item->setText(QString(word));
                }
                else{
                    item->setBackground(CONST->TRUEQB);
                }
        };
    };
}

void Crossword::verifyAll(){
    MainTable->selectionModel()->clearSelection();//clear background now focus element

    int maxRow=inCrosswordTableRowMax;
    int maxCol=inCrosswordTableColMax;
    for(int row = 0; row != maxRow; ++row){
        for(int column = 0; column !=maxCol; ++column){
                char word=tableWord->table[row][column].Value();
                if(word=='#' || word=='@'){continue;}
                QTableWidgetItem *item =MainTable->item(row,column);
                if(item->text()!=QString(word)){
                    item->setBackground(CONST->FALSEQB);
                }
                else{
                    item->setBackground(CONST->TRUEQB);
                }
        };
    };
}

void Crossword::SelectCell(){
    for(int i=0;i!=SecectInUsingWordList.size();++i){
        SecectInUsingWordList[i]->setBackground(CONST->DEFAULTQB);
    };
    SecectInUsingWordList.clear();
    for(int i=0;i!=InMainSelect.size();++i){
        InMainSelect[i]->setBackground(CONST->DEFAULTQB);
    };
    InMainSelect.clear();
    for(int i=0;i!=LastSelectInMainTable.size();++i){
        LastSelectInMainTable[i]->setBackground(CONST->DEFAULTQB);
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
                goodItem->setBackground(CONST->ACTIVEINTABLEQB);
                InMainSelect.push_back(goodItem);
            }
        }
    };
    for(int i=0;i!=UsingWordList->count();++i){
        QListWidgetItem * QListItem=UsingWordList->item(i);
        if(QListItem->text()==QString(selectFirstWord.ru.c_str())){
            QListItem->setBackground(CONST->ACTIVELISTQB);
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
                    if(CONST->AUTOCOMPLETION()){
                        int column=this->column(item);
                        int row=this->row(item);
                        //word can be vertical (up to-> down) or horizontal (left to-> right)
                        static bool GateToNewWord=true;
                        static Word selectFirstWord;

                        if(GateToNewWord){
                            selectFirstWord=tableForQKeyEvent->table[row][column].FirstWord();
                            GateToNewWord=false;
                        }
                        int sumIfNeedNewWord=0;
                        int down=row+1;
                        int right=column+1;

                        if(!NotInTableIndexError(down,vertical)){
                            if(!(tableForQKeyEvent->table[down][column].FirstWord().eng==selectFirstWord.eng || tableForQKeyEvent->table[down][column].SecondWord().eng==selectFirstWord.eng)){
                                sumIfNeedNewWord+=1;
                            }
                        }

                        if(!NotInTableIndexError(right,horizontal)){
                            if(!(tableForQKeyEvent->table[row][right].FirstWord().eng==selectFirstWord.eng || tableForQKeyEvent->table[row][right].SecondWord().eng==selectFirstWord.eng)){
                                sumIfNeedNewWord+=1;
                            }
                        }
                        if(sumIfNeedNewWord==2){
                            GateToNewWord=true;
                        }



                        if(!NotInTableIndexError(down,vertical)){
                            if(tableForQKeyEvent->table[down][column].FirstWord().eng==selectFirstWord.eng || tableForQKeyEvent->table[down][column].SecondWord().eng==selectFirstWord.eng){
                                this->setCurrentIndex(this->model()->index(down,column));
                                return;
                            }
                        }
                        if(!NotInTableIndexError(right,horizontal)){
                            if(tableForQKeyEvent->table[row][right].FirstWord().eng==selectFirstWord.eng || tableForQKeyEvent->table[row][right].SecondWord().eng==selectFirstWord.eng){
                                this->setCurrentIndex(this->model()->index(row,right));
                                return;
                            }
                        }
                    }
                }
            }
            int column=this->column(item);
            int row=this->row(item);
            switch(event->key()){
                case Qt::Key_Left:{
                    int left=column-1;
                    if(NotInTableIndexError(left,horizontal)){break;}
                    if(event->modifiers()==Qt::ControlModifier){
                        for(int i=left;i!=-1;--i){
                            if(this->item(row,i)->flags()==Qt::NoItemFlags || i==0){
                                if(i==0 && this->item(row,i)->flags()!=Qt::NoItemFlags){
                                    this->setCurrentIndex(this->model()->index(row,i+1));
                                }else{
                                    this->setCurrentIndex(this->model()->index(row,i));
                                }
                                return;
                            }
                        }
                    }
                    if(CONST->JUMP()){
                        if(this->item(row,left)->flags()==Qt::NoItemFlags){
                            for(int i=left;i!=-1;--i){
                                if(this->item(row,i)->flags()!=Qt::NoItemFlags){
                                    this->setCurrentIndex(this->model()->index(row,i));
                                    return;
                                }
                            }
                        }
                    }
                    this->setCurrentIndex(this->model()->index(row,left));
                    break;
                }case Qt::Key_Right:{
                    int right=column+1;
                    if(NotInTableIndexError(right,horizontal)){break;}
                    if(event->modifiers()==Qt::ControlModifier){
                        for(int i=right;i!=this->columnCount();++i){
                            if(this->item(row,i)->flags()==Qt::NoItemFlags || i==this->columnCount()-1){
                                if(i==this->columnCount()-1 && this->item(row,i)->flags()!=Qt::NoItemFlags){
                                    this->setCurrentIndex(this->model()->index(row,i-1));
                                }else{
                                    this->setCurrentIndex(this->model()->index(row,i));
                                }
                                return;
                            }
                        }

                    }
                    if(CONST->JUMP()){
                        if(this->item(row,right)->flags()==Qt::NoItemFlags){
                            for(int i=right;i!=this->columnCount();++i){
                                if(this->item(row,i)->flags()!=Qt::NoItemFlags){
                                    this->setCurrentIndex(this->model()->index(row,i));
                                    return;
                                }
                            }
                        }
                    }
                    this->setCurrentIndex(this->model()->index(row,right));
                    break;
                }case Qt::Key_Up:{
                    int up=row-1;
                    if(NotInTableIndexError(up,vertical)){break;}
                    if(event->modifiers()==Qt::ControlModifier){
                        for(int i=up;i!=-1;--i){
                            if(this->item(i,column)->flags()==Qt::NoItemFlags || i==0){
                                if(i==0 && this->item(i,column)->flags()!=Qt::NoItemFlags){
                                    this->setCurrentIndex(this->model()->index(i+1,column));
                                }else{
                                    this->setCurrentIndex(this->model()->index(i,column));
                                }
                                return;
                            }
                        }
                    }
                    if(CONST->JUMP()){
                        if(this->item(up,column)->flags()==Qt::NoItemFlags){
                            for(int i=up;i!=-1;--i){
                                if(this->item(i,column)->flags()!=Qt::NoItemFlags){
                                    this->setCurrentIndex(this->model()->index(i,column));
                                    return;
                                }
                            }
                        }
                    }
                    this->setCurrentIndex(this->model()->index(up,column));
                    break;
                }case Qt::Key_Down:{
                    int down=row+1;
                    if(NotInTableIndexError(down,vertical)){break;}
                    if(event->modifiers()==Qt::ControlModifier){
                        for(int i=down;i!=this->rowCount();++i){
                            if(this->item(i,column)->flags()==Qt::NoItemFlags || i==this->rowCount()-1){
                                if(i==this->rowCount()-1 && this->item(i,column)->flags()!=Qt::NoItemFlags){
                                    this->setCurrentIndex(this->model()->index(i-1,column));
                                }else{
                                    this->setCurrentIndex(this->model()->index(i,column));

                                }
                                return;
                            }
                        }
                    }
                    if(CONST->JUMP()){
                        if(this->item(down,column)->flags()==Qt::NoItemFlags){
                            for(int i=down;i!=this->rowCount();++i){
                                if(this->item(i,column)->flags()!=Qt::NoItemFlags){
                                    this->setCurrentIndex(this->model()->index(i,column));
                                    return;
                                }
                            }
                        }
                    }
                    this->setCurrentIndex(this->model()->index(down,column));
                    break;}
            case Qt::Key_Backspace:
            case Qt::Key_Delete:
                    this->item(row,column)->setText("");
                    break;
            }
        }
    }
}
