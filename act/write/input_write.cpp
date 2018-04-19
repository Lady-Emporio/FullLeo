#include "input_write.h"
#include <QHBoxLayout>
#include <QHeaderView>
#include <QDebug>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QPushButton>
#include <ctime>        // std::time
#include "backend/error_count.h"
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
                    item(0,i)->setBackground(LeoConst::CONST()->AllQBrushdictPARAMS["FALSEQB"]);
                    if(LeoConst::CONST()->All_BOOL_PARAMS["ERROR"]){
                        ErrorCount::addToDB(TrueWordWORD);
                    }
                }
            }
            if(sum==0){
                if(LeoConst::CONST()->All_BOOL_PARAMS["runAudio"]){
                    LeoConst::CONST()->player->setMedia(QUrl::fromLocalFile(QDir::toNativeSeparators("content\\"+TrueWord+".mp3")));
                    LeoConst::CONST()->player->play();
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
                        this->item(0,column)->setBackground(LeoConst::CONST()->AllQBrushdictPARAMS["TRUEQB"]);
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
                        if(LeoConst::CONST()->All_BOOL_PARAMS["ERROR"]){
                            ErrorCount::addToDB(TrueWordWORD);
                        }
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

InputWrite::InputWrite(QWidget *parent,Leo::Type this_is_status_type) : QWidget(parent),type_this(this_is_status_type)
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
    EverWordList=LeoConst::CONST()->ListWithWordConst;
    if(type_this==Leo::Type::random){
        std::srand ( unsigned ( std::time(0) ) );
        std::random_shuffle(EverWordList.begin(),EverWordList.end(),[](int i){return std::rand()%i;});
    }
    else if(type_this==Leo::Type::sortZ_A){
        std::sort(EverWordList.begin(),EverWordList.end(),[](Word x1,Word x2){return x1.eng<x2.eng;});
    }
    else if(type_this==Leo::Type::sortA_Z){
        std::sort(EverWordList.begin(),EverWordList.end(),[](Word x1,Word x2){return x1.eng>x2.eng;});
    }
    ListWord=EverWordList;
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
        if(LeoConst::CONST()->All_BOOL_PARAMS["EVER"]){
            if(type_this==Leo::Type::random){
                std::srand ( unsigned ( std::time(0) ) );
                std::random_shuffle(EverWordList.begin(),EverWordList.end(),[](int i){return std::rand()%i;});
            }
            ListWord=EverWordList;
        }else{
        TrueLabel->setText("Слова закончились");
        return;
        }
    }
    TrueWord=ListWord.back();
    ListWord.pop_back();
    inputTable->TrueWord=TrueWord.eng.toLower();
    inputTable->TrueWordWORD=TrueWord;
    QString word=TrueWord.eng;
    TrueLabel->setText(TrueWord.ru);
    inputTable->setColumnCount(word.size());
    for(size_t i=0;i!=word.size();++i){
        QTableWidgetItem *item = new QTableWidgetItem;
//        setFontToWidget(item);
        item->setBackground(LeoConst::CONST()->AllQBrushdictPARAMS["WRITECELL"]);
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        inputTable->setItem(0, i, item);
    }
}

OneTableOneRow::OneTableOneRow(QWidget *parent){
    this->setColumnCount(30);
    this->setRowCount(1);
    this->setShowGrid(true);
    for(size_t i=0;i!=this->columnCount();++i){
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setBackground(LeoConst::CONST()->AllQBrushdictPARAMS["NOTUSEQB"]);
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item->setFlags(Qt::ItemFlag::NoItemFlags);
        this->setItem(0, i, item);
    }
    this->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->verticalHeader()->setVisible(false);
    this->horizontalHeader()->setVisible(false);
    for(int i=0;i!=this->rowCount();++i){
        this->setRowHeight(i,20);
    }
    for(int i=0;i!=this->columnCount();++i){
        this->setColumnWidth(i,20);
    };
}

void OneTableOneRow::keyPressEvent(QKeyEvent * event){
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
            for(size_t i=0,textIndexNow=beginTableWord;i!=TrueWord.size();++i,++textIndexNow){
                if(item(0,textIndexNow)->text()!=QString(TrueWord[i])){
                    ++sum;
                    item(0,textIndexNow)->setBackground(LeoConst::CONST()->AllQBrushdictPARAMS["FALSEQB"]);
                }
            }
            if(sum==0){
                if(LeoConst::CONST()->All_BOOL_PARAMS["runAudio"]){
                    LeoConst::CONST()->player->setMedia(QUrl::fromLocalFile(QDir::toNativeSeparators("content\\"+TrueWord+".mp3")));
                    LeoConst::CONST()->player->play();
                };
                emit singal_nextWord();
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
        case Qt::Key_2:{
            int sum=0;
            for(size_t i=0,textIndexNow=beginTableWord;i!=TrueWord.size();++i,++textIndexNow){
                if(item(0,textIndexNow)->text()!=QString(TrueWord[i])){
                    ++sum;
                    item(0,textIndexNow)->setBackground(LeoConst::CONST()->AllQBrushdictPARAMS["FALSEQB"]);
                }
            }
            if(sum==0){
                if(LeoConst::CONST()->All_BOOL_PARAMS["runAudio"]){
                    LeoConst::CONST()->player->setMedia(QUrl::fromLocalFile(QDir::toNativeSeparators("content\\"+TrueWord+".mp3")));
                    LeoConst::CONST()->player->play();
                };
            }
            break;
        }
        default:{
            if(notActiveItem){
                return;
            }
            QString text=event->text().toLower();
            if(text.count()!=0){
                QRegExpValidator r;
                if(type_this!=Leo::contra_Vice_versa){
                    r.setRegExp(QRegExp ("[a-zA-Z]"));
                }else{
                    r.setRegExp(QRegExp ("\\D"));
                }
                int pos = 0;
                if(r.validate(text,pos)==QValidator::Acceptable){
                    int textIndexNow=column-beginTableWord;
                    if(text==QString(TrueWord[textIndexNow])){
                        nowItem->setText(text);
                        this->setStyleSheet("QTableView::item:selected:active { background: rgb(230, 230,230);color:rgb(0,0,0);}");
                        this->item(0,column)->setBackground(LeoConst::CONST()->AllQBrushdictPARAMS["TRUEQB"]);
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
                        if(LeoConst::CONST()->All_BOOL_PARAMS["ERROR"]){
                            ErrorCount::addToDB(TrueWordWORD);
                        }
                        this->setStyleSheet("QTableView::item:selected:active {background: rgb(255, 0,0);color:rgb(0,0,0);}");
                    }
                }
            }
        }
        break;
    }
}
}

