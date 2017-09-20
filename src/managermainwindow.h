#ifndef MANAGERMAINWINDOW_H
#define MANAGERMAINWINDOW_H
#include "ui_managermainwindow.h"
#include <QMainWindow>
#include "abstractshow.h"
#include "cook.h"
#include "waiter.h"
#include "manager.h"
namespace Ui {
class ManagerMainWindow;
}

class ManagerMainWindow : public AbstractShow
{
    Q_OBJECT

public:
    ManagerMainWindow(QMainWindow *mainWindow);
    ~ManagerMainWindow();
    void clear();
    Ui::ManagerMainWindow *getUi();
private:
    Ui::ManagerMainWindow *ui;
    vector<QLabel*> alllabel;
    QVBoxLayout *vbox;
    vector<QHBoxLayout*> hbox;
    Manager manager;
public slots:
    void show();
    void Init(QJsonObject *user);
};

#endif // MANAGERMAINWINDOW_H
