#include "customer.h"

Customer::Customer()
{
    table = 0;
}

void Customer::updateUser(QJsonObject *newUser)
{
    name = newUser->value("name").toString();
    password = newUser->value("password").toString();
    type = newUser->value("type").toInt();
    table = newUser->value("table").toInt();
    //clear
    vector<QString> temp;
    DishesHaveDone.clear();
    DishesHaveDone.swap(temp);

    DishesNotDone.clear();
    DishesNotDone.swap(temp);

    DishesNotPaid.clear();
    DishesNotPaid.swap(temp);

    DishesDoing.clear();
    DishesDoing.swap(temp);

    waiter.clear();
    waiter.swap(temp);

    DishesEating.clear();
    DishesEating.swap(temp);
    vector<int> v;
    DishesPrice.clear();
    DishesPrice.swap(v);
    //load
    QJsonArray arraywaiter = newUser->value("waiter").toArray();
    for(QJsonArray::iterator iter = arraywaiter.begin();iter != arraywaiter.end();iter++)
    {
        waiter.push_back((*iter).toString());
    }
    QJsonArray dishhavedone = newUser->value("havedone").toArray();
    for(QJsonArray::iterator iter = dishhavedone.begin();iter != dishhavedone.end();iter++)
    {
        DishesHaveDone.push_back((*iter).toString());
    }
    QJsonArray disheating = newUser->value("eating").toArray();
    for(QJsonArray::iterator iter = disheating.begin();iter != disheating.end();iter++)
    {
        DishesEating.push_back((*iter).toString());
    }
    QJsonArray dishnotdone = newUser->value("notdone").toArray();
    for(QJsonArray::iterator iter = dishnotdone.begin();iter != dishnotdone.end();iter++)
    {
        DishesNotDone.push_back((*iter).toString());
    }
    QJsonArray dishnotpaid = newUser->value("notpaid").toArray();
    for(QJsonArray::iterator iter = dishnotpaid.begin();iter != dishnotpaid.end();iter++)
    {
        DishesNotPaid.push_back((*iter).toString());
    }
    QJsonArray dishdoing = newUser->value("doing").toArray();
    for(QJsonArray::iterator iter = dishdoing.begin();iter != dishdoing.end();iter++)
    {
        DishesDoing.push_back((*iter).toString());
    }
    QJsonArray dishprice = newUser->value("price").toArray();
    for(QJsonArray::iterator iter = dishprice.begin();iter != dishprice.end();iter++)
    {
        DishesPrice.push_back((*iter).toInt());
    }
}

vector<int> &Customer::getDishesPrice()
{
    return DishesPrice;
}

vector<QString> &Customer::getDishesNotPaid()
{
    return DishesNotPaid;
}

vector<QString> &Customer::getDishesDoing()
{
    return DishesDoing;
}

vector<QString> &Customer::getDishesHaveDone()
{
    return DishesHaveDone;
}

vector<QString> &Customer::getDishesEating()
{
    return DishesEating;
}

vector<QString> &Customer::getDishesNotDone()
{
    return DishesNotDone;
}

void Customer::addDishesNotPaid(QString t_dish)
{
    DishesNotPaid.push_back(t_dish);
}

void Customer::addDishesPrice(int t_price)
{
    DishesPrice.push_back(t_price);
}

void Customer::saveData()
{
    QJsonObject userObj;
    userObj.insert("name",name);
    userObj.insert("password",password);
    userObj.insert("type",type);
    userObj.insert("table",table);

    QJsonArray ArrayWaiter;
    for(vector<QString>::iterator iter = waiter.begin();iter!=waiter.end();iter++)
        ArrayWaiter.push_back(*iter);
    userObj.insert("waiter",ArrayWaiter);
    QJsonArray haveDone;
    for(vector<QString>::iterator iter = DishesHaveDone.begin();iter!=DishesHaveDone.end();iter++)
        haveDone.push_back(*iter);
    userObj.insert("havedone",haveDone);
    QJsonArray eating;
    for(vector<QString>::iterator iter = DishesEating.begin();iter!=DishesEating.end();iter++)
        eating.push_back(*iter);
    userObj.insert("eating",eating);
    QJsonArray notDone;
    for(vector<QString>::iterator iter = DishesNotDone.begin();iter!=DishesNotDone.end();iter++)
        notDone.push_back(*iter);
    userObj.insert("notdone",notDone);
    QJsonArray notPaid;
    for(vector<QString>::iterator iter = DishesNotPaid.begin();iter!=DishesNotPaid.end();iter++)
        notPaid.push_back(*iter);
    userObj.insert("notpaid",notPaid);
    QJsonArray Doing;
    for(vector<QString>::iterator iter = DishesDoing.begin();iter!=DishesDoing.end();iter++)
        Doing.push_back(*iter);
    userObj.insert("doing",Doing);
    QJsonArray dishPrice;
    for(vector<int>::iterator iter = DishesPrice.begin();iter!=DishesPrice.end();iter++)
        dishPrice.push_back(*iter);
    userObj.insert("price",dishPrice);
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

void Customer::deleteDishesNotPaid(int num)
{
    vector<QString>::iterator iter = DishesNotPaid.begin();
    for(int i = 0;i<num;i++,iter++);
    DishesNotPaid.erase(iter);
}

void Customer::deleteDishesPrice(int num)
{
    vector<int>::iterator iter = DishesPrice.begin();
    for(int i = 0;i<num;i++,iter++);
    DishesPrice.erase(iter);
}

void Customer::addDishesNotDone(QString t_dish)
{
    DishesNotDone.push_back(t_dish);
}

void Customer::addDishesDoing(QString dishdoing)
{
    DishesDoing.push_back(dishdoing);
}

void Customer::clearDisherPrice()
{
    vector<int> v;
    DishesPrice.clear();
    DishesPrice.swap(v);
}

void Customer::clearDishesNotPaid()
{
    vector<QString> temp;
    DishesNotPaid.clear();
    DishesNotPaid.swap(temp);
}

void Customer::addDisherHaveDone(QString dishname)
{
    DishesHaveDone.push_back(dishname);
}

int Customer::getTable()
{
    return table;
}

void Customer::setTable(int n)
{
    table = n;
}

void Customer::addWaiter(QString nwaiter)
{
    waiter.push_back(nwaiter);
}

vector<QString> &Customer::getWaiter()
{
    return waiter;
}

void Customer::delWaiter(QString dwaiter)
{
    for(vector<QString>::iterator iter = waiter.begin();iter != waiter.end(); iter++)
    {
        QString now = *iter;
        if(dwaiter==now)
        {
            waiter.erase(iter);
            return;
        }
    }
}

void Customer::addDishesEating(QString neweat)
{
    DishesEating.push_back(neweat);
}
