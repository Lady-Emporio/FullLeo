#include "settings.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QString>
#include "const.h"
#include <QPushButton>
#include <QRadioButton>

Settings::Settings(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout=new QVBoxLayout(this);
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

    countRow->setText(QString("").setNum(CONST->TABLE_ROW()));
    countColumn->setText(QString("").setNum(CONST->TABLE_COL()));

    comboAlg=new QComboBox(this);
    comboAlg->addItem("fast");
    comboAlg->addItem("full");
    QPushButton * buttomJump=new QPushButton("jump",this);
    buttomJump->setCheckable(true);
    QPushButton * buttomAutoCompletion=new QPushButton("auto completion",this);
    buttomAutoCompletion->setCheckable(true);
    setLayout(mainLayout);
    mainLayout->addLayout(regionRowAndColLayout);
    mainLayout->addWidget(comboAlg);
    mainLayout->addWidget(comboStyle);
    mainLayout->addWidget(buttomJump);
    mainLayout->addWidget(buttomAutoCompletion);
    comboStyle->addItem("defaults");
    comboStyle->addItem("low");



    connect(comboStyle, SIGNAL(currentIndexChanged(int)), this, SLOT(connectSelectNewStyle_trigger(int)));
    connect(comboAlg, SIGNAL(currentIndexChanged(int)), this, SLOT(connectALG_trigger(int)));
    connect(updateRowAndCol, SIGNAL(clicked()), this, SLOT(connectSetRowAndColCount()));
    connect(buttomJump, SIGNAL(clicked()), this, SLOT(connectJUMP_trigger()));
    connect(buttomAutoCompletion, SIGNAL(clicked()), this, SLOT(connectAUTOCOMPLETION_trigger()));
}

void Settings::connectSelectNewStyle_trigger(int x){
    QString select=comboStyle->itemText(x);
    if(select=="defaults"){
        CONST->setSize(defaults);
    }
    else if(select=="low"){
        CONST->setSize(low);
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








