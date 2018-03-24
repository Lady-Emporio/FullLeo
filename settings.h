#ifndef SETTINGS_H
#define SETTINGS_H
#include <QComboBox>
#include <QWidget>
#include <QLabel>
#include <QEvent>
#include <QCloseEvent>
#include <QLineEdit>
class Settings : public QWidget
{
    Q_OBJECT
public:
    QComboBox *comboStyle;
    QComboBox *comboAlg;
    QLineEdit *countRow;
    QLineEdit *countColumn;
    QLabel *nowRow;
    QLabel *nowCol;

    static Settings * getSettings();
signals:

public slots:
    void connectSelectNewStyle_trigger(int);
    void connectALG_trigger(int);
    void connectSetRowAndColCount();
    void connectJUMP_trigger();
    void connectAUTOCOMPLETION_trigger();

private:
    void closeEvent(QCloseEvent *);
    explicit Settings(QWidget *parent = 0);

};

#endif // SETTINGS_H
