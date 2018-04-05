#include "input_write.h"
#include <QHBoxLayout>
#include <QHeaderView>
#include <QDebug>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QPushButton>

TableWrite::TableWrite(QWidget *parent) : QTableWidget(parent){
    this->setRowCount(1);
    this->verticalHeader()->setVisible(false);
    this->horizontalHeader()->setVisible(false);
    this->verticalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    this->verticalHeader()->setStretchLastSection( true );
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setStyleSheet(
                "QTableView::item:selected:active {"
                "background: rgb(230, 230,230);color:rgb(0,0,0);}"
    );
}

void TableWrite::keyPressEvent(QKeyEvent *event){
    if(event->type()==QEvent::KeyPress){
        QList<QTableWidgetItem *> IselectItem=this->selectedItems();
        bool notActiveItem=false;
        QTableWidgetItem * nowItem=0;
        int column=0;
        if(IselectItem.size()==0){
            notActiveItem=true;
        }else{
            nowItem=IselectItem[0];
            column=this->column(nowItem);
        }
        switch(event->key()){
        case Qt::Key_Enter:
        case Qt::Key_Return:{
            int sum=0;
            for(size_t i=0;i!=this->columnCount();++i){
                if(item(0,i)->text()!=QString(TrueWord[i])){
                    ++sum;
                    item(0,i)->setBackground(LeoConst::CONST()->FALSEQB);
                }
            }
            if(sum==0){
                if(LeoConst::CONST()->runAudio){
                    LeoConst::player->setMedia(QUrl::fromLocalFile(QDir::toNativeSeparators("content\\"+TrueWord+".mp3")));
                    LeoConst::player->play();
                };
                emit singal_needNexRound();
            }
            break;
            }
        case Qt::Key_Left:{
            for(size_t i=1;i!=columnCount();++i){
                int next=column-i;
                if(next>=0 && item(0,next)->flags()!=Qt::NoItemFlags){
                    this->setCurrentIndex(this->model()->index(0,next));
                    break;
                }
            }
            break;
        }
        case Qt::Key_Right:{
            for(size_t i=1;i!=columnCount();++i){
                int next=column+i;
                if(next<columnCount() && item(0,next)->flags()!=Qt::NoItemFlags){
                    this->setCurrentIndex(this->model()->index(0,next));
                    break;
                }
            }
            break;
        }
        default:{
            if(notActiveItem){
                return;
            }
            QString text=event->text().toLower();
            if(text.count()!=0){
                QRegExpValidator r(QRegExp ("[a-zA-Z]"), 0);
                int pos = 0;
                if(r.validate(text,pos)==QValidator::Acceptable){
                    if(text==QString(TrueWord[column])){
                        nowItem->setText(text);
                        this->setStyleSheet("QTableView::item:selected:active { background: rgb(230, 230,230);color:rgb(0,0,0);}");
                        this->item(0,column)->setBackground(LeoConst::CONST()->TRUEQB);
                        this->item(0,column)->setFlags(Qt::NoItemFlags);
                        if(column+1<this->columnCount() && this->item(0,column+1)->flags()!=Qt::NoItemFlags){
                            this->setCurrentIndex(this->model()->index(0,column+1));
                        }else{
                            for(size_t i=columnCount()-1;i!=-1;--i){
                                if(this->item(0,i)->flags()!=Qt::NoItemFlags){
                                    this->setCurrentIndex(this->model()->index(0,i));
                                    break;
                                }
                            }
                        }
                    }
                    else{
                        this->setStyleSheet("QTableView::item:selected:active {background: rgb(255, 0,0);color:rgb(0,0,0);}");
                    }
                }
            }
        }
        break;
        }//end  switch
    }
}

void TableWrite::resizeEvent(QResizeEvent *event){
    size_t intMaxColumn=this->columnCount();
    if (intMaxColumn!=0){
        QRect viewRect = this->rect();
        size_t column0_width = viewRect.width() * (100/intMaxColumn*0.01);//Calculate first column's width as 80% of QTableView's width.
        for(size_t i=0;i!=intMaxColumn;++i){
            this->setColumnWidth( i, column0_width );
        }
    }
}

InputWrite::InputWrite(QWidget *parent) : QWidget(parent)
{
    inputTable=new TableWrite(this);
    setFontToWidget(inputTable);
    TrueLabel=new QLabel(this);
    setFontToWidget(TrueLabel);
    TrueLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    QHBoxLayout *settingAndImage=new QHBoxLayout;
    mainLayout->addWidget(TrueLabel);
    mainLayout->addWidget(inputTable);
    mainLayout->addLayout(settingAndImage);

    QPushButton *nextRound=new QPushButton(this);
    setFontToWidget(nextRound);
    nextRound->setText("next round");
    settingAndImage->addWidget(nextRound);
    this->setLayout(mainLayout);
    ListWord=LeoConst::CONST()->ListWithWordConst;
    connect(nextRound, SIGNAL(clicked()), this, SLOT(connectNextRound_trigger()));
    connect(inputTable, SIGNAL(singal_needNexRound()), this, SLOT(connectNextRound_trigger()));

}

void InputWrite::connectNextRound_trigger(){
    run();
    inputTable->setCurrentIndex(inputTable->model()->index(0,0));
    size_t intMaxColumn=inputTable->columnCount();
    if (intMaxColumn!=0){
        QRect viewRect = inputTable->rect();
        size_t column0_width = viewRect.width() * (100/intMaxColumn*0.01);//Calculate first column's width as 80% of QTableView's width.
        for(size_t i=0;i!=intMaxColumn;++i){
            inputTable->setColumnWidth( i, column0_width );
        }
    }
}

void InputWrite::run(){
    if(ListWord.size()==0){
        TrueLabel->setText("Слова закончились");
        return;
    }
    TrueWord=ListWord.back();
    ListWord.pop_back();
    inputTable->TrueWord=TrueWord.eng.toLower();
    QString word=TrueWord.eng;
    TrueLabel->setText(TrueWord.ru);
    inputTable->setColumnCount(word.size());
    for(size_t i=0;i!=word.size();++i){
        QTableWidgetItem *item = new QTableWidgetItem;
//        setFontToWidget(item);
        item->setBackground(LeoConst::CONST()->WRITECELL);
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        inputTable->setItem(0, i, item);
    }
}