OneLongRowTable::OneLongRowTable(QWidget *parent,Leo::Type this_is_status_type) : QWidget(parent),type_this(this_is_status_type)
{
    inputTable=new OneTableOneRow(this);
    inputTable->type_this=type_this;
    setFontToWidget(inputTable);
    TrueLabel=new QLabel(this);
    setFontToWidget(TrueLabel);
    TrueLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QGridLayout *mainLayout=new QGridLayout(this);
    RoundLabel=new QLabel("0",this);
    setFontToWidget(RoundLabel);
    NomberLabel=new QLabel("0",this);
    setFontToWidget(NomberLabel);
    RoundLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    NomberLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QPushButton *nextRound=new QPushButton("next round",this);
    connect(nextRound, SIGNAL(clicked()), this, SLOT(connectNextRound_trigger()));
    connect(inputTable, SIGNAL(singal_needNexRound()), this, SLOT(connectNextRound_trigger()));

    mainLayout->addWidget(TrueLabel,0,0,1,3);
    mainLayout->addWidget(inputTable,1,0,1,3);
    mainLayout->addWidget(nextRound,2,0);
    mainLayout->addWidget(RoundLabel,2,1);
    mainLayout->addWidget(NomberLabel,2,2);
    this->setLayout(mainLayout);

    EverWordList=LeoConst::CONST()->ListWithWordConst;
    if(type_this==Leo::Type::random){
        std::srand ( unsigned ( std::time(0) ) );
        std::random_shuffle(EverWordList.begin(),EverWordList.end(),[](int i){return std::rand()%i;});
    }
    else if(type_this==Leo::Type::sortZ_A){
        std::sort(EverWordList.begin(),EverWordList.end(),[](Word x1,Word x2){return x1.eng<x2.eng;});
    }
    else if(type_this==Leo::Type::sortA_Z){
        std::sort(EverWordList.begin(),EverWordList.end(),[](Word x1,Word x2){return x1.eng>x2.eng;});
    }
    ListWord=EverWordList;
    connect(inputTable, SIGNAL(singal_nextWord()), this, SLOT(connectNext_Word_trigger()));
}

void OneLongRowTable::connectNext_Word_trigger(){
    int round=NomberLabel->text().toInt();
    ++round;
    NomberLabel->setText(QString("").setNum(round));
}

void OneLongRowTable::connectNextRound_trigger(){
    if(ListWord.size()==0){
        if(LeoConst::CONST()->All_BOOL_PARAMS["EVER"]){
            if(type_this==Leo::Type::random){
                std::srand ( unsigned ( std::time(0) ) );
                std::random_shuffle(EverWordList.begin(),EverWordList.end(),[](int i){return std::rand()%i;});
            }
            ListWord=EverWordList;
            int round=RoundLabel->text().toInt();
            ++round;
            RoundLabel->setText(QString("").setNum(round));
        }else{
            TrueLabel->setText("Слова закончились");
            return;
        }
    }
    if(!LeoConst::CONST()->All_BOOL_PARAMS["ACCOUNT"]){
        RoundLabel->hide();
        NomberLabel->hide();
    }else{
        RoundLabel->show();
        NomberLabel->show();
    }
    for(size_t i=0;i!=inputTable->columnCount();++i){
        inputTable->item(0,i)->setText("");
        inputTable->item(0,i)->setFlags(Qt::ItemFlag::NoItemFlags);
        inputTable->item(0,i)->setBackground(LeoConst::CONST()->AllQBrushdictPARAMS["NOTUSEQB"]);
    }
    TrueWord=ListWord.back();
    ListWord.pop_back();
    QString word;
    if(type_this!=Leo::contra_Vice_versa){
        inputTable->TrueWord=TrueWord.eng.toLower();
        inputTable->TrueWordWORD=TrueWord;
        word=TrueWord.eng;
        TrueLabel->setText(TrueWord.ru);
    }else{
        inputTable->TrueWord=TrueWord.ru.toLower();
        inputTable->TrueWordWORD=TrueWord;
        word=TrueWord.ru;
        TrueLabel->setText(TrueWord.eng);
    }
    int haldWord=word.size()/2;
    int startTable=inputTable->columnCount()/2-haldWord;
    inputTable->beginTableWord=startTable;
    if(startTable+word.size()>=inputTable->columnCount()){
        TrueLabel->setText("columnCount large");
        return;
    }
    else if(startTable<0){
        TrueLabel->setText("columnCount small");
        return;
    }
    for(size_t i=startTable,n=0;n!=word.size();++i,++n){
        QTableWidgetItem *item=inputTable->item(0,i);
        item->setBackground(LeoConst::CONST()->AllQBrushdictPARAMS["WRITECELL"]);
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    }
    inputTable->setCurrentIndex(inputTable->model()->index(0,startTable));
}
