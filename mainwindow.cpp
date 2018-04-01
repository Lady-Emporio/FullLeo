#include "mainwindow.h"
#include "backend/leo_setting.h"
#include "act/crossword/crossword.h"
#include "act/engrus/eng_rus.h"

saveMdiSub::saveMdiSub(QWidget *parent) :QMdiSubWindow(parent){}
void saveMdiSub::closeEvent(QCloseEvent *event){ /*work but i not know;*/}
saveMdiSub::~saveMdiSub(){/*qDebug()<<"we are del";*/}
void saveMdiSub::connectUpdateTable(){
     LeoConst::CONST()->GetFromBD();
     emit needUpdateThisIsWindow();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mdiArea = new QMdiArea(this);
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);

    highTopMenu=new QMenuBar;
    QMenu*  addMenu   = new QMenu("Add");
    highTopMenu->addMenu(addMenu);
    this->setMenuBar(highTopMenu);
    highTopMenu->addAction("Settings",this,SLOT(on_actionOpenSettingstriggered()));

    QMenu*  windowMenu   = new QMenu("Window");
    highTopMenu->addMenu(windowMenu);
    addMenu->addAction("New crossword",this,SLOT(on_actionAddCrossword_triggered()));
    addMenu->addAction("New EngRus",this,SLOT(on_actionAddEngRus4x1_triggered()));
    windowMenu->addAction("Cascade sub windows",this,SLOT(on_actionCascadeSubWindows()));
    windowMenu->addAction("Tile sub windows",this,SLOT(on_actionTileSubWindows()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::on_actionOpenSettingstriggered(){
//    static Settings *settings =Settings::getSettings();
//    static bool firstCreate=true;
//    if (firstCreate){
//        saveMdiSub *subWindow1 = new saveMdiSub;
//        subWindow1->setWidget(settings);
//        mdiArea->addSubWindow(subWindow1);
//        firstCreate=false;
//        subWindow1->show();
//    }
//    else{
//        QList<QMdiSubWindow *>	allSub=mdiArea->subWindowList();
//        for(auto x:allSub){
//            if(x->widget()==settings && x->isHidden()){
//                    x->show();
//            }
//        };
//    }
    QList<QMdiSubWindow *>	allSub=mdiArea->subWindowList();
    for(auto x:allSub){
        if(x->widget()->objectName()=="settings"){
//            qDebug()<<"open he";
            x->close();
        }
    }
    Settings *settings =new Settings(this);
    saveMdiSub *subWindow1 = new saveMdiSub;
    subWindow1->setWidget(settings);
    mdiArea->addSubWindow(subWindow1);
    subWindow1->setAttribute(Qt::WA_DeleteOnClose);
    subWindow1->show();
//    connect(settings->updateDB, SIGNAL(clicked()), subWindow1, SLOT(connectUpdateTable()));
    connect(settings->updateDB, SIGNAL(clicked()), subWindow1, SLOT(connectUpdateTable()));
    connect(subWindow1, SIGNAL(needUpdateThisIsWindow()), this, SLOT(on_actionOpenSettingstriggered()));
}

void MainWindow::on_actionCascadeSubWindows(){
    mdiArea->cascadeSubWindows();
}

void MainWindow::on_actionTileSubWindows(){
    mdiArea->tileSubWindows();
}

void MainWindow::on_actionAddCrossword_triggered(){
    Crossword *cross = new Crossword(mdiArea);
    mdiArea->addSubWindow(cross);
    cross->show();
}

void MainWindow::on_actionAddEngRus4x1_triggered(){
    EngRus *eng_rus_leo=new EngRus;
    QMdiSubWindow *subWindow1 = new QMdiSubWindow;
    subWindow1->setWidget(eng_rus_leo);
    subWindow1->setAttribute(Qt::WA_DeleteOnClose);
    mdiArea->addSubWindow(subWindow1);
    subWindow1->show();
}
