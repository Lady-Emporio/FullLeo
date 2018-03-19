#ifndef CONST_H
#define CONST_H
#include <QColor>
#include <QBrush>
int const TABLE_ROW=40;
int const TABLE_COL=40;
int const ROWHEIGHT=20;
int const COLUMNWIDTH=20;
int const MARGIN1=65;
enum status{freely,block,wordHere};
enum pos{vertical,horizontal,zero};


QBrush const DEFAULTQB=QBrush(QColor(255, 255, 255));
QBrush const NOTUSEQB=QBrush(QColor(0, 255, 255));
QBrush const TRUEQB=QBrush(QColor(255, 140, 0));
QBrush const FALSEQB=QBrush(QColor(219, 112, 147));
QBrush const GRIDQB=QBrush(QColor(255, 0, 0));
QBrush const ACTIVEINTABLEQB=QBrush(QColor(0, 255, 0));
QBrush const ACTIVELISTQB=QBrush(QColor(128, 128, 128));
#endif // CONST_H
