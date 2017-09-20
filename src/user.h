#ifndef USER_H
#define USER_H

#include <QObject>
#include <QString>
#include <vector>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTextStream>
#include <QFile>
#define CUSTOMER 1
#define ADMIN 0
#define COOK 2
#define WAITER 3
#define MANAGER 4
using std::vector;
class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QObject *parent = nullptr);
    QString getName();
    QString getPassword();
    int getType();

    void setName(QString t_name);
    void setPassword(QString t_password);
    void setType(int t_type);
protected:
    QString name;
    QString password;
    int type;
signals:

public slots:
};

#endif // USER_H
