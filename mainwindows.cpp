#include "mainwindows.h"
#include "settings.h"

#include <QDebug>

saveMdiSub::saveMdiSub(QWidget *parent) :QMdiSubWindow(parent){

}
void saveMdiSub::closeEvent(QCloseEvent *event){
        //work but i not know;
}




MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    mdiArea = new QMdiArea(this);  // инициализируем QMdiArea
    // Настраиваем скроллбары
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    // Устанавливаем Mdi Area в качестве центрального виджета
    setCentralWidget(mdiArea);

    highTopMenu=new QMenuBar;

    QMenu*  add   = new QMenu("Add");
    highTopMenu->addMenu(add);
    this->setMenuBar(highTopMenu);

    QAction* pCheckableAction = add->addAction("New crossword",this,SLOT(on_actionAddCrossword_triggered()));
    highTopMenu->addAction("Settings",this,SLOT(on_actionOpenSettingstriggered()));
}

void MainWindow::on_actionAddCrossword_triggered(){
    Crossword *cross = new Crossword(mdiArea);
    mdiArea->addSubWindow(cross);
    cross->show();
}

void MainWindow::on_actionOpenSettingstriggered(){
    static Settings *settings =Settings::getSettings();
    static bool firstCreate=true;
    if (firstCreate){
        saveMdiSub *subWindow1 = new saveMdiSub;
        subWindow1->setWidget(settings);
        mdiArea->addSubWindow(subWindow1);
        firstCreate=false;
        subWindow1->show();
    }
    else{
        QList<QMdiSubWindow *>	allSub=mdiArea->subWindowList();
        for(auto x:allSub){
            if(x->widget()==settings && x->isHidden()){
                    x->show();
            }
        };
    }
}
