#ifndef MAINWINDOWS_H
#define MAINWINDOWS_H
#include "crossword.h"
#include <QMainWindow>
#include <QMdiArea>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include "QMdiSubWindow"
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

signals:

public slots:

private:
    QMdiArea * mdiArea;  // Область, в которую будут добавляться окна
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
