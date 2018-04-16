#ifndef XY_H
#define XY_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <vector>
#include "backend/word.h"
#include "backend/leo_const.h"

class XY : public QWidget
{
    Q_OBJECT
public:
    explicit XY(QWidget *parent = 0);
    QLabel *main_Label;
    QLabel *ImageLabel;
    std::vector<Word> ListWord;
    std::vector<Word> UsingWordForStory;
    std::vector<Word> EverWordList;
    std::vector<Word> sizeWordinLastSizeEnd;
    std::vector<QPushButton*>listButton;
    int MaxButton;
    Word TrueWord;
    void nextRound();
    int RoundForLabel;
    int NomberForLabel;
    QLabel *NomberLabel;
    QLabel *RoundLabel;
signals:
public slots:
    void connectSelectWord();
};

#endif // XY_H
