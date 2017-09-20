#ifndef WAITERMAINWINDOW_H
#define WAITERMAINWINDOW_H

#include <QMainWindow>
#include "ui_waitermainwindow.h"
#include "abstractshow.h"
#include "waiter.h"
#include "customer.h"
namespace Ui {
class WaiterMainWindow;
}

class WaiterMainWindow : public AbstractShow
{
    Q_OBJECT

public:
    WaiterMainWindow(QMainWindow *mainWindow);
    ~WaiterMainWindow();
    Ui::WaiterMainWindow *getUi();
    void clear();
private:
    bool showmsg;
    Ui::WaiterMainWindow *ui;
    Waiter waiter;
    QSignalMapper *map;
    QVBoxLayout *vlist;
    vector<QHBoxLayout*> hbox;
    vector<QLabel*> dishname;
    vector<QLabel*> username;
    vector<QPushButton*> waiterbutton;

    vector<QLabel*> msgbox;
    vector<QLabel*> userbox;
public slots:
    void show(int i);
    void waitdish(int i);
    void waittable();
    void Init(QJsonObject *user);
    void dishtomsg();
};

#endif // WAITERMAINWINDOW_H
