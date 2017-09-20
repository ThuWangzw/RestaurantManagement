#include "admin.h"

Admin::Admin()
{

}

void Admin::updateUser(QJsonObject *t_user)
{
    name = t_user->value("name").toString();
    password = t_user->value("password").toString();
    type = t_user->value("type").toInt();
}
