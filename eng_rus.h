#ifndef RUSENG_H
#define RUSENG_H
#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <vector>
#include "word.h"
#include "bd.h"
class Button : public QPushButton
{
   Q_OBJECT
public:
    explicit Button(QWidget *parent = 0);
};

class EngRus : public QWidget
{
    Q_OBJECT
public:
    QLabel *main_Label;
    std::vector<Button*>listButton;
    explicit EngRus(QWidget *parent = 0);
    void nextRound();
    std::vector<Word> ListWord;
    Word TrueWord;
signals:

public slots:

private slots:
    void connectSelectWord();
};
#endif // RUSENG_H
