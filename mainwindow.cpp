#include "mainwindow.h"
#include "backend/leo_setting.h"
#include "act/crossword/crossword.h"
#include "act/engrus/eng_rus.h"
#include "backend/list_word_db.h"

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
    highTopMenu->addAction("DB word",this,SLOT(on_actionOpenListWordDBstriggered()));
    highTopMenu->addAction("Active bd",this,SLOT(on_actionActiveBD()));

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
    QList<QMdiSubWindow *>	allSub=mdiArea->subWindowList();
    for(auto x:allSub){
        if(x->widget()->objectName()=="settings"){
            x->close();
        }
    }
    Settings *settings =new Settings(this);
    saveMdiSub *subWindow1 = new saveMdiSub;
    subWindow1->setWidget(settings);
    mdiArea->addSubWindow(subWindow1);
    subWindow1->setAttribute(Qt::WA_DeleteOnClose);
    subWindow1->show();
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
void MainWindow::on_actionOpenListWordDBstriggered(){
    ListWordDB *widgetEditDB=new ListWordDB;
    QMdiSubWindow *subWindow1 = new QMdiSubWindow;
    subWindow1->setWidget(widgetEditDB);
    subWindow1->setAttribute(Qt::WA_DeleteOnClose);
    mdiArea->addSubWindow(subWindow1);
    subWindow1->show();
}

void MainWindow::on_actionActiveBD(){
    QWidget *w=new QWidget(this);
    QVBoxLayout *mainLayout=new QVBoxLayout(w);
    QListWidget *WordInActive=new QListWidget(w);
    w->setLayout(mainLayout);
    mainLayout->addWidget(WordInActive);
    std::vector <Word> nowWordList;
    QMdiSubWindow *activeSub=mdiArea->activeSubWindow();
    if(activeSub==0){
        QMessageBox msgBox;
        msgBox.setText("Нет активного виджета");
        msgBox.exec();
        return;
    }
    if(activeSub->widget()->objectName()=="EngRus"){
        EngRus * now=qobject_cast<EngRus *>(activeSub->widget());
        nowWordList=now->ListWord;
    }
    for(size_t i=0;i!=nowWordList.size();++i){
        QListWidgetItem *next=new QListWidgetItem(WordInActive);
        next->setText(nowWordList[i].eng+" | "+nowWordList[i].ru);
        WordInActive->addItem(next);
    }
    QMdiSubWindow *subWindow1 = new QMdiSubWindow;
    subWindow1->setWidget(w);
    subWindow1->setAttribute(Qt::WA_DeleteOnClose);
    mdiArea->addSubWindow(subWindow1);
    subWindow1->show();
}
