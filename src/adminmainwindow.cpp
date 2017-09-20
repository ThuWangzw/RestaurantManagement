#include "adminmainwindow.h"
#include <QDebug>

AdminMainWindow::AdminMainWindow(QMainWindow *mainWindow)
{
    ui = new Ui::AdminMainWindow;
    ctrlUi = new Ui::AdminUserCtrl;
    mainwindow = mainWindow;
    admin = new Admin;
    searchResult = NULL;
    usersearchResult = NULL;
}

AdminMainWindow::~AdminMainWindow()
{
    delete ui;
    delete admin;
}

void AdminMainWindow::showUser()
{
    ctrlUi->setupUi(mainwindow);
    clearvector();
    //
    userdeleteMap = new QSignalMapper;
    adminctrlLayout = new QVBoxLayout;
    ctrlUi->scrollAreaWidgetContents->setLayout(adminctrlLayout);
    int i = 0;

    QJsonArray *showarray;
    if(usersearchResult==NULL)
    {
        showarray = allUser;
    }
    else
    {
        showarray = new QJsonArray;
        showarray->push_back(usersearchResult->getName());
    }
    for(QJsonArray::iterator iter = showarray->begin();iter != showarray->end(); iter++)
    {
        User *m_user = loadUser((*iter).toString());

        QHBoxLayout *m_hBox = new QHBoxLayout;
        oneUser.push_back(m_hBox);
        adminctrlLayout->addLayout(m_hBox);

        QLineEdit *name = new QLineEdit(m_user->getName());
        name->setReadOnly(true);
        QLineEdit *password = new QLineEdit(m_user->getPassword());
        password->setReadOnly(true);
        QLineEdit *type;
        switch (m_user->getType())
        {
        case CUSTOMER:
            type = new QLineEdit("Customer");
            break;
        case ADMIN:
            type = new QLineEdit("Admin");
            break;
        case COOK:
            type = new QLineEdit("Cook");
            break;
        case WAITER:
            type = new QLineEdit("Waiter");
            break;
        case MANAGER:
            type = new QLineEdit("Manager");
            break;
        default:
            break;
        }
        type->setReadOnly(true);
        QPushButton *m_delete = new QPushButton("Delete");

        nameLine.push_back(name);
        passwordLine.push_back(password);
        typeLine.push_back(type);
        deleteButton.push_back(m_delete);

        m_hBox->addWidget(name);
        m_hBox->addWidget(password);
        m_hBox->addWidget(type);
        m_hBox->addWidget(m_delete);

        disconnect(m_delete,SIGNAL(clicked(bool)),userdeleteMap,SLOT(map()));
        connect(m_delete,SIGNAL(clicked(bool)),userdeleteMap,SLOT(map()));
        userdeleteMap->setMapping(m_delete,i++);
    }
    disconnect(userdeleteMap,SIGNAL(mapped(int)),this,SLOT(isdeleteUser(int)));
    connect(userdeleteMap,SIGNAL(mapped(int)),this,SLOT(isdeleteUser(int)));
    emit REconnect(ADMINCTRL);
}

void AdminMainWindow::ShowMain()
{
    clearvector();
    ui->setupUi(mainwindow);

    dishchangeMap = new QSignalMapper;
    dishdeleteMap = new QSignalMapper;
    dishLayout = new QVBoxLayout;
    ui->scrollAreaWidgetContents->setLayout(dishLayout);
    int i = 0;
    int j = 0;
    vector<Dish*> showDish;
    if(searchResult==NULL)
    {
        showDish = allDish;
    }
    else
    {
        showDish.push_back(searchResult);
    }
    for(vector<Dish*>::iterator iter = showDish.begin();iter != showDish.end(); iter++)
    {
        Dish* now = *iter;
        QHBoxLayout *m_hBox = new QHBoxLayout;
        DishList.push_back(m_hBox);
        dishLayout->addLayout(m_hBox);

        QLineEdit *name = new QLineEdit(now->getName());
        name->setReadOnly(true);
        QLineEdit *price = new QLineEdit(QString::number(now->getPrice()));
        price->setReadOnly(true);
        /*QLineEdit *type;
        switch (m_user->getType())
        {
        case CUSTOMER:
            type = new QLineEdit("Customer");
            break;
        case ADMIN:
            type = new QLineEdit("Admin");
            break;
        case COOK:
            type = new QLineEdit("Cook");
            break;
        case WAITER:
            type = new QLineEdit("Waiter");
            break;
        case MANAGER:
            type = new QLineEdit("Manager");
            break;
        default:
            break;
        }*/
        QPushButton *m_delete = new QPushButton("Delete");
        QPushButton *m_change = new QPushButton("Change");

        dishnameLine.push_back(name);
        dishpriceLine.push_back(price);
        //typeLine.push_back(type);
        deleteButton.push_back(m_delete);

        m_hBox->addWidget(name);
        m_hBox->addWidget(price);
        //m_hBox->addWidget(type);
        m_hBox->addWidget(m_delete);
        m_hBox->addWidget(m_change);

        disconnect(m_delete,SIGNAL(clicked(bool)),dishdeleteMap,SLOT(map()));
        connect(m_delete,SIGNAL(clicked(bool)),dishdeleteMap,SLOT(map()));
        dishdeleteMap->setMapping(m_delete,i++);

        disconnect(m_change,SIGNAL(clicked(bool)),dishchangeMap,SLOT(map()));
        connect(m_change,SIGNAL(clicked(bool)),dishchangeMap,SLOT(map()));
        dishchangeMap->setMapping(m_change,j++);
    }
    disconnect(dishdeleteMap,SIGNAL(mapped(int)),this,SLOT(isdeleteDish(int)));
    disconnect(dishchangeMap,SIGNAL(mapped(int)),this,SLOT(changeDish(int)));
    connect(dishdeleteMap,SIGNAL(mapped(int)),this,SLOT(isdeleteDish(int)));
    connect(dishchangeMap,SIGNAL(mapped(int)),this,SLOT(changeDish(int)));
    emit REconnect(ADMINMAIN);
}

