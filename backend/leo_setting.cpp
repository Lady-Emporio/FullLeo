#include "leo_setting.h"
#include "leo_const.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QString>
#include <QMessageBox>
Settings::Settings(QWidget *parent) : QWidget(parent)
{
    this->setObjectName("settings");
    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    QHBoxLayout *hl1=new QHBoxLayout();
    QHBoxLayout *hl2=new QHBoxLayout();
    hl1->addWidget(groupFont());
    hl1->addWidget(groupDB());
    hl2->addWidget(groupStyle());
    hl2->addWidget(groupEngRus());
    mainLayout->addLayout(hl1);
    mainLayout->addLayout(hl2);
    this->setLayout(mainLayout);
}

Settings * Settings::getSettings(){
    static Settings *s=new Settings;
    return s;
}
void Settings::closeEvent(QCloseEvent *eClose){
    eClose->ignore();
    this->hide();

}

Settings::~Settings(){
    //qDebug()<<"Delete";
}

QGroupBox * Settings::groupDB(){
    QGroupBox *group_db = new QGroupBox("data base",this);
    setFontToWidget(group_db);
    group_db->setStyleSheet("QGroupBox{border: 4px solid black;}");
    QLabel *FromDB=new QLabel("getFromDB[0-9]{4}");
    setFontToWidget(FromDB);
    QLineEdit *IntFromDB=new QLineEdit(group_db);
    setFontToWidget(IntFromDB);
    IntFromDB->setText(QString("").setNum(LeoConst::CONST()->getFromDB));
    IntFromDB->setValidator(new QRegExpValidator(QRegExp("[0-9]{4}"), group_db));
    QLabel *pathTodb=new QLabel("path to db("+LeoConst::CONST()->path_bd+") ");
    setFontToWidget(pathTodb);
    QLineEdit *EditpathTodb=new QLineEdit(group_db);
    setFontToWidget(EditpathTodb);
    EditpathTodb->setText(LeoConst::CONST()->path_bd);
    QVBoxLayout *mainLayout=new QVBoxLayout();
    QHBoxLayout *hl1=new QHBoxLayout();
    QHBoxLayout *hl2=new QHBoxLayout();
    QHBoxLayout *hl3=new QHBoxLayout();
    QListWidget *listWord=new QListWidget(this);
    setFontToWidget(listWord);
    for(int i=0;i!=LeoConst::CONST()->ListWithWordConst.size();++i){
        QListWidgetItem *next=new QListWidgetItem(listWord);
        QString Qeng=LeoConst::CONST()->ListWithWordConst[i].eng;
        QString Qru=LeoConst::CONST()->ListWithWordConst[i].ru;
        next->setText(Qeng+" "+Qru);
        listWord->addItem(next);
    }
    updateDB=new QPushButton(this);
    setFontToWidget(updateDB);
    updateDB->setText("Обновим db");
    setFontToWidget(updateDB);

    group_db->setLayout(mainLayout);
    hl1->addWidget(FromDB);
    hl1->addWidget(IntFromDB);
    hl2->addWidget(pathTodb);
    hl2->addWidget(EditpathTodb);
    hl3->addWidget(listWord);
    hl3->addWidget(updateDB);
    mainLayout->addLayout(hl1);
    mainLayout->addLayout(hl2);
    mainLayout->addLayout(hl3);
    if (group_db->font().pointSize()>10){
        mainLayout->setContentsMargins(10,group_db->font().pointSize(),10,10);
    }
    connect(IntFromDB, SIGNAL(textChanged(const QString &)), this, SLOT(connectIntFromDB(const QString &)));
    connect(EditpathTodb, SIGNAL(textChanged(const QString &)), this, SLOT(connectPathToDB(const QString &)));
    return group_db;
}

void Settings::connectIntFromDB(const QString & x){
     LeoConst::CONST()->getFromDB=x.toInt();
 }
void Settings::connectPathToDB(const QString & x){
    LeoConst::CONST()->path_bd=x;
}

