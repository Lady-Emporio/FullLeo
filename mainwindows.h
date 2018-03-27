#ifndef MAINWINDOWS_H
#define MAINWINDOWS_H
#include "crossword.h"
#include <QMainWindow>
#include <QMdiArea>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include "QMdiSubWindow"
#include "updown/up_down.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    QMdiArea * mdiArea;  // Область, в которую будут добавляться окна  //пока тест пусть будет публик. Отлаживать легче.
signals:

public slots:

private:

    QMenuBar *highTopMenu;
private slots:
    void on_actionAddCrossword_triggered();
    void on_actionOpenSettingstriggered();
    void on_actionCascadeSubWindows();
    void on_actionTileSubWindows();
    void on_actionAddEngRus4x1_triggered();
};

#endif // MAINWINDOWS_H


class saveMdiSub : public QMdiSubWindow
{
    Q_OBJECT
public:
    explicit saveMdiSub(QWidget *parent = 0);

signals:

public slots:

private:
    void closeEvent(QCloseEvent *);
private slots:
};
