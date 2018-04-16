#include "x_y.h"
#include <ctime>
#include "QTime"
#include <algorithm>
#include <QGridLayout>
#include "backend/error_count.h"
XY::XY(QWidget *parent) : QWidget(parent)
{
    this->setObjectName("XY");
    main_Label=new QLabel("We are",this);
    main_Label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    setFontToWidget(main_Label);
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    main_Label->setSizePolicy(sizePolicy);
    ImageLabel=new QLabel("Image",this);
    ImageLabel->setSizePolicy(sizePolicy);
    ImageLabel->setMaximumHeight(180);
    ImageLabel->setMaximumWidth(180);
    QGridLayout *mainLayout=new QGridLayout(this);
    MaxButton=LeoConst::CONST()->All_INT_PARAMS["COUNT_BUTTOM"];
    for(int i=0;i!=MaxButton;++i){
        QPushButton *nextButton=new QPushButton("we are",this);
        nextButton->setMaximumHeight(LeoConst::CONST()->All_INT_PARAMS["FONT_SIZE"]+16);
        nextButton->setMaximumWidth(250);
        nextButton->setStyleSheet(LeoConst::CONST()->All_QString_PARAMS["DEFAULT_BUTTOM_COLOR"]);
        setFontToWidget(nextButton);
        nextButton->setSizePolicy(sizePolicy);
        mainLayout->addWidget(nextButton,i,1);
        connect(nextButton, SIGNAL(clicked()), this, SLOT(connectSelectWord()));
        nextButton->setObjectName(QString("WeAreButtonMy25/03/2018").setNum(i));
        listButton.push_back(nextButton);
    }
    RoundForLabel=0;
    NomberForLabel=0;
    RoundLabel=new QLabel(QString("").setNum(RoundForLabel),this);
    NomberLabel=new QLabel(QString("").setNum(NomberForLabel),this);
    this->setLayout(mainLayout);
    mainLayout->addWidget(main_Label,0,0);
    mainLayout->addWidget(ImageLabel,1,0,MaxButton-1,1);
    mainLayout->addWidget(RoundLabel,MaxButton,0);
    mainLayout->addWidget(NomberLabel,MaxButton,1);
    EverWordList=LeoConst::CONST()->ListWithWordConst;
    sort(EverWordList.begin(),EverWordList.end(),[](Word x1,Word x2) {return (x1.eng<x2.eng);}); //убираю дубли
    auto last=unique(EverWordList.begin(),EverWordList.end(),[](Word x1,Word x2) {return (x1.eng==x2.eng);});
    EverWordList.erase(last, EverWordList.end());
    ListWord=EverWordList;
    if (ListWord.size()<MaxButton || ListWord.size()==0){
            main_Label->setText(QString("Small size: ")+QString("").setNum(ListWord.size()));
            return;
    };
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    std::vector<int> UniqueWord;
    while(UniqueWord.size()!=MaxButton){
        int x=qrand()%ListWord.size();
        auto it = std::find (UniqueWord.begin(), UniqueWord.end(), x);
        if (it == UniqueWord.end()){
            UniqueWord.push_back(x);
        }
    }
    for(size_t i=0;i!=UniqueWord.size();++i){
        sizeWordinLastSizeEnd.push_back(ListWord[UniqueWord[i]]);
    }
    std::srand ( (int)time(0));
    random_shuffle ( ListWord.begin(), ListWord.end(),[](int i) {return std::rand()%i;});
}

void XY::connectSelectWord(){
    if(main_Label->text()=="We are"){
        nextRound();
        return;
    }
    QObject* obj = sender();
    QPushButton *button=findChild<QPushButton*>(obj->objectName());
    if(button->text()==QString(TrueWord.ru)){
        if(LeoConst::CONST()->All_BOOL_PARAMS["runAudio"]){
            LeoConst::CONST()->player->setMedia(QUrl::fromLocalFile(QDir::toNativeSeparators("content\\"+TrueWord.eng+".mp3")));
            LeoConst::CONST()->player->play();
        };
        static bool go_next=false;
         if (!go_next){
             if(LeoConst::CONST()->All_BOOL_PARAMS["runImage"]){
                 QPixmap image("./content/"+TrueWord.eng+".png");
                 ImageLabel->setPixmap(image);
                 ImageLabel->show();
             }
             button->setStyleSheet(LeoConst::CONST()->All_QString_PARAMS["TRUE_ANSWER_COLOR"]);
             go_next=true;
         }
         else{
             go_next=false;
             nextRound();
        }
    }else{
        if(LeoConst::CONST()->All_BOOL_PARAMS["ERROR"]){
            ErrorCount::addToDB(TrueWord);
        }
        button->setStyleSheet(LeoConst::CONST()->All_QString_PARAMS["FALSE_ANSWER_COLOR"]);
    }
}

void XY::nextRound(){
    for(size_t i=0;i!=listButton.size();++i){
        listButton[i]->setStyleSheet(LeoConst::CONST()->All_QString_PARAMS["DEFAULT_BUTTOM_COLOR"]);
    }
    if (ListWord.size()<=0){
            if(LeoConst::CONST()->All_BOOL_PARAMS["EVER"]){
                ++RoundForLabel;
                RoundLabel->setText(QString("").setNum(RoundForLabel));
                ListWord=EverWordList;
            }
            else{
                main_Label->setText(QString("End size: ")+QString("").setNum(ListWord.size()));
                return;
            }
    };
    ++NomberForLabel;
    std::vector<Word>UsingWord;
    TrueWord=ListWord.back();
    ListWord.pop_back();
    UsingWord.push_back(TrueWord);
    Word nextWord=TrueWord;
    nextWord.Round=RoundForLabel;
    nextWord.Nomber=NomberForLabel;
    UsingWordForStory.push_back(nextWord);
    for(size_t i=1;UsingWord.size()!=MaxButton;++i){
        if(i>=ListWord.size()){
            break;
        }else{
            UsingWord.push_back(ListWord[ListWord.size()-i]);
        }
    };
    std::vector<Word>updateLastSizeEnd=sizeWordinLastSizeEnd;
    random_shuffle ( UsingWord.begin(), UsingWord.end(),[](int i) {return std::rand()%i;});
    if (ListWord.size()+1<=MaxButton){
        for(size_t i=0;i!=listButton.size();++i){
            if(i<UsingWord.size()){
                listButton[i]->setText(UsingWord[i].ru);
            }
            else{
                Word backWord=sizeWordinLastSizeEnd.back();
                sizeWordinLastSizeEnd.pop_back();
                listButton[i]->setText(backWord.ru);
               }
        }
        sizeWordinLastSizeEnd=updateLastSizeEnd;
    }else{
        for(size_t i=0;i!=listButton.size();++i){
            listButton[i]->setText(UsingWord[i].ru);
        }
    }
    ImageLabel->hide();
    NomberLabel->setText(QString("").setNum(NomberForLabel));
    if(!LeoConst::CONST()->All_BOOL_PARAMS["ACCOUNT"]){
        RoundLabel->hide();
        NomberLabel->hide();
    }else{
        RoundLabel->show();
        NomberLabel->show();
    }
    main_Label->setText(QString(TrueWord.eng));
}
