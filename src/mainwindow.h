#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

#include "abstractshow.h"
#include "registerwindow.h"
#include "customermainwindow.h"
#include "adminmainwindow.h"
#include "cookmainwindow.h"
#include "waitermainwindow.h"
#include "managermainwindow.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *getUi();

private:
    Ui::MainWindow *ui;
    RegisterWindow *registerwindow;
    CustomerMainWindow *customerMainWindow;
    AdminMainWindow *adminmainwindow;
    CookMainWindow *cookmainwindow;
    WaiterMainWindow *waitermainwindow;
    ManagerMainWindow *managermainwindow;
public slots:
    void showwindow();
    void buttonConnect(int Type);
    void LogInCheck();
signals:
    void Reconnect(int type);
    void LogInSuccess(QJsonObject *user);
};
#endif // MAINWINDOW_H