void AdminMainWindow::isdeleteUser(int i)
{
    QMessageBox *m_msgBox = new QMessageBox;
    m_msgBox->setInformativeText("Sure to delete?");
    m_msgBox->setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    QSignalMapper *map = new QSignalMapper;
    disconnect(m_msgBox->button(QMessageBox::Yes),SIGNAL(clicked(bool)),map,SLOT(map()));
    connect(m_msgBox->button(QMessageBox::Yes),SIGNAL(clicked(bool)),map,SLOT(map()));
    map->setMapping(m_msgBox->button(QMessageBox::Yes),i);
    disconnect(map,SIGNAL(mapped(int)),this,SLOT(deleteUser(int)));
    connect(map,SIGNAL(mapped(int)),this,SLOT(deleteUser(int)));

    disconnect(m_msgBox->button(QMessageBox::No),SIGNAL(clicked(bool)),m_msgBox,SLOT(close()));
    connect(m_msgBox->button(QMessageBox::No),SIGNAL(clicked(bool)),m_msgBox,SLOT(close()));
    m_msgBox->show();
}

void AdminMainWindow::deleteUser(int i)
{
    QJsonArray::iterator iter = allUser->begin();
    for(int j = 0; j < i; j++,iter++);
    QString name((*iter).toString());
    if(name==admin->getName())
    {
        ShowMessage("You can't do this!");
        return;
    }
    name.append(".json");
    allUser->erase(iter);
    //delete all
    QJsonArray all;
    for(int i = 0; i<allUser->size();i++) all.push_back(allUser->at(i));
    QJsonDocument userDoc;
    userDoc.setArray(all);
    QFile deleteFile("AllUser.json");
    deleteFile.remove();
    QFile userFile("AllUser.json");
    userFile.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream userStream(&userFile);
    userStream<<userDoc.toJson();
    userFile.close();
    //delete user
    QFile deleteusefile(name);
    deleteusefile.remove();
    //repaint
    showUser();
}

void AdminMainWindow::Init(QJsonObject* t_user)
{
    if(t_user->value("type").toInt()!=ADMIN) return;
    admin->updateUser(t_user);
    ShowMain();
}

Ui::AdminMainWindow *AdminMainWindow::getmainUi()
{
    return ui;
}

Ui::AdminUserCtrl *AdminMainWindow::getUserUi()
{
    return ctrlUi;
}

void AdminMainWindow::addDish()
{
    //check
    //null
    if(ui->NameLine->text().isEmpty()||ui->PriceLine->text().isEmpty())
    {
        ShowMessage("Error!");
        return;
    }
    //same
    QString name = ui->NameLine->text();
    name.append(".json");
    if(QFile::exists(name)==true)
    {
        ShowMessage("Have exsited!");
        return;
    }

    //add
    Dish *newdish = new Dish;
    newdish->setName(ui->NameLine->text());
    newdish->setPrice(ui->PriceLine->text().toInt());
    allDish.push_back(newdish);
    newdish->saveDish();
    //save local main
    QFile deleteFile("AllDishes.json");
    deleteFile.remove();
    QJsonArray all;
    for(vector<Dish*>::iterator iter = allDish.begin();iter != allDish.end();iter++)
    {
        Dish *now = *iter;
        all.push_back(now->getName());
    }
    QJsonDocument userDoc;
    userDoc.setArray(all);

    QFile userFile("AllDishes.json");
    if(!userFile.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        ShowMessage("Load json error!");
        return;
    }

    QTextStream userStream(&userFile);
    userStream<<userDoc.toJson();
    userFile.close();
    //clear
    ui->NameLine->clear();
    ui->PriceLine->clear();
    //repaint
    ShowMain();
}

void AdminMainWindow::changeDish(int i)
{
    //TODO
}

