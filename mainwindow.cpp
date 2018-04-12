#include "mainwindow.h"
#include "backend/leo_setting.h"
#include "act/crossword/crossword.h"
#include "act/engrus/eng_rus.h"
#include "backend/list_word_db.h"
#include "act/write/input_write.h"
#include "act/notvisual/not_visual_one_row.h"

saveMdiSub::saveMdiSub(QWidget *parent) :QMdiSubWindow(parent){}
void saveMdiSub::closeEvent(QCloseEvent *event){ /*work but i not know;*/}
saveMdiSub::~saveMdiSub(){/*qDebug()<<"we are del";*/}
void saveMdiSub::connectUpdateTable(){
//     LeoConst::CONST()->GetFromBD();
    LeoConst::CONST()->THIS_IS_ALL_UPDATE_fromfileAndBD();
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
    QMenu*  crossword_menu   = new QMenu("Crossword");
    QMenu*  x_vs_y_menu   = new QMenu("X vs Y");
    QMenu*  inputWrite_menu   = new QMenu("Input write");
    QMenu*  Visual_menu   = new QMenu("Visual");
    addMenu->addMenu(crossword_menu);
    addMenu->addMenu(x_vs_y_menu);
    addMenu->addMenu(inputWrite_menu);
    addMenu->addMenu(Visual_menu);

    crossword_menu->addAction("New crossword",this,SLOT(on_actionAddCrossword_triggered()));
    x_vs_y_menu->addAction("New EngRus wrong vert",this,SLOT(on_actionAddEngRus4x1_vert_triggered()));
    x_vs_y_menu->addAction("New EngRus wrong hori",this,SLOT(on_actionAddEngRus4x1_hori_triggered()));
    inputWrite_menu->addAction("New InputWite",this,SLOT(on_actionAddInputWite_triggered()));
    inputWrite_menu->addAction("New random",this,SLOT(on_actionAddInputWrite_Random_triggered()));
    inputWrite_menu->addAction("New sort A-Z",this,SLOT(on_actionAddInputWrite_Sort_A_Z_triggered()));
    inputWrite_menu->addAction("New sort Z-A",this,SLOT(on_actionAddInputWrite_Sort_triggered()));
    inputWrite_menu->addAction("New one row",this,SLOT(on_actionAddOneRowtriggered()));
    inputWrite_menu->addAction("New one sort A-Z",this,SLOT(on_actionAddOneRow_A_Z_triggered()));
    inputWrite_menu->addAction("New one sort Z-A",this,SLOT(on_actionAddOneRow_Z_A_triggered()));
    inputWrite_menu->addAction("New one random",this,SLOT(on_actionAddOneRow_random_triggered()));
    inputWrite_menu->addAction("New one contra Vice versa",this,SLOT(on_actionAddOneRow_contra_Vice_versa_triggered()));
    Visual_menu->addAction("New visual",this,SLOT(on_actionAdd_visual_triggered()));
    windowMenu->addAction("Cascade sub windows",this,SLOT(on_actionCascadeSubWindows()));
    windowMenu->addAction("Tile sub windows",this,SLOT(on_actionTileSubWindows()));
    windowMenu->addAction("Sub window view",this,SLOT(on_actionSubWindowView()));
    windowMenu->addAction("Tabbed view",this,SLOT(on_actionTabbedView()));
}

void MainWindow::on_actionAdd_visual_triggered(){
    NotVisualOneRow *input =new NotVisualOneRow(this);
    saveMdiSub *subWindow1 = new saveMdiSub;
    subWindow1->setWidget(input);
    mdiArea->addSubWindow(subWindow1);
    subWindow1->setAttribute(Qt::WA_DeleteOnClose);
    subWindow1->show();
}

void MainWindow::on_actionAddOneRow_contra_Vice_versa_triggered(){
    OneLongRowTable *input =new OneLongRowTable(this,Leo::contra_Vice_versa);
    saveMdiSub *subWindow1 = new saveMdiSub;
    subWindow1->setWidget(input);
    mdiArea->addSubWindow(subWindow1);
    subWindow1->setAttribute(Qt::WA_DeleteOnClose);
    subWindow1->show();
}

