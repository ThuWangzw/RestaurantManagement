#ifndef ADMINMAINWINDOW_H
#define ADMINMAINWINDOW_H

#include <QMainWindow>
#include "ui_adminmainwindow.h"
#include "abstractshow.h"
#include "admin.h"
#include "ui_adminuserctrl.h"
namespace Ui {
class AdminMainWindow;
}

class AdminMainWindow : public AbstractShow
{
    Q_OBJECT

public:
    AdminMainWindow(QMainWindow *mainWindow);
    ~AdminMainWindow();
    Ui::AdminMainWindow *getmainUi();
    Ui::AdminUserCtrl *getUserUi();
    void clearvector();
private:
    Dish *searchResult;
    Admin *admin;
    User *usersearchResult;
    //dish window
    Ui::AdminMainWindow *ui;
    QSignalMapper *dishchangeMap;
    QSignalMapper *dishdeleteMap;
    QVBoxLayout *dishLayout;
    vector<QHBoxLayout*> DishList;
    vector<QLineEdit*> dishnameLine;
    vector<QLineEdit*> dishpriceLine;
    vector<QPushButton*> dishdeleteButton;
    vector<QPushButton*> dishchangeButton;
    //ctrl window
    QSignalMapper *userdeleteMap;
    Ui::AdminUserCtrl *ctrlUi;
    QVBoxLayout *adminctrlLayout;
    vector<QHBoxLayout*> oneUser;
    vector<QLineEdit*> nameLine;
    vector<QLineEdit*> passwordLine;
    vector<QLineEdit*> typeLine;
    vector<QPushButton*> deleteButton;
public slots:
    //dish
    void Init(QJsonObject* t_user);
    void ShowMain();
    void changeDish(int i);
    void isdeleteDish(int i);
    void deleteDish(int i);
    void addDish();
    //ctrl
    void showUser();
    void addUser();
    void isdeleteUser(int i);
    void deleteUser(int i);
    void SearchDish();
    void SearchUser();
};

#endif // ADMINMAINWINDOW_H
