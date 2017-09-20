#include "mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    registerwindow = new RegisterWindow(this);
    customerMainWindow = new CustomerMainWindow(this);
    adminmainwindow = new AdminMainWindow(this);
    cookmainwindow = new CookMainWindow(this);
    waitermainwindow = new WaiterMainWindow(this);
    managermainwindow = new ManagerMainWindow(this);
    //load all user
    QFile allfile("AllUser.json");
    allfile.open(QIODevice::ReadOnly);
    QByteArray allbyte = allfile.readAll();
    allfile.close();
    QJsonDocument alldoc = QJsonDocument::fromJson(allbyte);
    *(AbstractShow::allUser) = alldoc.array();

    //load all dish
    QFile alldishfile("AllDishes.json");
    alldishfile.open(QIODevice::ReadOnly);
    QByteArray alldishbyte = alldishfile.readAll();
    alldishfile.close();
    QJsonDocument alldishdoc = QJsonDocument::fromJson(alldishbyte);
    QJsonArray alldishArray = alldishdoc.array();
    for(QJsonArray::iterator iter = alldishArray.begin();iter!=alldishArray.end();iter++)
    {
        QString name((*iter).toString());
        name.append(".json");
        QFile dishfile(name);
        dishfile.open(QIODevice::ReadOnly);
        QByteArray dishbyte = dishfile.readAll();
        dishfile.close();
        QJsonDocument dishdoc = QJsonDocument::fromJson(dishbyte);
        QJsonObject dishobj = dishdoc.object();
        Dish *m_dish = new Dish(&dishobj);
        AbstractShow::allDish.push_back(m_dish);
    }
    //connect
    connect(this,SIGNAL(Reconnect(int)),this,SLOT(buttonConnect(int)));
    connect(registerwindow,SIGNAL(REconnect(int)),this,SLOT(buttonConnect(int)));
    connect(customerMainWindow,SIGNAL(REconnect(int)),this,SLOT(buttonConnect(int)));
    connect(adminmainwindow,SIGNAL(REconnect(int)),this,SLOT(buttonConnect(int)));
    connect(cookmainwindow,SIGNAL(REconnect(int)),this,SLOT(buttonConnect(int)));
    connect(waitermainwindow,SIGNAL(REconnect(int)),this,SLOT(buttonConnect(int)));
    connect(managermainwindow,SIGNAL(REconnect(int)),this,SLOT(buttonConnect(int)));

    connect(ui->LogInButton,SIGNAL(clicked(bool)),this,SLOT(LogInCheck()));
    connect(this,SIGNAL(LogInSuccess(QJsonObject*)),customerMainWindow,SLOT(Init(QJsonObject*)));
    connect(this,SIGNAL(LogInSuccess(QJsonObject*)),adminmainwindow,SLOT(Init(QJsonObject*)));
    connect(this,SIGNAL(LogInSuccess(QJsonObject*)),cookmainwindow,SLOT(Init(QJsonObject*)));
    connect(this,SIGNAL(LogInSuccess(QJsonObject*)),waitermainwindow,SLOT(Init(QJsonObject*)));
    connect(this,SIGNAL(LogInSuccess(QJsonObject*)),managermainwindow,SLOT(Init(QJsonObject*)));
    buttonConnect(MAIN);
}

MainWindow::~MainWindow()
{
    delete  ui;
    delete registerwindow;
}

Ui::MainWindow *MainWindow::getUi()
{
    return ui;
}

void MainWindow::showwindow()
{
    ui->setupUi(this);
    //connect
    disconnect(ui->LogInButton,SIGNAL(clicked(bool)),this,SLOT(LogInCheck()));
    connect(ui->LogInButton,SIGNAL(clicked(bool)),this,SLOT(LogInCheck()));
    emit Reconnect(MAIN);
}

