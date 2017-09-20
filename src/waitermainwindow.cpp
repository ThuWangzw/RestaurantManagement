#include "waitermainwindow.h"

#include <QDebug>

WaiterMainWindow::WaiterMainWindow(QMainWindow *mainWindow)
{
    ui = new Ui::WaiterMainWindow;
    mainwindow = mainWindow;
    showmsg = false;
}

Ui::WaiterMainWindow *WaiterMainWindow::getUi()
{
    return ui;
}

WaiterMainWindow::~WaiterMainWindow()
{
    delete ui;
}

void WaiterMainWindow::show(int i)
{
    clear();
    ui->setupUi(mainwindow);
    if(i==9)
    {
        ui->MessageButton->setText("Task");
        vlist = new QVBoxLayout;
        ui->scrollAreaWidgetContents->setLayout(vlist);
        int j = 0;
        for(vector<QString>::iterator iter = waiter.getMsg().begin(); iter != waiter.getMsg().end();iter++,j++)
        {
            QHBoxLayout *mhbox = new QHBoxLayout;
            hbox.push_back(mhbox);
            vlist->addLayout(mhbox);

            QLabel *msglabel = new QLabel(*iter);
            QString sendname = waiter.getSender()[j];
            QLabel *senderlabel = new QLabel(sendname);

            mhbox->addWidget(msglabel);
            mhbox->addWidget(senderlabel);

            msgbox.push_back(msglabel);
            userbox.push_back(senderlabel);
        }
    }
    else
    {
        ui->MessageButton->setText("Message");
        for(int i = 0; i < 8;i++)
        {
            ui->comboBox->addItem(QString::number(i),i);
        }
        ui->comboBox->setCurrentIndex(i);
        map = new QSignalMapper;
        vlist = new QVBoxLayout;
        ui->scrollAreaWidgetContents->setLayout(vlist);
        int j = 0;
        for(QJsonArray::iterator iter = allUser->begin();iter != allUser->end(); iter++)
        {
            User* now = loadUser((*iter).toString());
            if(now->getType()!=CUSTOMER) continue;
            //open
            QString mstr(now->getName());
            mstr.append(".json");
            QFile userfile(mstr);
            userfile.open(QIODevice::ReadOnly);
            QByteArray mbyte = userfile.readAll();
            QJsonDocument mdoc = QJsonDocument::fromJson(mbyte);
            QJsonObject *userobj = new QJsonObject;
            userobj = &mdoc.object();
            Customer user;
            user.updateUser(userobj);
            if(user.getTable()!=i) continue;
            //show
            for(vector<QString>::iterator iter = user.getDishesHaveDone().begin();iter != user.getDishesHaveDone().end();iter++)
            {
                QHBoxLayout *mhbox = new QHBoxLayout;
                hbox.push_back(mhbox);
                vlist->addLayout(mhbox);

                QLabel *mdish = new QLabel(*iter);
                QLabel *muser = new QLabel(user.getName());
                QPushButton *waiting = new QPushButton("GO!");

                dishname.push_back(mdish);
                username.push_back(muser);
                waiterbutton.push_back(waiting);

                mhbox->addWidget(mdish);
                mhbox->addWidget(muser);
                mhbox->addWidget(waiting);
                connect(waiting,SIGNAL(clicked(bool)),map,SLOT(map()));
                map->setMapping(waiting,j++);
            }
        }
        connect(map,SIGNAL(mapped(int)),this,SLOT(waitdish(int)));
    }
    REconnect(WAITERMAIN);
}

void WaiterMainWindow::waittable()
{
    int n = ui->comboBox->currentIndex();
    waiter.setChaegeTable(n);
    waiter.savedata();
    //change the customer data
    for(QJsonArray::iterator iter = allUser->begin();iter != allUser->end(); iter++)
    {
        User *nowuser = loadUser((*iter).toString());
        if(nowuser->getType()!=CUSTOMER) continue;
        QString mstr(nowuser->getName());
        mstr.append(".json");
        QFile userfile(mstr);
        userfile.open(QIODevice::ReadOnly);
        QByteArray mbyte = userfile.readAll();
        QJsonDocument mdoc = QJsonDocument::fromJson(mbyte);
        QJsonObject *userobj = new QJsonObject;
        userobj = &mdoc.object();
        Customer user;
        user.updateUser(userobj);
        //delete the waiter
        for(vector<QString>::iterator iter = user.getWaiter().begin();iter!=user.getWaiter().end();iter++)
        {
            QString now = *iter;
            if(now==waiter.getName())
            {
                user.getWaiter().erase(iter);
                user.saveData();
                break;
            }
        }
        if(user.getTable()==waiter.getChargeTable())
        {
            user.addWaiter(waiter.getName());
            user.saveData();
        }
    }
    show(n);
}

void WaiterMainWindow::Init(QJsonObject *user)
{
    if(user->value("type")!=WAITER) return;
    waiter.updateUser(user);
    show(waiter.getChargeTable());
}

void WaiterMainWindow::clear()
{
    vector<QHBoxLayout*> boxtemp;

    hbox.clear();
    hbox.swap(boxtemp);

    vector<QLabel*> dishtemp;
    dishname.clear();
    dishname.swap(dishtemp);
    username.clear();
    username.swap(dishtemp);
    msgbox.clear();
    msgbox.swap(dishtemp);
    userbox.clear();
    userbox.swap(dishtemp);
    vector<QPushButton*> buttontemp;
    buttontemp.clear();
    buttontemp.swap(buttontemp);
}

void WaiterMainWindow::waitdish(int i)
{
    vector<QLabel*>::iterator dishiter = dishname.begin();
    for(int j = 0; j < i;j++, dishiter++);
    QLabel* nowdish = *dishiter;
    QString mdish = nowdish->text();
    dishname.erase(dishiter);

    vector<QLabel*>::iterator nameiter = username.begin();
    for(int j = 0; j < i;j++, nameiter++);
    QLabel *nowuser = *nameiter;
    QString muser = nowuser->text();
    username.erase(nameiter);

    //delete
    vector<QHBoxLayout*>::iterator outiter = hbox.begin();
    for(int j = 0; j < i; j++, outiter++);
    hbox.erase(outiter);

    vector<QPushButton*>::iterator buttoniter = waiterbutton.begin();
    for(int j = 0; j < i; j++, buttoniter++);
    waiterbutton.erase(buttoniter);
    //open
    QString mstr(muser);
    mstr.append(".json");
    QFile userfile(mstr);
    userfile.open(QIODevice::ReadOnly);
    QByteArray mbyte = userfile.readAll();
    QJsonDocument mdoc = QJsonDocument::fromJson(mbyte);
    QJsonObject *userobj = new QJsonObject;
    userobj = &mdoc.object();
    Customer user;
    user.updateUser(userobj);
    //find the dish
    vector<QString>::iterator iter = user.getDishesHaveDone().begin();
    for(;iter != user.getDishesHaveDone().end(); iter++)
    {
        QString now = *iter;
        if(now == mdish) break;
    }
    //change
    waiter.waitnumadd();
    user.addDishesEating(*iter);
    user.getDishesHaveDone().erase(iter);
    user.saveData();
    //show
    show(waiter.getChargeTable());
}

void WaiterMainWindow::dishtomsg()
{
    if(showmsg)
    {
        showmsg = false;
        show(waiter.getChargeTable());
    }
    else
    {
        showmsg = true;
        show(9);
    }
}