QGroupBox * Settings::groupFont(){
    QGroupBox *groupFont = new QGroupBox("font",this);
    groupFont->setStyleSheet("QGroupBox{border: 4px solid rgb(0, 255, 0);}");
    setFontToWidget(groupFont);
    QLabel *fontFamyle=new QLabel("Font family");
    setFontToWidget(fontFamyle);
    QLineEdit *EditFamily=new QLineEdit(groupFont);
    setFontToWidget(EditFamily);
    EditFamily->setText(LeoConst::CONST()->fontFamyle);
    QLabel *fontSize=new QLabel("Font size");
    setFontToWidget(fontSize);
    QLineEdit *EditSizeFont=new QLineEdit(groupFont);
    setFontToWidget(EditSizeFont);
    EditSizeFont->setText(QString("").setNum(LeoConst::CONST()->FONT_SIZE));
    EditSizeFont->setValidator(new QRegExpValidator(QRegExp("[1-9][0-9]"), groupFont));
    QVBoxLayout *mainLayout=new QVBoxLayout(groupFont);
    QHBoxLayout *hl1=new QHBoxLayout();
    QHBoxLayout *hl2=new QHBoxLayout();
    hl1->addWidget(fontFamyle);
    hl1->addWidget(EditFamily);
    hl2->addWidget(fontSize);
    hl2->addWidget(EditSizeFont);
    mainLayout->addLayout(hl1);
    mainLayout->addLayout(hl2);
    groupFont->setLayout(mainLayout);
    QListWidget *listWord=new QListWidget(this);
    setFontToWidget(listWord);
    listWord->addItem(new QListWidgetItem("Arial",listWord));
    listWord->addItem(new QListWidgetItem("Courier New",listWord));
    listWord->addItem(new QListWidgetItem("Georgia",listWord));
    listWord->addItem(new QListWidgetItem("Times New Roman",listWord));
    listWord->addItem(new QListWidgetItem("MS Sans Serif",listWord));
    listWord->addItem(new QListWidgetItem("Tahoma",listWord));
    mainLayout->addWidget(listWord);
    if (groupFont->font().pointSize()>10){
        mainLayout->setContentsMargins(10,groupFont->font().pointSize(),10,10);
    }
    connect(EditFamily, SIGNAL(textChanged(const QString &)), this, SLOT(connectFontFamily(const QString &)));
    connect(EditSizeFont, SIGNAL(textChanged(const QString &)), this, SLOT(connectFontSize(const QString &)));
    return groupFont;
}

void Settings::connectFontFamily(const QString &x){
    LeoConst::CONST()->fontFamyle=x;
}

void Settings::connectFontSize(const QString &x){
    LeoConst::CONST()->FONT_SIZE=x.toInt();
}

QGroupBox * Settings::groupStyle(){
    QGroupBox *groupStyle = new QGroupBox("crossword",this);
    groupStyle->setStyleSheet("QGroupBox{border: 4px solid rgb(255, 0, 0);}");
    setFontToWidget(groupStyle);
    QVBoxLayout *mainLayout=new QVBoxLayout(groupStyle);
    int red,green,blue;
    QStringList *StyleList=new QStringList;
    QString Error;
    QComboBox *comboStyle=new QComboBox(groupStyle);
    setFontToWidget(comboStyle);
    if(getStyle(StyleList,"default","DEFAULTQB",&red,&green,&blue,Error)!=0){
        comboStyle->addItem("Error style.json");
    }
    else{
        for(int i=0;i!=StyleList->size();++i){
            comboStyle->addItem(StyleList->at(i));
        }
    }
    mainLayout->addWidget(comboStyle);
    if (groupStyle->font().pointSize()>10){
        mainLayout->setContentsMargins(10,groupStyle->font().pointSize(),10,10);
    }
    QLabel *row=new QLabel("row[1-9][02468]{2}");
    setFontToWidget(row);
    QLineEdit *EditRowCount=new QLineEdit(groupStyle);
    setFontToWidget(EditRowCount);
    EditRowCount->setText(QString("").setNum(LeoConst::CONST()->TABLE_ROW));
    EditRowCount->setValidator(new QRegExpValidator(QRegExp("[1-9][02468]{2}"), groupStyle));
    QLabel *col=new QLabel("col[1-9][02468]{2}");
    setFontToWidget(col);
    QLineEdit *EditCOL=new QLineEdit(groupStyle);
    setFontToWidget(EditCOL);
    EditCOL->setText(QString("").setNum(LeoConst::CONST()->TABLE_COL));
    EditCOL->setValidator(new QRegExpValidator(QRegExp("[1-9][02468]{2}"), groupStyle));
    QComboBox *comboAlg=new QComboBox(groupStyle);
    comboAlg->addItem("fast");
    comboAlg->addItem("full");
    QCheckBox * buttomJump=new QCheckBox("jump?",this);
    QCheckBox * buttomAutoCompletion=new QCheckBox("auto completion?",this);
    QCheckBox * ButtomGrin=new QCheckBox("delete grid?",this);
    QHBoxLayout *hl1=new QHBoxLayout();
    QHBoxLayout *hl2=new QHBoxLayout();
    hl1->addWidget(row);
    hl1->addWidget(EditRowCount);
    hl2->addWidget(col);
    hl2->addWidget(EditCOL);
    mainLayout->addLayout(hl1);
    mainLayout->addLayout(hl2);
    mainLayout->addWidget(comboAlg);
    mainLayout->addWidget(buttomJump);
    mainLayout->addWidget(buttomAutoCompletion);
    mainLayout->addWidget(ButtomGrin);
    groupStyle->setLayout(mainLayout);
    connect(EditRowCount, SIGNAL(textChanged(const QString &)), this, SLOT(connectRowTable(const QString &)));
    connect(EditCOL, SIGNAL(textChanged(const QString &)), this, SLOT(connectColTable(const QString &)));
    connect(comboAlg, SIGNAL(currentTextChanged(const QString &)), this, SLOT(connectALG_trigger(const QString &)));
    connect(comboStyle, SIGNAL(currentTextChanged(const QString &)), this, SLOT(connectStyleJson_trigger(const QString &)));
    connect(buttomAutoCompletion, SIGNAL(clicked()), this, SLOT(connectAUTOCOMPLETION_trigger()));
    connect(buttomJump, SIGNAL(clicked()), this, SLOT(connectJUMP_trigger()));
    connect(ButtomGrin, SIGNAL(clicked()), this, SLOT(connectGRIDTABLE_trigger()));
    return groupStyle;
}

