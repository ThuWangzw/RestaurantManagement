#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "user.h"

class Customer : public User
{
    Q_OBJECT
public:
    Customer();
    void saveData();
    vector<QString> &getDishesHaveDone();
    vector<QString> &getDishesNotDone();
    vector<QString> &getDishesNotPaid();
    vector<QString> &getDishesDoing();
    vector<QString> &getDishesEating();
    vector<int> &getDishesPrice();
    void addDishesNotPaid(QString t_dish);
    void addDishesPrice(int t_price);
    void addDishesNotDone(QString t_dish);
    void addDisherHaveDone(QString dishname);
    void addDishesDoing(QString dishdoing);
    void clearDishesNotPaid();
    void clearDisherPrice();
    void deleteDishesNotPaid(int num);
    void deleteDishesPrice(int num);
    void addDishesEating(QString neweat);
    int getTable();

    vector<QString> &getWaiter();
    void addWaiter(QString nwaiter);
    void delWaiter(QString dwaiter);
private:
    vector<QString> DishesHaveDone;
    vector<QString> DishesNotDone;
    vector<QString> DishesNotPaid;
    vector<QString> DishesDoing;
    vector<QString> DishesEating;
    vector<int> DishesPrice;
    vector<QString> waiter;
    int table;
signals:

public slots:
    void updateUser(QJsonObject *newUser);
    void setTable(int n);
};

#endif // CUSTOMER_H
