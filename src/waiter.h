#ifndef WAITER_H
#define WAITER_H
#include "user.h"

class Waiter : public User
{
    Q_OBJECT
public:
    Waiter();
    int getChargeTable();
    void savedata();
    int getWaitNum();
    void waitnumadd();
    void grade(int gra);
    void addMsg(QString msg);
    void addSender(QString user);
    vector<QString> &getMsg();
    vector<QString> &getSender();
private:
    int waitnum;
    int chargetable;
    vector<int> waitgrade;
    vector<QString> senduser;
    vector<QString> sendmsg;
signals:

public slots:
    void setChaegeTable(int n);
    void updateUser(QJsonObject *waiter);
};

#endif // WAITER_H
