#include "cook.h"
#include <QDebug>
Cook::Cook()
{

}

void Cook::addDish(QString username, QString dishname)
{
    CookDish.push_back(dishname);
    CookName.push_back(username);
}

void Cook::clear()
{
    vector<QString> temp;
    CookDish.clear();
    CookDish.swap(temp);
    CookName.clear();
    CookName.swap(temp);
}

void Cook::updateUser(QJsonObject *user)
{
    name = user->value("name").toString();
    password = user->value("password").toString();
    type = user->value("type").toInt();
    cooknum = user->value("cooknum").toInt();
    clear();
    QJsonArray userarray = user->value("cookname").toArray();
    for(QJsonArray::iterator iter = userarray.begin();iter != userarray.end();iter++)
    {
        CookName.push_back((*iter).toString());
    }
    QJsonArray disharray = user->value("cookdish").toArray();
    for(QJsonArray::iterator iter = disharray.begin();iter != disharray.end();iter++)
    {
        CookDish.push_back((*iter).toString());
    }
}

void Cook::saveData()
{
    QJsonObject userObj;
    userObj.insert("name",name);
    userObj.insert("password",password);
    userObj.insert("type",type);
    userObj.insert("cooknum",cooknum);
    QJsonArray userarray;
    for(vector<QString>::iterator iter = CookName.begin();iter != CookName.end(); iter++)
    {
        userarray.push_back(*iter);
    }
    userObj.insert("cookname",userarray);
    QJsonArray disharray;
    for(vector<QString>::iterator iter = CookDish.begin();iter != CookDish.end(); iter++)
    {
        disharray.push_back(*iter);
    }
    userObj.insert("cookdish",disharray);

    QJsonDocument userDoc;
    userDoc.setObject(userObj);

    QString fileName;
    fileName.append(name);
    fileName.append(".json");
    QFile deleteFile(fileName);
    deleteFile.remove();

    QFile userFile(fileName);
    if(!userFile.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        return;
    }

    QTextStream userStream(&userFile);
    userStream<<userDoc.toJson();
    userFile.close();
    qDebug()<<"cook saved";
    return;
}

vector<QString> &Cook::getCookDish()
{
    return CookDish;
}

vector<QString> &Cook::getCookName()
{
    return CookName;
}

void Cook::cooknumadd()
{
    cooknum++;
}

int Cook::getCookNum()
{
    return cooknum;
}
