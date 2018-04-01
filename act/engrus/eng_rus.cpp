#include "eng_rus.h"
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

    this->setStyleSheet(LeoConst::CONST()->DEFAULT_BUTTOM_COLOR);
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setSizePolicy(sizePolicy);
}


EngRus::EngRus(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout=new QVBoxLayout;
    QVBoxLayout *ImageAndButtonLayout=new QVBoxLayout;
    QHBoxLayout *imageLayout=new QHBoxLayout;
    QHBoxLayout *buttonLayout=new QHBoxLayout;
    ImageAndButtonLayout->addLayout(imageLayout);
    ImageAndButtonLayout->addLayout(buttonLayout);
    main_Label=new QLabel("We are",this);
    setFontToWidget(main_Label);
    main_Label->setAlignment(Qt::AlignCenter);
    main_Label->setCursor(QCursor(Qt::CrossCursor));
    for(int i=0;i!=LeoConst::CONST()->COUNT_BUTTOM;++i){
        Button *newButton=new Button(this);
        newButton->setText(QString("We are: ").setNum(i));
        newButton->setObjectName(QString("WeAreButtonMy25/03/2018").setNum(i));
        setFontToWidget(newButton);
        listButton.push_back(newButton);
        QLabel *imageLabel = new QLabel;
        imageLabel->setBackgroundRole(QPalette::Base);
        listImage.push_back(imageLabel);
        imageLayout->addWidget(imageLabel);
        buttonLayout->addWidget(newButton);
        connect(newButton, SIGNAL(clicked()), this, SLOT(connectSelectWord()));
    }
    mainLayout->addWidget(main_Label);
    mainLayout->addLayout(ImageAndButtonLayout);
    this->setLayout(mainLayout);

    ListWord=LeoConst::CONST()->ListWithWordConst;
    if (ListWord.size()<=5){
            main_Label->setText(QString("Small size: ")+QString("").setNum(ListWord.size()));
            return;
    };
    sort(ListWord.begin(),ListWord.end(),[](Word x1,Word x2) {return (x1.eng<x2.eng);}); //убираю дубли
    auto last=unique(ListWord.begin(),ListWord.end(),[](Word x1,Word x2) {return (x1.eng==x2.eng);});
    ListWord.erase(last, ListWord.end());
    std::srand ( (int)time(0));
    random_shuffle ( ListWord.begin(), ListWord.end(),[](int i) {return std::rand()%i;});
}

void EngRus::nextRound(){
    for(size_t i=0;i!=listButton.size();++i){
        listButton[i]->setStyleSheet(LeoConst::CONST()->DEFAULT_BUTTOM_COLOR);
    }
    if (ListWord.size()<=5){
            main_Label->setText(QString("Small size: ")+QString("").setNum(ListWord.size()));
            return;
    };
    random_shuffle ( ListWord.begin(), ListWord.end(),[](int i) {return std::rand()%i;});
    std::vector<Word>UsingWord;
    TrueWord=ListWord.back();
    ListWord.pop_back();
    UsingWord.push_back(TrueWord);
    for(size_t i=1;i!=listButton.size();++i){
        UsingWord.push_back(ListWord[ListWord.size()-i]);
    };
    random_shuffle ( UsingWord.begin(), UsingWord.end(),[](int i) {return std::rand()%i;});
    for(size_t i=0;i!=listButton.size();++i){
        listButton[i]->setText(UsingWord[i].ru);
        if(LeoConst::CONST()->runImage){
            QString fileName="./content/"+UsingWord[i].eng+".png";
            QImage image(fileName);
            listImage[i]->setPixmap(QPixmap::fromImage(image));
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
        if(LeoConst::CONST()->runAudio){
            static QMediaPlayer *player = new QMediaPlayer;
            player->setMedia(QUrl::fromLocalFile(QDir::toNativeSeparators("content\\"+TrueWord.eng+".mp3")));
            player->play();
        };
        static bool go_next=false;
         if (!go_next){
             buttom->setStyleSheet(LeoConst::CONST()->TRUE_ANSWER_COLOR);
             go_next=true;
         }
         else{
             go_next=false;
             nextRound();
        }
    }else{
        buttom->setStyleSheet(LeoConst::CONST()->FALSE_ANSWER_COLOR);
    }


}

EngRus::~EngRus(){}
