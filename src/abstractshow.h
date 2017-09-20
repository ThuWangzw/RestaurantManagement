#ifndef ABSTRACTSHOW_H
#define ABSTRACTSHOW_H

#include <QObject>
#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QTextStream>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QComboBox>
#include <QFont>
#include <QLabel>
#include "vector"
using std::vector;
#include "dish.h"
#include "user.h"
#define MAIN 0
#define REGISTER 1
#define CUSTOMERMAIN 2
#define CUSTOMERCACU 3
#define CUSTOMERPRO 4
#define ADMINMAIN 5
#define ADMINCTRL 6
#define COOKMAIN 7
#define WAITERMAIN 8
#define MANAGERMAIN 9
class AbstractShow : public QObject
{
    Q_OBJECT
public:
    explicit AbstractShow(QObject *parent = nullptr);
    static void ShowMessage(QString message);
    bool NewUserLoadInJson(QString name,QString password,int type);
    static QJsonArray *allUser;
    static vector<Dish*> allDish;
    bool addUserToLocal(QString user);
    User *loadUser(QString name);
    //bool deeleteUserFromLocal(QString user);
protected:
    int type;
    QMainWindow *mainwindow;
signals:
    void REconnect(int Type);
public slots:

};

#endif // ABSTRACTSHOW_H
