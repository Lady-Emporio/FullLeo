//#include "crossword.h"
#include "mainwindows.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Crossword w;
//    w.show();
    MainWindow w;
    w.show();
    return a.exec();
}