void AdminMainWindow::isdeleteDish(int i)
{
    QMessageBox *m_msgBox = new QMessageBox;
    m_msgBox->setInformativeText("Sure to delete?");
    m_msgBox->setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    QSignalMapper *map = new QSignalMapper;
    disconnect(m_msgBox->button(QMessageBox::Yes),SIGNAL(clicked(bool)),map,SLOT(map()));
    connect(m_msgBox->button(QMessageBox::Yes),SIGNAL(clicked(bool)),map,SLOT(map()));
    map->setMapping(m_msgBox->button(QMessageBox::Yes),i);
    disconnect(map,SIGNAL(mapped(int)),this,SLOT(deleteDish(int)));
    connect(map,SIGNAL(mapped(int)),this,SLOT(deleteDish(int)));

    disconnect(m_msgBox->button(QMessageBox::No),SIGNAL(clicked(bool)),m_msgBox,SLOT(close()));
    connect(m_msgBox->button(QMessageBox::No),SIGNAL(clicked(bool)),m_msgBox,SLOT(close()));
    m_msgBox->show();
}

void AdminMainWindow::deleteDish(int i)
{
    vector<Dish*>::iterator iter = allDish.begin();
    for(int j = 0; j < i; j++, iter++);
    Dish* now = *iter;
    QString deletefilename(now->getName());
    deletefilename.append(".json");
    QFile defi(deletefilename);
    defi.remove();
    allDish.erase(iter);



    QFile deleteFile("AllDishes.json");
    deleteFile.remove();
    QJsonArray all;
    for(vector<Dish*>::iterator iter = allDish.begin();iter != allDish.end();iter++)
    {
        Dish *now = *iter;
        all.push_back(now->getName());
    }
    QJsonDocument userDoc;
    userDoc.setArray(all);

    QFile userFile("AllDishes.json");
    if(!userFile.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        ShowMessage("Load json error!");
        return;
    }

    QTextStream userStream(&userFile);
    userStream<<userDoc.toJson();
    userFile.close();
    ShowMain();
}

void AdminMainWindow::addUser()
{
    //check
    //null
    if(ctrlUi->NameLine->text().isEmpty()||ctrlUi->PasswordLine->text().isEmpty()||ctrlUi->TypeLine->text().isEmpty())
    {
        ShowMessage("Error!");
        return;
    }
    //same
    QString name = ctrlUi->NameLine->text();
    name.append(".json");
    if(QFile::exists(name)==true)
    {
        ShowMessage("Have exsited!");
        return;
    }
    //error
    QString mtype = ctrlUi->TypeLine->text();
    if(!((mtype == "Customer")||(mtype == "Admin")||(mtype == "Cook")||(mtype == "Waiter")||(mtype == "Manager")))
    {
        ShowMessage("error");
        return;
    }
    //add
    User *newdish = new User;
    newdish->setName(ctrlUi->NameLine->text());
    newdish->setPassword(ctrlUi->PasswordLine->text());
    if(mtype=="Customer")
        newdish->setType(CUSTOMER);
    if(mtype=="Admin")
        newdish->setType(ADMIN);
    if(mtype=="Cook")
        newdish->setType(COOK);
    if(mtype=="Waiter")
        newdish->setType(WAITER);
    if(mtype=="Manager")
        newdish->setType(MANAGER);
    addUserToLocal(newdish->getName());
    NewUserLoadInJson(newdish->getName(),newdish->getPassword(),newdish->getType());
    //clear
    ctrlUi->NameLine->clear();
    ctrlUi->PasswordLine->clear();
    ctrlUi->TypeLine->clear();
    //repaint
    showUser();
}

void AdminMainWindow::SearchDish()
{
    searchResult = NULL;
    for(int i = 0;i<allDish.size();i++)
    {
        if(allDish[i]->getName()==ui->SearchLine->text())
        {
            searchResult = new Dish;
            searchResult->setName(allDish[i]->getName());
            searchResult->setPrice(allDish[i]->getPrice());
            ShowMain();
            return;
        }
    }
    ShowMessage("404 not found~");
    ShowMain();
}

void AdminMainWindow::clearvector()
{
    vector<QHBoxLayout*> outtemp;
    DishList.clear();
    DishList.swap(outtemp);
    oneUser.clear();
    oneUser.swap(outtemp);

    vector<QLineEdit*> labeltemp;
    dishnameLine.clear();
    dishnameLine.swap(labeltemp);
    dishpriceLine.clear();
    dishpriceLine.swap(labeltemp);
    nameLine.clear();
    nameLine.swap(labeltemp);
    passwordLine.clear();
    passwordLine.swap(labeltemp);
    typeLine.clear();
    typeLine.swap(labeltemp);

    vector<QPushButton*> buttontemp;
    dishchangeButton.clear();
    dishchangeButton.swap(buttontemp);
    dishdeleteButton.clear();
    dishdeleteButton.swap(buttontemp);
    deleteButton.clear();
    deleteButton.swap(buttontemp);

}

void AdminMainWindow::SearchUser()
{
    usersearchResult = NULL;
    for(QJsonArray::iterator iter = allUser->begin();iter!=allUser->end();iter++)
    {
        QString name = (*iter).toString();
        if(ctrlUi->SearchLine->text()==name)
        {
            usersearchResult = loadUser(name);
            showUser();
            return;
        }
    }
    ShowMessage("404 not found~");
    showUser();
}