void MainWindow::buttonConnect(int Type)
{
    switch (Type)
    {
    case MAIN:
        connect(this->getUi()->RegisterButton,SIGNAL(clicked(bool)),registerwindow,SLOT(show()));
        break;
    case REGISTER:
        connect(registerwindow->getUi()->BackButton,SIGNAL(clicked(bool)),this,SLOT(showwindow()));
        connect(registerwindow,SIGNAL(CreateUserSuccess()),this,SLOT(showwindow()));
        break;
    case CUSTOMERMAIN:
        connect(customerMainWindow->getMainUi()->BackButton,SIGNAL(clicked(bool)),this,SLOT(showwindow()));
        connect(customerMainWindow->getMainUi()->ShoppingBoxButton,SIGNAL(clicked(bool)),customerMainWindow,SLOT(showCustomerCacu()));
        break;
    case CUSTOMERCACU:
        connect(customerMainWindow->getCacuUi()->BackButton,SIGNAL(clicked(bool)),customerMainWindow,SLOT(showmainwindow()));
        connect(customerMainWindow->getCacuUi()->PayButton,SIGNAL(clicked(bool)),customerMainWindow,SLOT(isPay()));
        break;
    case CUSTOMERPRO:
        connect(customerMainWindow->getProUi()->BackButton,SIGNAL(clicked(bool)),customerMainWindow,SLOT(showmainwindow()));
        connect(customerMainWindow->getProUi()->SendButton,SIGNAL(clicked(bool)),customerMainWindow,SLOT(SendMsg()));
        break;
    case ADMINMAIN:
        connect(adminmainwindow->getmainUi()->BackButton,SIGNAL(clicked(bool)),this,SLOT(showwindow()));
        connect(adminmainwindow->getmainUi()->UserContrlButton,SIGNAL(clicked(bool)),adminmainwindow,SLOT(showUser()));
        connect(adminmainwindow->getmainUi()->AddButton,SIGNAL(clicked(bool)),adminmainwindow,SLOT(addDish()));
        connect(adminmainwindow->getmainUi()->SearchButton,SIGNAL(clicked(bool)),adminmainwindow,SLOT(SearchDish()));
        break;
    case ADMINCTRL:
        connect(adminmainwindow->getUserUi()->BackButton,SIGNAL(clicked(bool)),adminmainwindow,SLOT(ShowMain()));
        connect(adminmainwindow->getUserUi()->AddButton,SIGNAL(clicked(bool)),adminmainwindow,SLOT(addUser()));
        connect(adminmainwindow->getUserUi()->SearchButton,SIGNAL(clicked(bool)),adminmainwindow,SLOT(SearchUser()));
        break;
    case COOKMAIN:
        connect(cookmainwindow->getUi()->BackButton,SIGNAL(clicked(bool)),this,SLOT(showwindow()));
        connect(cookmainwindow->getUi()->CookButton,SIGNAL(clicked(bool)),cookmainwindow,SLOT(cooking()));
        break;
    case WAITERMAIN:
        connect(waitermainwindow->getUi()->BackButton,SIGNAL(clicked(bool)),this,SLOT(showwindow()));
        connect(waitermainwindow->getUi()->OKButton,SIGNAL(clicked(bool)),waitermainwindow,SLOT(waittable()));
        connect(waitermainwindow->getUi()->MessageButton,SIGNAL(clicked(bool)),waitermainwindow,SLOT(dishtomsg()));
        break;
    case MANAGERMAIN:
        connect(managermainwindow->getUi()->BackButton,SIGNAL(clicked(bool)),this,SLOT(showwindow()));
        break;
    default:
        break;
    }
}

void MainWindow::LogInCheck()
{
    QString name = ui->UserNameInput->text();
    QString password = ui->PasswordInput->text();
    //check the password
    bool flag = false;
    for(QJsonArray::iterator iter = AbstractShow::allUser->begin();iter != AbstractShow::allUser->end();iter++)
    {
        QString nowName = (*iter).toString();
        //if have
        if(nowName==name)flag = true;
    }
    if(!flag)
    {
        AbstractShow::ShowMessage("Don't have this user!");
        return;
    }
    QString namestr;
    namestr.append(name);
    namestr.append(".json");
    QFile userFile(namestr);
    userFile.open(QIODevice::ReadOnly);
    QByteArray userByte = userFile.readAll();
    QJsonDocument userJson = QJsonDocument::fromJson(userByte);
    QJsonObject *userObj = new QJsonObject(userJson.object());
    if(userObj->value("password").toString()!=password)
    {
        AbstractShow::ShowMessage("Password error!");
        delete userObj;
        return;
    }
    AbstractShow::ShowMessage("Log in successfully!");
    emit LogInSuccess(userObj);
}
