#ifndef DISH_H
#define DISH_H
#include <QString>
#include <vector>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QByteArray>
#include <QJsonDocument>
#include <QTextStream>
using std::vector;
class Dish
{
public:
    Dish(QJsonObject *t_json);
    Dish(){}
    QString getName();
    int getPrice();
    vector<QString>& getComment();
    void setName(QString t_name);
    void setPrice(int t_price);
    void addComment(QString t_comment);
    bool saveDish();
    void addToLoaclMain();
private:
    QString name;
    int price;
    vector<QString> Comment;
};

#endif // DISH_H