void MainWindow::on_actionAddInputWrite_Random_triggered(){
    InputWrite *input =new InputWrite(this,Leo::Type::random);
    saveMdiSub *subWindow1 = new saveMdiSub;
    subWindow1->setWidget(input);
    mdiArea->addSubWindow(subWindow1);
    subWindow1->setAttribute(Qt::WA_DeleteOnClose);
    subWindow1->show();
}
void MainWindow::on_actionAddInputWrite_Sort_triggered(){
    InputWrite *input =new InputWrite(this,Leo::Type::sortZ_A);
    saveMdiSub *subWindow1 = new saveMdiSub;
    subWindow1->setWidget(input);
    mdiArea->addSubWindow(subWindow1);
    subWindow1->setAttribute(Qt::WA_DeleteOnClose);
    subWindow1->show();
}
void MainWindow::on_actionAddInputWrite_Sort_A_Z_triggered(){
    InputWrite *input =new InputWrite(this,Leo::Type::sortA_Z);
    saveMdiSub *subWindow1 = new saveMdiSub;
    subWindow1->setWidget(input);
    mdiArea->addSubWindow(subWindow1);
    subWindow1->setAttribute(Qt::WA_DeleteOnClose);
    subWindow1->show();
}
void MainWindow::on_actionAddOneRowtriggered(){
    OneLongRowTable *input =new OneLongRowTable(this,Leo::Type::common);
    saveMdiSub *subWindow1 = new saveMdiSub;
    subWindow1->setWidget(input);
    mdiArea->addSubWindow(subWindow1);
    subWindow1->setAttribute(Qt::WA_DeleteOnClose);
    subWindow1->show();
}

void MainWindow::on_actionAddOneRow_A_Z_triggered(){
    OneLongRowTable *input =new OneLongRowTable(this,Leo::Type::sortA_Z);
    saveMdiSub *subWindow1 = new saveMdiSub;
    subWindow1->setWidget(input);
    mdiArea->addSubWindow(subWindow1);
    subWindow1->setAttribute(Qt::WA_DeleteOnClose);
    subWindow1->show();
}
void MainWindow::on_actionAddOneRow_Z_A_triggered(){
    OneLongRowTable *input =new OneLongRowTable(this,Leo::Type::sortZ_A);
    saveMdiSub *subWindow1 = new saveMdiSub;
    subWindow1->setWidget(input);
    mdiArea->addSubWindow(subWindow1);
    subWindow1->setAttribute(Qt::WA_DeleteOnClose);
    subWindow1->show();
}
void MainWindow::on_actionAddOneRow_random_triggered(){
    OneLongRowTable *input =new OneLongRowTable(this,Leo::Type::random);
    saveMdiSub *subWindow1 = new saveMdiSub;
    subWindow1->setWidget(input);
    mdiArea->addSubWindow(subWindow1);
    subWindow1->setAttribute(Qt::WA_DeleteOnClose);
    subWindow1->show();
}




void MainWindow::on_actionSubWindowView(){
    mdiArea->setViewMode(QMdiArea::SubWindowView);
}
void MainWindow::on_actionTabbedView(){
    mdiArea->setViewMode(QMdiArea::TabbedView);
}

MainWindow::~MainWindow()
{

}
void MainWindow::on_actionAddInputWite_triggered(){
    InputWrite *input =new InputWrite(this);
    saveMdiSub *subWindow1 = new saveMdiSub;
    subWindow1->setWidget(input);
    mdiArea->addSubWindow(subWindow1);
    subWindow1->setAttribute(Qt::WA_DeleteOnClose);
    subWindow1->show();
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

void MainWindow::on_actionAddEngRus4x1_vert_triggered(){
    EngRus *eng_rus_leo=new EngRus(this,Leo::vertical);
    QMdiSubWindow *subWindow1 = new QMdiSubWindow;
    subWindow1->setWidget(eng_rus_leo);
    subWindow1->setAttribute(Qt::WA_DeleteOnClose);
    mdiArea->addSubWindow(subWindow1);
    subWindow1->show();
}
void MainWindow::on_actionAddEngRus4x1_hori_triggered(){
    EngRus *eng_rus_leo=new EngRus(this,Leo::horizontal);
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
