#ifndef SETTINGS_H
#define SETTINGS_H
#include <QComboBox>
#include <QWidget>
#include <QLabel>
class Settings : public QWidget
{
    Q_OBJECT
public:
    explicit Settings(QWidget *parent = 0);
    QComboBox *comboBoxsize;
    QComboBox *comboBoxstyle;
    QLabel *sizeRow;
signals:

public slots:
    void connectSelectNewStyle_trigger(int);
private:

};

#endif // SETTINGS_H
