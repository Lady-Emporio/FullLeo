#ifndef MAINWINDOWS_H
#define MAINWINDOWS_H
#include "crossword.h"
#include <QMainWindow>
#include <QMdiArea>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

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
};

#endif // MAINWINDOWS_H
