#include "abstractshow.h"
QJsonArray *AbstractShow::allUser = new QJsonArray;
vector<Dish*> AbstractShow::allDish;
AbstractShow::AbstractShow(QObject *parent) : QObject(parent)
{

}

void AbstractShow::ShowMessage(QString message)
{
    QMessageBox *m_msgBox = new QMessageBox;
    m_msgBox->setInformativeText(message);
    m_msgBox->setStandardButtons(QMessageBox::Ok);
    connect((QObject *)m_msgBox->button(QMessageBox::Ok),SIGNAL(clicked(bool)),m_msgBox,SLOT(close()));
    m_msgBox->show();
}

bool AbstractShow::NewUserLoadInJson(QString name, QString password, int type)
{
    QJsonObject userObj;
    userObj.insert("name",name);
    userObj.insert("password",password);
    userObj.insert("type",type);

    QJsonDocument userDoc;
    userDoc.setObject(userObj);

    QString fileName;
    fileName.append(name);
    fileName.append(".json");
    QFile userFile(fileName);
    if(!userFile.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        ShowMessage("Load json error!");
        return false;
    }

    QTextStream userStream(&userFile);
    userStream<<userDoc.toJson();
    userFile.close();
    return true;
}

bool AbstractShow::addUserToLocal(QString user)
{
    QJsonArray all;
    for(int i = 0; i<allUser->size();i++) all.push_back(allUser->at(i));
    all.push_back(user);

    QJsonDocument userDoc;
    userDoc.setArray(all);

    QFile deleteFile("AllUser.json");
    deleteFile.remove();

    QFile userFile("AllUser.json");
    if(!userFile.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        ShowMessage("Load json error!");
        return false;
    }

    QTextStream userStream(&userFile);
    userStream<<userDoc.toJson();
    userFile.close();
    allUser->push_back(user);
    return true;
}

User *AbstractShow::loadUser(QString name)
{
    User *m_user = new User;
    QString fileName(name);
    fileName.append(".json");
    QFile mfile(fileName);
    mfile.open(QIODevice::ReadOnly);
    QByteArray mbyte = mfile.readAll();
    mfile.close();

    QJsonDocument mdoc = QJsonDocument::fromJson(mbyte);
    QJsonObject mobj = mdoc.object();
    m_user->setName(mobj.value("name").toString());
    m_user->setPassword(mobj.value("password").toString());
    m_user->setType(mobj.value("type").toInt());
    return m_user;
}
