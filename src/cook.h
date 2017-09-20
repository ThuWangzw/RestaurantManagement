#ifndef COOK_H
#define COOK_H
#include "user.h"

class Cook : public User
{
    Q_OBJECT
public:
    Cook();
    void addDish(QString username,QString dishname);
    void clear();
    void updateUser(QJsonObject *user);
    void saveData();
    void cooknumadd();
    int getCookNum();
    vector<QString> &getCookDish();
    vector<QString> &getCookName();
private:
    int cooknum;
    vector<QString> CookDish;
    vector<QString> CookName;
signals:

public slots:
};

#endif // COOK_H
