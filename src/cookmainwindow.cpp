#include "cookmainwindow.h"
#include <QDebug>

CookMainWindow::CookMainWindow(QMainWindow *mainWindow)
{
    ui = new Ui::CookMainWindow;
    mainwindow = mainWindow;

}

CookMainWindow::~CookMainWindow()
{
    delete ui;
}

void CookMainWindow::clear()
{
    vector<QLabel*> labeltemp;
    dishname.clear();
    dishname.swap(labeltemp);
    username.clear();
    username.swap(labeltemp);

    vector<QPushButton*> buttontemp;
    buttontemp.clear();
    buttontemp.swap(buttontemp);

    vector<QHBoxLayout*> outtemp;
    outtemp.clear();
    outtemp.swap(outtemp);
}

void CookMainWindow::show()
{
    clear();
    ui->setupUi(mainwindow);

    map = new QSignalMapper;
    dishlist = new QVBoxLayout;
    ui->scrollAreaWidgetContents->setLayout(dishlist);
    int i = 0;
    for(QJsonArray::iterator iter = allUser->begin();iter!=allUser->end();iter++)
    {
        User *now = loadUser((*iter).toString());
        if(now->getType()!=CUSTOMER) continue;
        //open file
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
        //read not done
        for(vector<QString>::iterator iter = user.getDishesNotDone().begin();iter!=user.getDishesNotDone().end();iter++)
        {
            QHBoxLayout *mhbox = new QHBoxLayout;
            dishlist->addLayout(mhbox);
            hbox.push_back(mhbox);

            QLabel *mdishlabel = new QLabel(*iter);
            QLabel *muserlabel = new QLabel(user.getName());
            QPushButton *mbutton = new QPushButton("Claim");

            dishname.push_back(mdishlabel);
            username.push_back(muserlabel);
            claimButton.push_back(mbutton);

            mhbox->addWidget(mdishlabel);
            mhbox->addWidget(muserlabel);
            mhbox->addWidget(mbutton);

            //connect
            disconnect(mbutton,SIGNAL(clicked(bool)),map,SLOT(map()));
            connect(mbutton,SIGNAL(clicked(bool)),map,SLOT(map()));
            map->setMapping(mbutton,i++);
        }
    }
    connect(map,SIGNAL(mapped(int)),this,SLOT(addcook(int)));
    emit REconnect(COOKMAIN);
}

void CookMainWindow::addcook(int i)
{
    //open file
    QString mstr(username[i]->text());
    mstr.append(".json");
    QFile userfile(mstr);
    userfile.open(QIODevice::ReadOnly);
    QByteArray mbyte = userfile.readAll();
    QJsonDocument mdoc = QJsonDocument::fromJson(mbyte);
    QJsonObject *userobj = new QJsonObject;
    userobj = &mdoc.object();
    Customer user;
    user.updateUser(userobj);
    //change
    QString changestr;
    for(vector<QString>::iterator iter = user.getDishesNotDone().begin();iter!=user.getDishesNotDone().end();iter++)
    {
        changestr = *iter;
        QLabel *now= dishname[i];
        if(now->text()==changestr)
        {
            user.getDishesNotDone().erase(iter);
            break;
        }
    }
    user.addDishesDoing(changestr);
    cook.addDish(user.getName(),changestr);
    //save
    user.saveData();
    cook.saveData();
    qDebug()<<"show";
    show();
}

void CookMainWindow::cooking()
{
    //find
    int i = 0;
    for(vector<QString>::iterator iter = cook.getCookName().begin(); iter!=cook.getCookName().end();iter++,i++)
    {
        //open file
        QString mstr = *iter;
        mstr.append(".json");
        QFile userfile(mstr);
        userfile.open(QIODevice::ReadOnly);
        QByteArray mbyte = userfile.readAll();
        QJsonDocument mdoc = QJsonDocument::fromJson(mbyte);
        QJsonObject *userobj = new QJsonObject;
        userobj = &mdoc.object();
        Customer user;
        user.updateUser(userobj);
        //find cooking
        vector<QString>::iterator miter = user.getDishesDoing().begin();
        for(;miter!=user.getDishesDoing().end();miter++)
        {
            QString mnow = *miter;
            QString now = cook.getCookDish()[i];
            if(now==mnow)
            {
                break;
            }
        }
        //change
        cook.cooknumadd();
        user.addDisherHaveDone(*miter);
        user.getDishesDoing().erase(miter);
        user.saveData();
    }
    cook.clear();
    cook.saveData();
    show();
}

void CookMainWindow::Init(QJsonObject *user)
{
    if(user->value("type").toInt()!=COOK) return;
    cook.updateUser(user);
    show();
}

Ui::CookMainWindow *CookMainWindow::getUi()
{
    return ui;
}
