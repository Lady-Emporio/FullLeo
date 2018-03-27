#include "mainwindows.h"
#include "settings.h"
#include "eng_rus.h"
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

    QMenu*  addMenu   = new QMenu("Add");
    highTopMenu->addMenu(addMenu);
    this->setMenuBar(highTopMenu);

    addMenu->addAction("New crossword",this,SLOT(on_actionAddCrossword_triggered()));
    addMenu->addAction("New EngRus4x1",this,SLOT(on_actionAddEngRus4x1_triggered()));
    highTopMenu->addAction("Settings",this,SLOT(on_actionOpenSettingstriggered()));

    QMenu*  windowMenu   = new QMenu("Window");
    highTopMenu->addMenu(windowMenu);
    windowMenu->addAction("Cascade sub windows",this,SLOT(on_actionCascadeSubWindows()));
    windowMenu->addAction("Tile sub windows",this,SLOT(on_actionTileSubWindows()));
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

void MainWindow::on_actionCascadeSubWindows(){
    mdiArea->cascadeSubWindows();
}

void MainWindow::on_actionTileSubWindows(){
    mdiArea->tileSubWindows();
}

void MainWindow::on_actionAddEngRus4x1_triggered(){
    EngRus *eng_rus_leo=new EngRus;
    QMdiSubWindow *subWindow1 = new QMdiSubWindow;
    subWindow1->setWidget(eng_rus_leo);
    subWindow1->setAttribute(Qt::WA_DeleteOnClose);
    mdiArea->addSubWindow(subWindow1);
    subWindow1->show();
}








