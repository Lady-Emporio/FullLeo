#ifndef NOTVISUALONEROW_H
#define NOTVISUALONEROW_H
#include "backend/leo_const.h"
#include "backend/word.h"
#include <QWidget>
#include <QMediaPlayer>
#include <QDir>
#include <QPushButton>
#include <QLabel>
#include <QKeyEvent>
class NotVisualOneRow : public QWidget
{
    Q_OBJECT
    void keyPressEvent(QKeyEvent * event);
public:
    explicit NotVisualOneRow(QWidget *parent = 0);
    QMediaPlayer *player;
    std::vector<Word> ListWord;
    std::vector<Word> EverWordList;
    QLabel *TrueLabel;
    QLabel *InputLabel;
    Word TrueWord;
    int indexInput;
signals:

public slots:
    void NextRound();
};

#endif // NOTVISUALONEROW_H
