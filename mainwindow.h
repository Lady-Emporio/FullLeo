#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMdiArea>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include "QMdiSubWindow"
#include "backend/leo_const.h"
#include "backend/leo_setting.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QMdiArea * mdiArea;  // Область, в которую будут добавляться окна //пока debug она private
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    QMenuBar *highTopMenu;
public slots:
    void on_actionOpenSettingstriggered();//debug
    void on_actionAddCrossword_triggered();//debug
    void on_actionAddEngRus4x1_triggered();
private slots:
    void on_actionCascadeSubWindows();
    void on_actionTileSubWindows();

};



class saveMdiSub : public QMdiSubWindow //чтобы настройки не удалялись при закрытии окна
{
    Q_OBJECT
public:
    explicit saveMdiSub(QWidget *parent = 0);

signals:
    void needUpdateThisIsWindow();//При нажатии клавиши посылается сигнал, который mdiArea перенаправляет в sub, sub меняет все и отправляет сигнал на удаление себя же в mdiArea.
public slots:

private:
    void closeEvent(QCloseEvent *);
    ~saveMdiSub();
private slots:
    void connectUpdateTable();
};

#endif // MAINWINDOW_H
