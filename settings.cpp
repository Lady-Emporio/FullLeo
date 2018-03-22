#include "settings.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QString>
#include "const.h"

Settings::Settings(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    sizeRow=new QLabel;
    comboBoxsize=new QComboBox(this);
    comboBoxstyle=new QComboBox(this);
    setLayout(mainLayout);
    mainLayout->addWidget(sizeRow);
    mainLayout->addWidget(comboBoxsize);
    mainLayout->addWidget(comboBoxstyle);
    comboBoxsize->addItem("defaults");
    comboBoxsize->addItem("low");


    connect(comboBoxsize, SIGNAL(currentIndexChanged(int)), this, SLOT(connectSelectNewStyle_trigger(int)));
}

void Settings::connectSelectNewStyle_trigger(int x){
    QString select=comboBoxsize->itemText(x);
    if(select=="defaults"){
        CONST->setSize(defaults);
    }
    else if(select=="low"){
        CONST->setSize(low);
    }
    int row=CONST->TABLE_ROW();
    QString row_str;
    sizeRow->setText(row_str.setNum(row));
}
