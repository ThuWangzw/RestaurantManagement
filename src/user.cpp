#include "user.h"

User::User(QObject *parent) : QObject(parent)
{

}

QString User::getName()
{
    return name;
}

QString User::getPassword()
{
    return password;
}

int User::getType()
{
    return type;
}

void User::setName(QString t_name)
{
    name = t_name;
}

void User::setPassword(QString t_password)
{
    password = t_password;
}

void User::setType(int t_type)
{
    type = t_type;
}
