#include "waiter.h"
#include <QDebug>
Waiter::Waiter()
{
    chargetable = 0;
}

int Waiter::getChargeTable()
{
    return chargetable;
}

void Waiter::setChaegeTable(int n)
{
    chargetable = n;
}

void Waiter::updateUser(QJsonObject *waiter)
{
    name = waiter->value("name").toString();
    password = waiter->value("password").toString();
    type = waiter->value("type").toInt();
    chargetable = waiter->value("table").toInt();
    waitnum = waiter->value("waitnum").toInt();

    vector<QString> temp;
    senduser.clear();
    senduser.swap(temp);
    sendmsg.clear();
    sendmsg.swap(temp);
    vector<int> v;
    waitgrade.clear();
    waitgrade.swap(v);
    QJsonArray gradearray = waiter->value("waitgrade").toArray();
    for(QJsonArray::iterator iter = gradearray.begin();iter != gradearray.end(); iter++)
    {
        waitgrade.push_back((*iter).toInt());
    }
    for(int j = waitgrade.size() - 1; j < 6; j++) waitgrade.push_back(0);
    QJsonArray userarray = waiter->value("username").toArray();
    for(QJsonArray::iterator iter = userarray.begin();iter != userarray.end(); iter++)
    {
        senduser.push_back((*iter).toString());
    }
    QJsonArray msgarray = waiter->value("msgname").toArray();
    for(QJsonArray::iterator iter = msgarray.begin();iter != msgarray.end(); iter++)
    {
        sendmsg.push_back((*iter).toString());
    }
}

void Waiter::savedata()
{
    QJsonObject userObj;
    userObj.insert("name",name);
    userObj.insert("password",password);
    userObj.insert("type",type);
    userObj.insert("table",chargetable);
    userObj.insert("waitnum",waitnum);
    QJsonArray userarray;
    QJsonArray msgarray;
    QJsonArray gradearray;
    for(vector<QString>::iterator iter = senduser.begin();iter != senduser.end(); iter++)
        userarray.push_back(*iter);
    userObj.insert("username",userarray);
    for(vector<QString>::iterator iter = sendmsg.begin();iter != sendmsg.end(); iter++)
        msgarray.push_back(*iter);
    userObj.insert("msgname",msgarray);
    for(vector<int>::iterator iter = waitgrade.begin();iter != waitgrade.end(); iter++)
        gradearray.push_back(*iter);
    userObj.insert("waitgrade",gradearray);

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
    return;
}

void Waiter::addMsg(QString msg)
{
    sendmsg.insert(sendmsg.begin(),msg);
}

void Waiter::addSender(QString user)
{
    senduser.insert(senduser.begin(),user);
}

vector<QString> &Waiter::getMsg()
{
    return sendmsg;
}

vector<QString> &Waiter::getSender()
{
    return senduser;
}

void Waiter::waitnumadd()
{
    waitnum++;
    savedata();
}

void Waiter::grade(int gra)
{
    if(gra<0||gra>6) return;
    waitgrade[gra] = waitgrade[gra] + 1;
}

int Waiter::getWaitNum()
{
    return waitnum;
}
