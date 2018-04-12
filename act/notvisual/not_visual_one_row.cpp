#include "not_visual_one_row.h"
#include <QGridLayout>
#include <ctime>        // std::time
#include <QMediaPlaylist>
NotVisualOneRow::NotVisualOneRow(QWidget *parent) : QWidget(parent)
{
    player=new QMediaPlayer;
    QGridLayout * mainLayout=new QGridLayout(this);
    QPushButton *playButton=new QPushButton("play",this);
    TrueLabel=new QLabel(this);
    InputLabel=new QLabel(this);
    mainLayout->addWidget(TrueLabel,0,0);
    mainLayout->addWidget(InputLabel,1,0);
    mainLayout->addWidget(playButton,2,0);
    connect(playButton, SIGNAL(clicked()), this, SLOT(NextRound()));


    EverWordList=LeoConst::CONST()->ListWithWordConst;
    sort(EverWordList.begin(),EverWordList.end(),[](Word x1,Word x2) {return (x1.eng<x2.eng);}); //убираю дубли
    auto last=unique(EverWordList.begin(),EverWordList.end(),[](Word x1,Word x2) {return (x1.eng==x2.eng);});
    EverWordList.erase(last, EverWordList.end());
    std::srand ( unsigned ( std::time(0) ) );
    std::random_shuffle(EverWordList.begin(),EverWordList.end(),[](int i){return std::rand()%i;});
    ListWord=EverWordList;

}
void NotVisualOneRow::NextRound(){
    if (ListWord.size()<=0){
        if(LeoConst::CONST()->All_BOOL_PARAMS["EVER"]){
            std::random_shuffle(EverWordList.begin(),EverWordList.end(),[](int i){return std::rand()%i;});
            ListWord=EverWordList;
        }else{
            TrueLabel->setText(QString("End size: ")+QString("").setNum(ListWord.size()));
            return;
        }
    };
    TrueWord=ListWord.back();
    ListWord.pop_back();
    indexInput=0;
    TrueLabel->setText(TrueWord.ru);
    InputLabel->setText("");
    LeoConst::CONST()->player->setMedia(QUrl::fromLocalFile(QDir::toNativeSeparators("content\\"+QString("RU")+TrueWord.eng+".mp3")));
    LeoConst::CONST()->player->play();
}

void NotVisualOneRow::keyPressEvent(QKeyEvent * event){
if(TrueWord.eng.size()!=0 && TrueWord.ru.size()!=0){
QString text=event->text().toLower();
static bool go_next=false;
if(text.count()!=0){
    switch(event->key()){
    case Qt::Key_Enter:
    case Qt::Key_Return:
        if(go_next==true){
            go_next=false;
            NextRound();
            return;
        }
        break;
    case Qt::Key_1:{
        QString cout_text=InputLabel->text();
        QMediaPlaylist *playlist=new QMediaPlaylist(this);
        for(size_t i=0;i!=cout_text.size();++i){
            QString path=LeoConst::CONST()->CONST()->All_QString_PARAMS["alphabet"]+QString("RU")+QString(cout_text[i]).toLower()+".mp3";
            playlist->addMedia(QUrl::fromLocalFile(QDir::toNativeSeparators(path)));


        }
        playlist->setCurrentIndex(1);
        player->setPlaylist(playlist);
        player->play();
        return;
        break;
    }
    case Qt::Key_2:{
        LeoConst::CONST()->player->setMedia(QUrl::fromLocalFile(QDir::toNativeSeparators("content\\"+QString("RU")+TrueWord.eng+".mp3")));
        LeoConst::CONST()->player->play();
        return;
        break;
    }
    }

    QString word=TrueWord.eng;
    if(text==QString(word[indexInput])){
        InputLabel->setText(InputLabel->text()+QString(word[indexInput]));
        ++indexInput;
    }else{
        QMediaPlaylist *playlist=new QMediaPlaylist(this);
        QString path=LeoConst::CONST()->CONST()->All_QString_PARAMS["alphabet"]+QString("RU")+QString(text).toLower()+".mp3";
        QString mp3=LeoConst::CONST()->All_QString_PARAMS["TrueSound"];
        playlist->addMedia(QUrl::fromLocalFile(QDir::toNativeSeparators(mp3)));
        playlist->addMedia(QUrl::fromLocalFile(QDir::toNativeSeparators(path)));
        playlist->setCurrentIndex(1);
        player->setPlaylist(playlist);
        player->play();
    }
    if(indexInput==word.size()){
        LeoConst::CONST()->player->setMedia(QUrl::fromLocalFile(QDir::toNativeSeparators("content\\"+TrueWord.eng+".mp3")));
        LeoConst::CONST()->player->play();
        go_next=true;
    }
}
}
}
