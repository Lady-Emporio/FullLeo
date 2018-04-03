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
        QString text=event->text();
        QList<QTableWidgetItem *> IselectItem=this->selectedItems();
        if(IselectItem.size()!=0){
            QTableWidgetItem * item=IselectItem[0];
            if(text.count()!=0){
                QRegExpValidator r(QRegExp ("[a-z]"), 0);
                int pos = 0;
                int column=this->column(item);
                if(r.validate(text,pos)==QValidator::Acceptable){
                    if(text==QString(TrueWord[column])){
                        item->setText(text);
                        this->setStyleSheet(
                                    "QTableView::item:selected:active {"
                                    "background: rgb(230, 230,230);color:rgb(0,0,0);}"
                        );
                        if(column+1!=this->columnCount()){
                            this->setCurrentIndex(this->model()->index(0,column+1));
                        }
                        if(column-1>=0){
                            this->item(0,column-1)->setBackground(LeoConst::CONST()->WRITECELL);
                        }
                    }else{
//                        item->setBackground(LeoConst::CONST()->FALSEQB);
                        this->setStyleSheet(
                                    "QTableView::item:selected:active {"
                                    "background: rgb(255, 0,0);color:rgb(0,0,0);}"
                        );
                    }
                }
            }
        }
    }
}

void TableWrite::resizeEvent(QResizeEvent *event){
    size_t intMaxColumn=this->columnCount();
    if (intMaxColumn!=0){
        QRect viewRect = this->rect();
        size_t column0_width = viewRect.width() * (100/intMaxColumn*0.01);//Calculate first column's width as 80% of QTableView's width.
        for(size_t i=0;i!=column0_width-1;++i){
            this->setColumnWidth( i, column0_width );
        }
    }
}

InputWrite::InputWrite(QWidget *parent) : QWidget(parent)
{
    inputTable=new TableWrite(this);
    TrueLabel=new QLabel(this);
    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    QHBoxLayout *settingAndImage=new QHBoxLayout;
    mainLayout->addWidget(TrueLabel);
    mainLayout->addWidget(inputTable);
    mainLayout->addLayout(settingAndImage);

    QPushButton *nextRound=new QPushButton(this);
    nextRound->setText("next round");
    settingAndImage->addWidget(nextRound);
    this->setLayout(mainLayout);
    ListWord=LeoConst::CONST()->ListWithWordConst;
    connect(nextRound, SIGNAL(clicked()), this, SLOT(connectNextRound_trigger()));
}
void InputWrite::connectNextRound_trigger(){
    run();
    size_t intMaxColumn=inputTable->columnCount();
    if (intMaxColumn!=0){
        QRect viewRect = inputTable->rect();
        size_t column0_width = viewRect.width() * (100/intMaxColumn*0.01);//Calculate first column's width as 80% of QTableView's width.
        for(size_t i=0;i!=column0_width-1;++i){
            inputTable->setColumnWidth( i, column0_width );
        }
    }
}

void InputWrite::run(){
    TrueWord=ListWord.back();
    ListWord.pop_back();
    inputTable->TrueWord=TrueWord.eng;
    QString word=TrueWord.eng;
    TrueLabel->setText(TrueWord.ru);
    inputTable->setColumnCount(word.size());
    for(size_t i=0;i!=word.size();++i){
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setBackground(LeoConst::CONST()->WRITECELL);
        inputTable->setItem(0, i, item);
    }
}
