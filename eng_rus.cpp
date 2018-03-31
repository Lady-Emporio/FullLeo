#include "eng_rus.h"
#include "const.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <ctime>
#include <QMediaPlayer>
#include <QDir>
Button::Button(QWidget  *parent): QPushButton (parent){
    //font and start text
    {
    QFont font;
    font.setFamily(QStringLiteral("Courier New"));
    font.setPointSize(10);
    this->setFont(font);
    this->setText("MyClassButtom");
    }

    this->setStyleSheet(CONST->DEFAULT_BUTTOM_COLOR);
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setSizePolicy(sizePolicy);
}


EngRus::EngRus(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout=new QVBoxLayout;
    QHBoxLayout *buttonLayout=new QHBoxLayout;
    main_Label=new QLabel("We are",this);
    main_Label->setAlignment(Qt::AlignCenter);
    main_Label->setCursor(QCursor(Qt::CrossCursor));
    for(int i=0;i!=CONST->COUNT_BUTTOM();++i){
        Button *newButton=new Button(this);
        newButton->setText(QString("We are: ").setNum(i));
        newButton->setObjectName(QString("WeAreButtonMy25/03/2018").setNum(i));
        listButton.push_back(newButton);
        buttonLayout->addWidget(newButton);
        connect(newButton, SIGNAL(clicked()), this, SLOT(connectSelectWord()));
    }
    mainLayout->addWidget(main_Label);
    mainLayout->addLayout(buttonLayout);
    this->setLayout(mainLayout);


    ListWord=getWord();
    if (ListWord.size()<=5){
            main_Label->setText(QString("Small size: ").setNum(ListWord.size()));
            return;
    };
    sort(ListWord.begin(),ListWord.end(),[](Word x1,Word x2) {return (x1.eng<x2.eng);}); //убираю дубли
    auto last=unique(ListWord.begin(),ListWord.end(),[](Word x1,Word x2) {return (x1.eng==x2.eng);});
    ListWord.erase(last, ListWord.end());
    std::srand ( (int)time(0));
    random_shuffle ( ListWord.begin(), ListWord.end(),[](int i) {return std::rand()%i;});
}

void EngRus::nextRound(){
    for(int i=0;i!=listButton.size();++i){
        listButton[i]->setStyleSheet(CONST->DEFAULT_BUTTOM_COLOR);
    }
    if (ListWord.size()<=5){
            main_Label->setText(QString("Small size: ").setNum(ListWord.size()));
            return;
    };
    random_shuffle ( ListWord.begin(), ListWord.end(),[](int i) {return std::rand()%i;});
    TrueWord=ListWord.back();
    ListWord.pop_back();
    listButton[0]->setText(QString(TrueWord.ru.c_str()));
    for(int i=1;i!=listButton.size();++i){
        listButton[i]->setText(ListWord[ListWord.size()-i].ru.c_str());
    };
    random_shuffle ( listButton.begin(), listButton.end(),[](int i) {return std::rand()%i;});
    main_Label->setText(QString(TrueWord.eng.c_str()));

}

void EngRus::connectSelectWord(){
    if(main_Label->text()=="We are"){
        nextRound();
        return;
    }
    QObject* obj = sender();
    Button *buttom=findChild<Button*>(obj->objectName());
    if(buttom->text()==QString(TrueWord.ru.c_str())){
        if(CONST->runAudio){
            static QMediaPlayer *player = new QMediaPlayer;
            player->setMedia(QUrl::fromLocalFile(QDir::toNativeSeparators("content\\"+QString(TrueWord.eng.c_str())+".mp3")));
            player->play();
        };
        static bool go_next=false;
         if (!go_next){
             buttom->setStyleSheet(CONST->TRUE_ANSWER_COLOR);
             go_next=true;
         }
         else{
             go_next=false;
             nextRound();
        }
    }else{
        buttom->setStyleSheet(CONST->FALSE_ANSWER_COLOR);
    }


}

EngRus::~EngRus(){}

















