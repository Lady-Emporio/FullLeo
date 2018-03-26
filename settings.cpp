#include "settings.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QString>
#include "const.h"
#include <QPushButton>
#include <QRadioButton>
#include <QGroupBox>
#include <QCheckBox>
#include <QGridLayout>
Settings::Settings(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    QGroupBox *groupCrossword = new QGroupBox(tr("Crossword"),this);
    QGroupBox *groupStyle = new QGroupBox(tr("Style"),this);
    groupCrossword->setStyleSheet("QGroupBox{border: 4px solid green;}");
    groupStyle->setStyleSheet("QGroupBox{border: 4px solid blue;}");
    QVBoxLayout *mainCrosswordLayout=new QVBoxLayout(this);
    comboStyle=new QComboBox(this);

    QLabel *row=new QLabel("input count row[1-9][02468]{2}");
    QLabel *col=new QLabel("input count col[1-9][02468]{2}");
    nowRow=new QLabel(QString("row: ").setNum(CONST->TABLE_ROW()));
    nowCol=new QLabel(QString("col: ").setNum(CONST->TABLE_COL()));
    countRow=new QLineEdit;
    countColumn=new QLineEdit;
    countRow->setValidator(new QRegExpValidator(QRegExp("[1-9][02468]{2}"), this));
    countColumn->setValidator(new QRegExpValidator(QRegExp("[1-9][02468]{2}"), this));
    QHBoxLayout *rowLayount=new QHBoxLayout;
    QHBoxLayout *colLayount=new QHBoxLayout;
    QVBoxLayout *regionRowAndColLayout=new QVBoxLayout;
    rowLayount->addWidget(row);
    rowLayount->addWidget(countRow);
    rowLayount->addWidget(nowRow);
    colLayount->addWidget(col);
    colLayount->addWidget(countColumn);
    colLayount->addWidget(nowCol);
    QPushButton * updateRowAndCol=new QPushButton("Accept the change");
    updateRowAndCol->setToolTip("commit row and col\nUpdate table");
    regionRowAndColLayout->addLayout(rowLayount);
    regionRowAndColLayout->addLayout(colLayount);
    regionRowAndColLayout->addWidget(updateRowAndCol);
    ConstStyleSelect=new QComboBox(this);

    ConstStyleSelect->addItem("DEFAULTQB");
    ConstStyleSelect->addItem("NOTUSEQB");
    ConstStyleSelect->addItem("TRUEQB");
    ConstStyleSelect->addItem("FALSEQB");
    ConstStyleSelect->addItem("GRIDQB");
    ConstStyleSelect->addItem("ACTIVEINTABLEQB");
    ConstStyleSelect->addItem("ACTIVELISTQB");


    countRow->setText(QString("").setNum(CONST->TABLE_ROW()));
    countColumn->setText(QString("").setNum(CONST->TABLE_COL()));

    comboAlg=new QComboBox(this);
    comboAlg->addItem("fast");
    comboAlg->addItem("full");
    QCheckBox * buttomJump=new QCheckBox("jump?",this);
    QCheckBox * buttomAutoCompletion=new QCheckBox("auto completion?",this);
    QCheckBox * ButtomGrin=new QCheckBox("delete grid?",this);
    mainCrosswordLayout->addLayout(regionRowAndColLayout);
    mainCrosswordLayout->addWidget(comboAlg);
    mainCrosswordLayout->addWidget(buttomJump);
    mainCrosswordLayout->addWidget(buttomAutoCompletion);
    mainCrosswordLayout->addWidget(ButtomGrin);


    QGridLayout  *styleLayout=new QGridLayout(groupStyle);
    groupStyle->setLayout(styleLayout);
    styleLayout->addWidget(ConstStyleSelect,1,0,1,2);
    styleLayout->addWidget(comboStyle,0,0,1,2);
    comboStyle->addItem("defaults");
    comboStyle->addItem("low");
    comboStyle->addItem("as1C");
    comboStyle->addItem("dark");
    QLabel *redLabel=new QLabel("red");
    redEdit=new QLineEdit(this);
    redEdit->setValidator( new QIntValidator(0, 255, this) );
    styleLayout->addWidget(redLabel,2,0);
    styleLayout->addWidget(redEdit,2,1);
    QLabel *greenLabel=new QLabel("green");
    greenEdit=new QLineEdit(this);
    greenEdit->setValidator( new QIntValidator(0, 255, this) );
    styleLayout->addWidget(greenLabel,3,0);
    styleLayout->addWidget(greenEdit,3,1);
    QLabel *blueLabel=new QLabel("blue");
    blueEdit=new QLineEdit(this);
    blueEdit->setValidator( new QIntValidator(0, 255, this) );
    styleLayout->addWidget(blueLabel,4,0);
    styleLayout->addWidget(blueEdit,4,1);
    QPushButton * updateStyle=new QPushButton("Accept the change");
    updateStyle->setToolTip("commit style\nUpdate table");
    styleLayout->addWidget(updateStyle,5,0,1,2);

    QGroupBox *groupEngRus = new QGroupBox(tr("EngRus"),this);
    groupEngRus->setStyleSheet("QGroupBox{border: 4px solid black;}");
    QCheckBox * ButtomAudioPlay=new QCheckBox("AudioPlay",this);
    QVBoxLayout *regionEngRus=new QVBoxLayout;
    regionEngRus->addWidget(ButtomAudioPlay);
    groupEngRus->setLayout(regionEngRus);

    connect(comboStyle, SIGNAL(currentIndexChanged(int)), this, SLOT(connectSelectNewStyle_trigger(int)));
    connect(comboAlg, SIGNAL(currentIndexChanged(int)), this, SLOT(connectALG_trigger(int)));
    connect(updateRowAndCol, SIGNAL(clicked()), this, SLOT(connectSetRowAndColCount()));
    connect(buttomJump, SIGNAL(clicked()), this, SLOT(connectJUMP_trigger()));
    connect(buttomAutoCompletion, SIGNAL(clicked()), this, SLOT(connectAUTOCOMPLETION_trigger()));
    connect(ButtomGrin, SIGNAL(clicked()), this, SLOT(connectGRIDTABLE_trigger()));
    connect(updateStyle, SIGNAL(clicked()), this, SLOT(connectStyle_trigger()));
    connect(ButtomAudioPlay, SIGNAL(clicked()), this, SLOT(connectAudioPlay()));

    groupCrossword->setLayout(mainCrosswordLayout);
    mainLayout->addWidget(groupCrossword);
    mainLayout->addWidget(groupStyle);
    mainLayout->addWidget(groupEngRus);
    this->setLayout(mainLayout);
}
void Settings::connectAudioPlay(){

}

