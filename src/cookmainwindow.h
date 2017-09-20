#ifndef COOKMAINWINDOW_H
#define COOKMAINWINDOW_H

#include "abstractshow.h"
#include "ui_cookmainwindow.h"
#include "customer.h"
#include "cook.h"
namespace Ui {
class CookMainWindow;
}

class CookMainWindow : public AbstractShow
{
    Q_OBJECT

public:
    CookMainWindow(QMainWindow *mainWindow);
    ~CookMainWindow();
    void clear();
    Ui::CookMainWindow *getUi();
private:
    Ui::CookMainWindow *ui;
    QSignalMapper *map;
    QVBoxLayout *dishlist;
    vector<QLabel*> dishname;
    vector<QLabel*> username;
    vector<QHBoxLayout*> hbox;
    vector<QPushButton*> claimButton;
    Cook cook;
public slots:
    void show();
    void addcook(int i);
    void cooking();
    void Init(QJsonObject *user);
};

#endif // COOKMAINWINDOW_H
