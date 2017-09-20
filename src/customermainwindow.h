#ifndef CUSTOMERMAINWINDOW_H
#define CUSTOMERMAINWINDOW_H
#include "abstractshow.h"
#include "customer.h"
#include "ui_customermainwindow.h"
#include "ui_customercacu.h"
#include "ui_customerprogress.h"
#include "waiter.h"
class CustomerMainWindow : public AbstractShow
{
    Q_OBJECT
public:
    CustomerMainWindow(QMainWindow *mainWindow);
    Ui::CustomerMainWindow *getMainUi();
    Ui::CustomerCacu *getCacuUi();
    Ui::CustomerProgress *getProUi();
private:
    //main window
    Ui::CustomerMainWindow *ui;
    Customer *user;
    QVBoxLayout *dishListLayout;
    vector<QHBoxLayout*> HBox;
    vector<QLabel*> dishName;
    vector<QLabel*> dishPrice;
    vector<QPushButton*> viewComment;
    vector<QPushButton*> addShoppingBox;
    QSignalMapper *dishAddMap;
    //pay window
    Ui::CustomerCacu *cacuUi;
    QVBoxLayout * notPayDishLayout;
    vector<QHBoxLayout*> notPayHBox;
    vector<QLabel*> notPayDishName;
    vector<QLabel*> notPaydishPrice;
    vector<QPushButton*> notPayDeleteButton;
    QSignalMapper *notPayDishAddMap;
    //progress window
    Ui::CustomerProgress *proUi;
    QVBoxLayout *proDishLayout;
    vector<QHBoxLayout*> proHBox;
    vector<QLabel*> proName;
    vector<QLabel*> proStatus;
signals:

public slots:
    void Init(QJsonObject *User);
    void showmainwindow();
    void showCustomerCacu();
    void showProgress();
    void AddInShoppingBox(int num);
    void deleteShoppingBox(int num);
    void isPay();
    void Pay();
    void SendMsg();
};

#endif // CUSTOMERMAINWINDOW_H
