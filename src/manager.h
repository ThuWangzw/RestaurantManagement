#ifndef MANAGER_H
#define MANAGER_H
#include"user.h"

class Manager : public User
{
    Q_OBJECT
public:
    Manager();

signals:

public slots:
    void updateUser(QJsonObject *user);
};

#endif // MANAGER_H