void Settings::connectRowTable(const QString &x){
    LeoConst::CONST()->TABLE_ROW=x.toInt();

}
void Settings::connectColTable(const QString &x){
    LeoConst::CONST()->TABLE_COL=x.toInt();
}

void Settings::connectALG_trigger(const QString &x){
//    QString select=comboAlg->itemText(x);
    if(x=="fast"){
        LeoConst::CONST()->ALGORITMH=fast;
    }
    else if(x=="full"){
        LeoConst::CONST()->ALGORITMH=full;
    }
}

void Settings::connectStyleJson_trigger(const QString &x){
    QString Error;
    LeoConst::CONST()->setStyle(x,Error);
    if(Error.size()!=0){
        QMessageBox msgBox;
        msgBox.setText(Error);
        msgBox.exec();
    }
}

void Settings::connectAUTOCOMPLETION_trigger(){
    LeoConst::CONST()->AUTOCOMPLETION=!LeoConst::CONST()->AUTOCOMPLETION;
}
void Settings::connectJUMP_trigger(){
    LeoConst::CONST()->JUMP=!LeoConst::CONST()->JUMP;
}
void Settings::connectGRIDTABLE_trigger(){
    LeoConst::CONST()->GRID=!LeoConst::CONST()->GRID;
}


QGroupBox * Settings::groupEngRus(){
    QGroupBox *group_eng_rus = new QGroupBox("Eng rus",this);
    group_eng_rus->setStyleSheet("QGroupBox{border: 4px solid rgb(255, 0, 0);}");
    setFontToWidget(group_eng_rus);
    QVBoxLayout *mainLayout=new QVBoxLayout(group_eng_rus);
    if (group_eng_rus->font().pointSize()>10){
        mainLayout->setContentsMargins(10,group_eng_rus->font().pointSize(),10,10);
    }
    group_eng_rus->setLayout(mainLayout);
    QCheckBox * ButtomAudio=new QCheckBox("audio?",this);
    mainLayout->addWidget(ButtomAudio);
    connect(ButtomAudio, SIGNAL(clicked()), this, SLOT(connectAudio_trigger()));
    return group_eng_rus;
}
void Settings::connectAudio_trigger(){
    LeoConst::CONST()->runAudio=!LeoConst::CONST()->runAudio;
}

//QGroupBox * Settings::groupEngRus(){
//    QGroupBox *group_eng_rus = new QGroupBox("Eng rus",this);
//    group_eng_rus->setStyleSheet("QGroupBox{border: 4px solid rgb(255, 0, 0);}");
//    setFontToWidget(group_eng_rus);
//    QVBoxLayout *mainLayout=new QVBoxLayout(group_eng_rus);

//    if (group_eng_rus->font().pointSize()>10){
//        mainLayout->setContentsMargins(10,group_eng_rus->font().pointSize(),10,10);
//    }
//    group_eng_rus->setLayout(mainLayout);
//    return group_eng_rus;
//}

