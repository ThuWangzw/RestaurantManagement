#include "managermainwindow.h"
#include <QDebug>

ManagerMainWindow::ManagerMainWindow(QMainWindow *mainWindow)
{
    mainwindow = mainWindow;
    ui = new Ui::ManagerMainWindow;
}

ManagerMainWindow::~ManagerMainWindow()
{
    delete ui;
}

Ui::ManagerMainWindow *ManagerMainWindow::getUi()
{
    return ui;
}

void ManagerMainWindow::clear()
{
    vector<QLabel*> labeltemp;
    alllabel.clear();
    alllabel.swap(labeltemp);

    vector<QHBoxLayout*> boxtemp;
    boxtemp.clear();
    boxtemp.swap(boxtemp);
}

void ManagerMainWindow::show()
{
    clear();
    ui->setupUi(mainwindow);

    vbox = new QVBoxLayout;
    ui->scrollAreaWidgetContents->setLayout(vbox);

    QHBoxLayout *m_hbox = new QHBoxLayout;
    vbox->addLayout(m_hbox);
    hbox.push_back(m_hbox);
    QLabel *cook_label = new QLabel("cook data:");
    m_hbox->addWidget(cook_label);
    alllabel.push_back(cook_label);

    for(QJsonArray::iterator iter = allUser->begin();iter != allUser->end(); iter++)
    {
        User *now = loadUser((*iter).toString());
        if(now->getType()!=COOK) continue;
        QString mstr(now->getName());
        mstr.append(".json");
        QFile userfile(mstr);
        userfile.open(QIODevice::ReadOnly);
        QByteArray mbyte = userfile.readAll();
        QJsonDocument mdoc = QJsonDocument::fromJson(mbyte);
        QJsonObject *userobj = new QJsonObject;
        userobj = &mdoc.object();
        Cook user;
        user.updateUser(userobj);
        QHBoxLayout *mhbox = new QHBoxLayout;
        hbox.push_back(mhbox);
        vbox->addLayout(mhbox);

        QLabel *cookname = new QLabel(user.getName());
        QLabel *cooknumlabel = new QLabel(QString::number(user.getCookNum()));

        alllabel.push_back(cookname);
        alllabel.push_back(cooknumlabel);

        mhbox->addWidget(cookname);
        mhbox->addWidget(cooknumlabel);
    }

    QHBoxLayout *mhbox = new QHBoxLayout;
    vbox->addLayout(mhbox);
    hbox.push_back(mhbox);
    QLabel *cooklabel = new QLabel("waiter data:");
    mhbox->addWidget(cooklabel);
    alllabel.push_back(cooklabel);

    for(QJsonArray::iterator iter = allUser->begin();iter != allUser->end(); iter++)
    {
        User *now = loadUser((*iter).toString());
        if(now->getType()!=WAITER) continue;
        QString mstr(now->getName());
        mstr.append(".json");
        QFile userfile(mstr);
        userfile.open(QIODevice::ReadOnly);
        QByteArray mbyte = userfile.readAll();
        QJsonDocument mdoc = QJsonDocument::fromJson(mbyte);
        QJsonObject *userobj = new QJsonObject;
        userobj = &mdoc.object();
        Waiter user;
        user.updateUser(userobj);

        QHBoxLayout *mhbox = new QHBoxLayout;
        hbox.push_back(mhbox);
        vbox->addLayout(mhbox);

        QLabel *waitername = new QLabel(user.getName());
        QLabel *waiternumlabel = new QLabel(QString::number(user.getWaitNum()));

        alllabel.push_back(waitername);
        alllabel.push_back(waiternumlabel);

        mhbox->addWidget(waitername);
        mhbox->addWidget(waiternumlabel);
    }
    REconnect(MANAGERMAIN);
}

void ManagerMainWindow::Init(QJsonObject *user)
{
    if(user->value("type").toInt()!=MANAGER) return;
    manager.updateUser(user);

    show();
}
