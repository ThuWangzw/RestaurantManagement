#include "manager.h"

Manager::Manager()
{

}

void Manager::updateUser(QJsonObject *user)
{
    name = user->value("name").toString();
    password = user->value("password").toString();
    type = user->value("type").toInt();
}
