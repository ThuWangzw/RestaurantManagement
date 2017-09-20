#include "dish.h"

Dish::Dish(QJsonObject *t_json)
{
    name = t_json->value("name").toString();
    price = t_json->value("price").toInt();
    QJsonArray t_array = t_json->value("comment").toArray();
    for(QJsonArray::iterator iter = t_array.begin();iter!=t_array.end();iter++)
    {
        Comment.push_back((*iter).toString());
    }
}

QString Dish::getName()
{
    return name;
}

int Dish::getPrice()
{
    return price;
}

vector<QString> &Dish::getComment()
{
    return Comment;
}

void Dish::setName(QString  t_name)
{
    name.clear();
    name.append(t_name);
}

void Dish::setPrice(int t_price)
{
    price = t_price;
}

void Dish::addComment(QString t_comment)
{
    Comment.push_back(t_comment);
}

bool Dish::saveDish()
{
    QString fileName(name);
    fileName.append(".json");
    QJsonObject dishobj;
    dishobj.insert("name",name);
    dishobj.insert("price",price);
    QJsonArray dishArray;
    for(vector<QString>::iterator iter = Comment.begin();iter!=Comment.end();iter++)
        dishArray.push_back(*iter);
    dishobj.insert("comment",dishArray);
    QJsonDocument dishDoc;
    dishDoc.setObject(dishobj);

    QFile deleteFile(fileName);
    deleteFile.remove();

    QFile dishFile(fileName);
    if(!dishFile.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        return false;
    }

    QTextStream dishStream(&dishFile);
    dishStream<<dishDoc.toJson();//??????????????????
    dishFile.close();
    return true;
}

void Dish::addToLoaclMain()
{

}
