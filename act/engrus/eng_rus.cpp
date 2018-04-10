#include "eng_rus.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <ctime>
#include "QTime"
#include <algorithm>
Button::Button(QWidget  *parent): QPushButton (parent){
    //font and start text
    {
    QFont font;
    font.setFamily(QStringLiteral("Courier New"));
    font.setPointSize(10);
    this->setFont(font);
    this->setText("MyClassButtom");
    }
    this->setStyleSheet(LeoConst::CONST()->All_QString_PARAMS["DEFAULT_BUTTOM_COLOR"]);
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setSizePolicy(sizePolicy);
}



EngRus::EngRus(QWidget *parent,Leo::pos statusThis) : QWidget(parent) ,status(statusThis)
{
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    this->setObjectName("EngRus");
    QVBoxLayout *horizontal_mainLayout=new QVBoxLayout;
    QHBoxLayout *horizontal_ImageAndButtonLayout=new QHBoxLayout;
    QHBoxLayout *vertical_mainLayout=new QHBoxLayout;
    QVBoxLayout *vertical_ImageAndButtonLayout=new QVBoxLayout;
    main_Label=new QLabel("We are",this);
    setFontToWidget(main_Label);
    main_Label->setAlignment(Qt::AlignCenter);
    main_Label->setCursor(QCursor(Qt::CrossCursor));
    MaxButton=LeoConst::CONST()->All_INT_PARAMS["COUNT_BUTTOM"];
    for(int i=0;i!=MaxButton;++i){
        Button *newButton=new Button(this);
        newButton->setText(QString("We are: ").setNum(i));
        newButton->setObjectName(QString("WeAreButtonMy25/03/2018").setNum(i));
        setFontToWidget(newButton);
        listButton.push_back(newButton);
        QPushButton *newImage=new QPushButton;
        newImage->hide();
        listImage.push_back(newImage);


        connect(newButton, SIGNAL(clicked()), this, SLOT(connectSelectWord()));
        connect(newImage, SIGNAL(clicked()), this, SLOT(connectSelectImage()));
        if(status==Leo::horizontal){
            QVBoxLayout *newLayout=new QVBoxLayout;
            newLayout->addWidget(newImage);
            newLayout->addWidget(newButton);
            horizontal_ImageAndButtonLayout->addLayout(newLayout);
        }else if(status==Leo::vertical){
            QHBoxLayout *newLayout=new QHBoxLayout;
            newLayout->addWidget(newImage);
            newLayout->addWidget(newButton);
            vertical_ImageAndButtonLayout->addLayout(newLayout);
        }
    }
    if(status==Leo::horizontal){
        horizontal_mainLayout->addWidget(main_Label);
        horizontal_mainLayout->addLayout(horizontal_ImageAndButtonLayout);
        this->setLayout(horizontal_mainLayout);
    }else if(status==Leo::vertical){
        vertical_mainLayout->addWidget(main_Label);
        vertical_mainLayout->addLayout(vertical_ImageAndButtonLayout);
        this->setLayout(vertical_mainLayout);
    }


    EverWordList=LeoConst::CONST()->ListWithWordConst;
    sort(EverWordList.begin(),EverWordList.end(),[](Word x1,Word x2) {return (x1.eng<x2.eng);}); //убираю дубли
    auto last=unique(EverWordList.begin(),EverWordList.end(),[](Word x1,Word x2) {return (x1.eng==x2.eng);});
    EverWordList.erase(last, EverWordList.end());
    ListWord=EverWordList;
    if (ListWord.size()<=MaxButton || ListWord.size()==0){
            main_Label->setText(QString("Small size: ")+QString("").setNum(ListWord.size()));
            return;
    };
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
    if (ListWord.size()<=MaxButton){
            main_Label->setText(QString("Small size: ")+QString("").setNum(ListWord.size()));
            return;
    };
    std::srand ( (int)time(0));
    random_shuffle ( ListWord.begin(), ListWord.end(),[](int i) {return std::rand()%i;});
}
void EngRus::connectSelectImage(){
    if(LeoConst::CONST()->All_BOOL_PARAMS["runAudio"]){
        LeoConst::CONST()->player->setMedia(QUrl::fromLocalFile(QDir::toNativeSeparators("content\\"+TrueWord.eng+".mp3")));
        LeoConst::CONST()->player->play();
    };
}

