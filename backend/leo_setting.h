#ifndef LEOSETTING_H
#define LEOSETTING_H


#include <QComboBox>
#include <QWidget>
#include <QLabel>
#include <QEvent>
#include <QCloseEvent>
#include <QLineEdit>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDebug>
#include <QStringList>
#include <QPushButton>
#include <QRadioButton>
#include <QGroupBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QListWidget>
class Settings : public QWidget
{
    Q_OBJECT
public:
    static Settings * getSettings();
    QGroupBox * groupDB();//получаем группу с базой
    QGroupBox * groupFont();
    QGroupBox * groupStyle();
    QGroupBox * groupEngRus();
    explicit Settings(QWidget *parent = 0);
    QPushButton *updateDB;
signals:

public slots:
private:
    void closeEvent(QCloseEvent *);
    ~Settings();
private slots:
    void connectIntFromDB(const QString &);
    void connectPathToDB(const QString &);
    void connectFontSize(const QString &);
    void connectFontFamily(const QString &);
    void connectRowTable(const QString &);
    void connectColTable(const QString &);
    void connectALG_trigger(const QString &);
    void connectStyleJson_trigger(const QString &);
    void connectAUTOCOMPLETION_trigger();
    void connectJUMP_trigger();
    void connectAudio_trigger();
    void connectGRIDTABLE_trigger();
};

#endif // LEOSETTING_H