void Settings::connectStyle_trigger(){
    QString select=ConstStyleSelect->currentText();
    int red=redEdit->text().toInt();
    int green=greenEdit->text().toInt();
    int blue=blueEdit->text().toInt();
    if(select=="DEFAULTQB"){
        CONST->DEFAULTQB=QBrush(QColor(red, green, blue));
    }else if(select=="NOTUSEQB"){
        CONST->NOTUSEQB=QBrush(QColor(red, green, blue));
    }else if(select=="TRUEQB"){
        CONST->TRUEQB=QBrush(QColor(red, green, blue));
    }else if(select=="FALSEQB"){
        CONST->FALSEQB=QBrush(QColor(red, green, blue));
    }else if(select=="GRIDQB"){
        CONST->GRIDQB=QBrush(QColor(red, green, blue));
    }else if(select=="ACTIVEINTABLEQB"){
        CONST->ACTIVEINTABLEQB=QBrush(QColor(red, green, blue));
    }else if(select=="ACTIVELISTQB"){
        CONST->ACTIVELISTQB=QBrush(QColor(red, green, blue));
    }
}

void Settings::connectSelectNewStyle_trigger(int x){
    QString select=comboStyle->itemText(x);
    if(select=="defaults"){
        CONST->setStyle(defaults);
    }
    else if(select=="low"){
        CONST->setStyle(low);
    }
    else if(select=="as1C"){
        CONST->setStyle(as1C);
    }
    else if(select=="dark"){
        CONST->setStyle(dark);
    }
}

void Settings::connectGRIDTABLE_trigger(){
    if(CONST->GRID()){
        CONST->setGRID(false);
    }else{
        CONST->setGRID(true);
    }
}

void Settings::connectALG_trigger(int x){
    QString select=comboAlg->itemText(x);
    if(select=="fast"){
        CONST->setALGORITMH(fast);
    }
    else if(select=="full"){
        CONST->setALGORITMH(full);
    }
}

void Settings::closeEvent(QCloseEvent *eClose){
    eClose->ignore();
    this->hide();

}

Settings * Settings::getSettings(){
    static Settings *s=new Settings;
    return s;
}

void Settings::connectSetRowAndColCount(){
    int row=countRow->text().toInt();
    int col=countColumn->text().toInt();
    if (row!=CONST->TABLE_ROW()){
        CONST->setTABLE_ROW(row);
        nowRow->setText(QString("row: ").setNum(CONST->TABLE_ROW()));
    }
    if (col!=CONST->TABLE_COL()){
        CONST->setTABLE_COL(col);
        nowCol->setText(QString("col: ").setNum(CONST->TABLE_COL()));
    }
}

void Settings::connectJUMP_trigger(){
    if(CONST->JUMP()){
        CONST->setJUMP(false);
    }else{
        CONST->setJUMP(true);
    }
}

void Settings::connectAUTOCOMPLETION_trigger(){
    if(CONST->AUTOCOMPLETION()){
        CONST->setAUTOCOMPLETION(false);
    }else{
        CONST->setAUTOCOMPLETION(true);
    }
}








