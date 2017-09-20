#include "registerwindow.h"
#include "QDebug"
RegisterWindow::RegisterWindow(QMainWindow *mainWindow)
{
    ui = new Ui::RegisterWindow;
    mainwindow = mainWindow;
    type = REGISTER;
}

void RegisterWindow::show()
{
    ui->setupUi(mainwindow);
    //connect
    disconnect(ui->OKButton,SIGNAL(clicked(bool)),this,SLOT(on_OKButton_clicked(bool)));
    connect(ui->OKButton,SIGNAL(clicked(bool)),this,SLOT(on_OKButton_clicked(bool)));
    emit REconnect(type);
}

Ui::RegisterWindow *RegisterWindow::getUi()
{
    return ui;
}

bool RegisterWindow::InputRight()
{
    QString name = ui->UserNameLine->text();
    QString password1 = ui->PasswordLine->text();
    QString password2 = ui->RePasswordLine->text();

    //check name
    if(name.size()!=11) return false;
    for(int i = 0;i<allUser->size();i++)
    {
        if(name==allUser->at(i).toString()) return false;
    }
    QByteArray nametochar = name.toLatin1();
    const char *s = nametochar.data();
    while(*s&&*s>='0'&&*s<='9') s++;
    if(*s) return false;

    //check password
    if(password1.size()<10) return false;
    if(password1!=password2) return false;
    return true;
}

void RegisterWindow::on_OKButton_clicked(bool checked)
{
    //check if the input is right
    if(!InputRight())
    {
        //message
        ShowMessage("Sorry,your input is wrong.");
        return;
    }
    //save in json
    if(NewUserLoadInJson(ui->UserNameLine->text(),ui->PasswordLine->text(),type))
    {
        //add in list
        addUserToLocal(ui->UserNameLine->text());
        //success message
        ShowMessage("Successfuly created!");
        //ok
        emit CreateUserSuccess();
    }
}

