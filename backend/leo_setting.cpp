#include "leo_setting.h"
#include "leo_const.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QString>
#include <QMessageBox>
#include <QGridLayout>
Settings::Settings(QWidget *parent) : QWidget(parent)
{
    this->setObjectName("settings");
    QGridLayout *mainLayout=new QGridLayout(this);
    mainLayout->addWidget(groupFont(),0,0);
    mainLayout->addWidget(groupDB(),0,1);
    mainLayout->addWidget(groupStyle(),1,0);
    mainLayout->addWidget(groupEngRus(),1,1);
    mainLayout->addWidget(groupJson(),0,2,2,1);

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
    IntFromDB->setText(QString("").setNum(LeoConst::CONST()->All_INT_PARAMS["getFromDB"]));
    IntFromDB->setValidator(new QRegExpValidator(QRegExp("[0-9]{4}"), group_db));
    QLabel *pathTodb=new QLabel("path to db("+LeoConst::CONST()->All_QString_PARAMS["path_bd"]+") ");
    setFontToWidget(pathTodb);
    QLineEdit *EditpathTodb=new QLineEdit(group_db);
    setFontToWidget(EditpathTodb);
    EditpathTodb->setText(LeoConst::CONST()->All_QString_PARAMS["path_bd"]);
    QGridLayout *mainLayout=new QGridLayout();
    QListWidget *listWord=new QListWidget(this);
    setFontToWidget(listWord);
    for(size_t i=0;i!=LeoConst::CONST()->ListWithWordConst.size();++i){
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
    mainLayout->addWidget(FromDB,0,0);
    mainLayout->addWidget(IntFromDB,0,1);
    mainLayout->addWidget(pathTodb,1,0);
    mainLayout->addWidget(EditpathTodb,1,1);
    mainLayout->addWidget(listWord,2,0,1,2);
    mainLayout->addWidget(updateDB,3,0,1,2);

    if (group_db->font().pointSize()>10){
        mainLayout->setContentsMargins(10,group_db->font().pointSize(),10,10);
    }
    connect(IntFromDB, SIGNAL(textChanged(const QString &)), this, SLOT(connectIntFromDB(const QString &)));
    connect(EditpathTodb, SIGNAL(textChanged(const QString &)), this, SLOT(connectPathToDB(const QString &)));
    return group_db;
}

void Settings::connectIntFromDB(const QString & x){
     LeoConst::CONST()->All_INT_PARAMS["getFromDB"]=x.toInt();
 }
void Settings::connectPathToDB(const QString & x){
    LeoConst::CONST()->All_QString_PARAMS["path_bd"]=x;
}

QGroupBox * Settings::groupFont(){
    QGroupBox *groupFont = new QGroupBox("font",this);
    groupFont->setStyleSheet("QGroupBox{border: 4px solid rgb(0, 255, 0);}");
    setFontToWidget(groupFont);
    QLabel *fontFamyle=new QLabel("Font family");
    setFontToWidget(fontFamyle);
    QLineEdit *EditFamily=new QLineEdit(groupFont);
    setFontToWidget(EditFamily);
    EditFamily->setText(LeoConst::CONST()->All_QString_PARAMS["fontFamyle"]);
    QLabel *fontSize=new QLabel("Font size");
    setFontToWidget(fontSize);
    QLineEdit *EditSizeFont=new QLineEdit(groupFont);
    setFontToWidget(EditSizeFont);
    EditSizeFont->setText(QString("").setNum(LeoConst::CONST()->All_INT_PARAMS["FONT_SIZE"]));
    EditSizeFont->setValidator(new QRegExpValidator(QRegExp("[1-9][0-9]"), groupFont));
    QGridLayout *mainLayout=new QGridLayout(groupFont);
    mainLayout->addWidget(fontFamyle,0,0);
    mainLayout->addWidget(EditFamily,0,1);
    mainLayout->addWidget(fontSize,1,0);
    mainLayout->addWidget(EditSizeFont,1,1);
    groupFont->setLayout(mainLayout);
    QListWidget *listWord=new QListWidget(this);
    setFontToWidget(listWord);
    listWord->addItem(new QListWidgetItem("Arial",listWord));
    listWord->addItem(new QListWidgetItem("Courier New",listWord));
    listWord->addItem(new QListWidgetItem("Georgia",listWord));
    listWord->addItem(new QListWidgetItem("Times New Roman",listWord));
    listWord->addItem(new QListWidgetItem("MS Sans Serif",listWord));
    listWord->addItem(new QListWidgetItem("Tahoma",listWord));
    mainLayout->addWidget(listWord,2,0,1,2);
    if (groupFont->font().pointSize()>10){
        mainLayout->setContentsMargins(10,groupFont->font().pointSize(),10,10);
    }
    connect(EditFamily, SIGNAL(textChanged(const QString &)), this, SLOT(connectFontFamily(const QString &)));
    connect(EditSizeFont, SIGNAL(textChanged(const QString &)), this, SLOT(connectFontSize(const QString &)));
    return groupFont;
}

void Settings::connectFontFamily(const QString &x){
    LeoConst::CONST()->All_QString_PARAMS["fontFamyle"]=x;
}

void Settings::connectFontSize(const QString &x){
    LeoConst::CONST()->All_INT_PARAMS["FONT_SIZE"]=x.toInt();
}

QGroupBox * Settings::groupStyle(){
    QGroupBox *groupStyle = new QGroupBox("crossword",this);
    groupStyle->setStyleSheet("QGroupBox{border: 4px solid rgb(255, 0, 0);}");
    setFontToWidget(groupStyle);
    QVBoxLayout *mainLayout=new QVBoxLayout(groupStyle);
    QString Error;
    QComboBox *comboStyle=new QComboBox(groupStyle);
    setFontToWidget(comboStyle);
    for(int i=0;i!=LeoConst::CONST()->ListStyle.size();++i){
        comboStyle->addItem(LeoConst::CONST()->ListStyle.at(i));
    }
    mainLayout->addWidget(comboStyle);
    if (groupStyle->font().pointSize()>10){
        mainLayout->setContentsMargins(10,groupStyle->font().pointSize(),10,10);
    }
    QLabel *row=new QLabel("row[1-9][02468]{2}");
    setFontToWidget(row);
    QLineEdit *EditRowCount=new QLineEdit(groupStyle);
    setFontToWidget(EditRowCount);
    EditRowCount->setText(QString("").setNum(LeoConst::CONST()->All_INT_PARAMS["TABLE_ROW"]));
    EditRowCount->setValidator(new QRegExpValidator(QRegExp("[1-9][02468]{2}"), groupStyle));
    QLabel *col=new QLabel("col[1-9][02468]{2}");
    setFontToWidget(col);
    QLineEdit *EditCOL=new QLineEdit(groupStyle);
    setFontToWidget(EditCOL);
    EditCOL->setText(QString("").setNum(LeoConst::CONST()->All_INT_PARAMS["TABLE_COL"]));
    EditCOL->setValidator(new QRegExpValidator(QRegExp("[1-9][02468]{2}"), groupStyle));
    QComboBox *comboAlg=new QComboBox(groupStyle);
    comboAlg->addItem("fast");
    comboAlg->addItem("full");
    QCheckBox * buttomJump=new QCheckBox("jump?",this);
    if(LeoConst::CONST()->All_BOOL_PARAMS["JUMP"]){
        buttomJump->setCheckState(Qt::Checked);
    }
    setFontToWidget(buttomJump);
    QCheckBox * buttomAutoCompletion=new QCheckBox("auto completion?",this);
    if(LeoConst::CONST()->All_BOOL_PARAMS["AUTOCOMPLETION"]){
        buttomAutoCompletion->setCheckState(Qt::Checked);
    }
    setFontToWidget(buttomAutoCompletion);
    QCheckBox * ButtomGrin=new QCheckBox("delete grid?",this);
    if(LeoConst::CONST()->All_BOOL_PARAMS["GRID"]){
        ButtomGrin->setCheckState(Qt::Checked);
    }
    setFontToWidget(ButtomGrin);
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
    connect(comboAlg, SIGNAL(activated(const QString &)), this, SLOT(connectALG_trigger(const QString &)));
    connect(comboStyle, SIGNAL(activated(const QString &)), this, SLOT(connectStyleJson_trigger(const QString &)));
    connect(buttomAutoCompletion, SIGNAL(clicked()), this, SLOT(connectAUTOCOMPLETION_trigger()));
    connect(buttomJump, SIGNAL(clicked()), this, SLOT(connectJUMP_trigger()));
    connect(ButtomGrin, SIGNAL(clicked()), this, SLOT(connectGRIDTABLE_trigger()));
    return groupStyle;
}

void Settings::connectRowTable(const QString &x){
    LeoConst::CONST()->All_INT_PARAMS["TABLE_ROW"]=x.toInt();

}
void Settings::connectColTable(const QString &x){
    LeoConst::CONST()->All_INT_PARAMS["TABLE_COL"]=x.toInt();
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
    LeoConst::CONST()->setStyle(x);
}

void Settings::connectAUTOCOMPLETION_trigger(){
    LeoConst::CONST()->All_BOOL_PARAMS["AUTOCOMPLETION"]=!LeoConst::CONST()->All_BOOL_PARAMS["AUTOCOMPLETION"];
}
void Settings::connectJUMP_trigger(){
    LeoConst::CONST()->All_BOOL_PARAMS["JUMP"]=!LeoConst::CONST()->All_BOOL_PARAMS["JUMP"];
}
void Settings::connectGRIDTABLE_trigger(){
    LeoConst::CONST()->All_BOOL_PARAMS["GRID"]=!LeoConst::CONST()->All_BOOL_PARAMS["GRID"];
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
    setFontToWidget(ButtomAudio);
    if(LeoConst::CONST()->All_BOOL_PARAMS["runAudio"]){
        ButtomAudio->setCheckState(Qt::Checked);
    }
    QCheckBox * ButtonImage=new QCheckBox("image?",this);
    setFontToWidget(ButtonImage);
    if(LeoConst::CONST()->All_BOOL_PARAMS["runImage"]){
        ButtonImage->setCheckState(Qt::Checked);
    }
    mainLayout->addWidget(ButtomAudio);
    mainLayout->addWidget(ButtonImage);
    connect(ButtomAudio, SIGNAL(clicked()), this, SLOT(connectAudio_trigger()));
    connect(ButtonImage, SIGNAL(clicked()), this, SLOT(connectImage_trigger()));
    return group_eng_rus;
}
void Settings::connectAudio_trigger(){
    LeoConst::CONST()->All_BOOL_PARAMS["runAudio"]=!LeoConst::CONST()->All_BOOL_PARAMS["runAudio"];
}
void Settings::connectImage_trigger(){
    LeoConst::CONST()->All_BOOL_PARAMS["runImage"]=!LeoConst::CONST()->All_BOOL_PARAMS["runImage"];
}

QGroupBox * Settings::groupJson(){
    QGroupBox *group_Json = new QGroupBox("Json",this);
    group_Json->setStyleSheet("QGroupBox{border: 4px solid rgb(170, 0, 170);}");
    setFontToWidget(group_Json);
    QGridLayout *mainLayout=new QGridLayout(group_Json);

    QPushButton *save_button=new QPushButton("Save",this);
    QListWidget *ConstValue=new QListWidget(this);
    for(auto iter=LeoConst::CONST()->All_BOOL_PARAMS.begin();iter!=LeoConst::CONST()->All_BOOL_PARAMS.end();++iter){
        QString status;
        if (iter.value()==false){
            status="Выкл";
        }else{status="true";}
        ConstValue->addItem(iter.key()+" | "+status);
    }
    for(auto iter=LeoConst::CONST()->All_QString_PARAMS.begin();iter!=LeoConst::CONST()->All_QString_PARAMS.end();++iter){
        ConstValue->addItem(iter.key()+" | "+iter.value());
    }
    for(auto iter=LeoConst::CONST()->All_INT_PARAMS.begin();iter!=LeoConst::CONST()->All_INT_PARAMS.end();++iter){
        ConstValue->addItem(iter.key()+" | "+QString("").setNum(iter.value()));
    }
    if (group_Json->font().pointSize()>10){
        mainLayout->setContentsMargins(10,group_Json->font().pointSize(),10,10);
    }
    group_Json->setLayout(mainLayout);
    mainLayout->addWidget(ConstValue,0,0,1,1);
    mainLayout->addWidget(save_button,1,0,1,1);
    connect(save_button, SIGNAL(clicked()), this, SLOT(connectNeedSaveJson()));
    return group_Json;
}

void Settings::connectNeedSaveJson(){
    QMessageBox msgBox;
    QFile saveFile("style.json");
    if (!saveFile.open(QIODevice::WriteOnly)) {
        msgBox.setText("Couldn't open save file.");
        msgBox.exec();
        return;
    }


    QJsonObject Setting_Json;
    for(QMap<QString,bool>::iterator x = LeoConst::CONST()->All_BOOL_PARAMS.begin();x != LeoConst::CONST()->All_BOOL_PARAMS.end(); ++x){
        Setting_Json[x.key()]=x.value();
    }

    QJsonObject allToSave;
    for(QMap<QString,QMap<QString,QBrush>>::iterator x = LeoConst::CONST()->AllStyleMap.begin();x != LeoConst::CONST()->AllStyleMap.end(); ++x){
        QJsonObject MainNameStyleExampleAS1CorMINAMAL;
        for(QMap<QString,QBrush>::iterator nextBrush= x.value().begin();nextBrush!=x.value().end();++nextBrush){
            QJsonObject subStyleExampleTRUEWORDBRUSHorGRIDBRUSH;
            QColor next=nextBrush.value().color();
            subStyleExampleTRUEWORDBRUSHorGRIDBRUSH.insert("red",next.red());
            subStyleExampleTRUEWORDBRUSHorGRIDBRUSH.insert("green",next.green());
            subStyleExampleTRUEWORDBRUSHorGRIDBRUSH.insert("blue",next.blue());
            MainNameStyleExampleAS1CorMINAMAL.insert(nextBrush.key(),subStyleExampleTRUEWORDBRUSHorGRIDBRUSH);
        }
        allToSave.insert(x.key(),MainNameStyleExampleAS1CorMINAMAL);
    }
    Setting_Json["crossword"]=allToSave;

    for(QMap<QString,int>::iterator x = LeoConst::CONST()->All_INT_PARAMS.begin();x != LeoConst::CONST()->All_INT_PARAMS.end(); ++x){
        Setting_Json[x.key()]=x.value();
    }
    for(QMap<QString,QString>::iterator x = LeoConst::CONST()->All_QString_PARAMS.begin();x != LeoConst::CONST()->All_QString_PARAMS.end(); ++x){
        Setting_Json[x.key()]=x.value();
    }
    QJsonDocument saveDoc(Setting_Json);
    saveFile.write(saveDoc.toJson());
}


//QGroupBox * Settings::groupEngRus(){
//    QGroupBox *group_eng_rus = new QGroupBox("Eng rus",this);
//    group_eng_rus->setStyleSheet("QGroupBox{border: 4px solid rgb(255, 0, 0);}");
//    setFontToWidget(group_eng_rus);
//    QGridLayout *mainLayout=new QGridLayout(group_eng_rus);

//    if (group_eng_rus->font().pointSize()>10){
//        mainLayout->setContentsMargins(10,group_eng_rus->font().pointSize(),10,10);
//    }
//    group_eng_rus->setLayout(mainLayout);
//    return group_eng_rus;
//}

