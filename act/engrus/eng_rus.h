#ifndef ENGRUS_H
#define ENGRUS_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <vector>
#include "backend/word.h"
#include "backend/leo_const.h"
class Button : public QPushButton
{
   Q_OBJECT
public:
    explicit Button(QWidget *parent = 0);
};

class EngRus : public QWidget
{
    Q_OBJECT
private:
    ~EngRus();
public:
    QLabel *main_Label;
    std::vector<Button*>listButton;
    std::vector<QPushButton*>listImage;
    explicit EngRus(QWidget *parent = 0,Leo::pos statusThis=Leo::pos::vertical);
    Leo::pos status;
    void nextRound();
    std::vector<Word> ListWord;
    std::vector<Word> EverWordList;
    std::vector<Word> sizeWordinLastSizeEnd;
    int MaxButton;
    Word TrueWord;
signals:

public slots:

private slots:
    void connectSelectWord();
    void connectSelectImage();
};
#endif // ENGRUS_H
