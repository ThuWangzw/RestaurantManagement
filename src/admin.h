#ifndef ADMIN_H
#define ADMIN_H
#include "user.h"

class Admin : public User
{
    Q_OBJECT
public:
    Admin();

signals:

public slots:
    void updateUser(QJsonObject* t_user);
};

#endif // ADMIN_H
