#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QObject>
#include "abstractshow.h"
#include "ui_registerwindow.h"
class RegisterWindow : public AbstractShow
{
    Q_OBJECT
public:
    RegisterWindow(QMainWindow *mainWindow);
    Ui::RegisterWindow *getUi();
    bool InputRight();
private:
    QMainWindow *mainwindow;
    Ui::RegisterWindow *ui;
signals:
    void reshow(int type);
    void CreateUserSuccess();
public slots:
    void show();
public slots:
    void on_OKButton_clicked(bool checked);
};

#endif // REGISTERWINDOW_H
