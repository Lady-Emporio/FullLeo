#include "mainwindows.h"
#include "settings.h"
#include "QMdiSubWindow"
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
    Settings *settings =new Settings;
    settings->setParent(mdiArea);
    mdiArea->addSubWindow(settings);
    settings->show();
}