void EngRus::nextRound(){
    for(size_t i=0;i!=listButton.size();++i){
        listButton[i]->setStyleSheet(LeoConst::CONST()->All_QString_PARAMS["DEFAULT_BUTTOM_COLOR"]);
    }
    if (ListWord.size()<=0){
            if(LeoConst::CONST()->All_BOOL_PARAMS["EVER"]){
                ListWord=EverWordList;
            }
            else{
                main_Label->setText(QString("End size: ")+QString("").setNum(ListWord.size()));
                return;
            }
    };
    random_shuffle ( ListWord.begin(), ListWord.end(),[](int i) {return std::rand()%i;});
    std::vector<Word>UsingWord;
    TrueWord=ListWord.back();
    ListWord.pop_back();
    UsingWord.push_back(TrueWord);
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
                    if(LeoConst::CONST()->All_BOOL_PARAMS["runImage"]){
                        QString fileName="./content/"+UsingWord[i].eng+".png";
                        if(listImage[i]->isHidden()){
                            listImage[i]->show();
                        }
                        QPixmap pix(fileName);
                        listImage[i]->setIcon(pix);
                        listImage[i]->setIconSize(QSize(150, 100));
                    }
                    else{
                        listImage[i]->hide();
                    }
               }
               else{
                    Word backWord=sizeWordinLastSizeEnd.back();
                    sizeWordinLastSizeEnd.pop_back();
                    listButton[i]->setText(backWord.ru);
                    if(LeoConst::CONST()->All_BOOL_PARAMS["runImage"]){
                        QString fileName="./content/"+backWord.eng+".png";
                        if(listImage[i]->isHidden()){
                            listImage[i]->show();
                        }
                        QPixmap pix(fileName);
                        listImage[i]->setIcon(pix);
                        listImage[i]->setIconSize(QSize(150, 100));
                    }
                    else{
                        listImage[i]->hide();
                    }
               }
        }
        sizeWordinLastSizeEnd=updateLastSizeEnd;
    }else{
        for(size_t i=0;i!=listButton.size();++i){
            listButton[i]->setText(UsingWord[i].ru);
            if(LeoConst::CONST()->All_BOOL_PARAMS["runImage"]){
                QString fileName="./content/"+UsingWord[i].eng+".png";
                if(listImage[i]->isHidden()){
                    listImage[i]->show();
                }
                QPixmap pix(fileName);
                listImage[i]->setIcon(pix);
                listImage[i]->setIconSize(QSize(150, 100));
            }
            else{
                listImage[i]->hide();
            }
        }
    }
    main_Label->setText(QString(TrueWord.eng));
}

void EngRus::connectSelectWord(){
    if(main_Label->text()=="We are"){
        nextRound();
        return;
    }
    QObject* obj = sender();
    Button *buttom=findChild<Button*>(obj->objectName());
    if(buttom->text()==QString(TrueWord.ru)){
        if(LeoConst::CONST()->All_BOOL_PARAMS["runAudio"]){
            LeoConst::CONST()->player->setMedia(QUrl::fromLocalFile(QDir::toNativeSeparators("content\\"+TrueWord.eng+".mp3")));
            LeoConst::CONST()->player->play();
        };
        static bool go_next=false;
         if (!go_next){
             buttom->setStyleSheet(LeoConst::CONST()->All_QString_PARAMS["TRUE_ANSWER_COLOR"]);
             go_next=true;
         }
         else{
             go_next=false;
             nextRound();
        }
    }else{
        buttom->setStyleSheet(LeoConst::CONST()->All_QString_PARAMS["FALSE_ANSWER_COLOR"]);
    }


}

EngRus::~EngRus(){}
