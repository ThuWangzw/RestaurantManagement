#include "customermainwindow.h"
#include <QDebug>
CustomerMainWindow::CustomerMainWindow(QMainWindow *mainWindow)
{
    ui = new Ui::CustomerMainWindow;
    user = new Customer;
    mainwindow = mainWindow;
    dishAddMap = new QSignalMapper;
    cacuUi = new Ui::CustomerCacu;
    proUi = new Ui::CustomerProgress;
}

void CustomerMainWindow::Init(QJsonObject *User)
{
    if(User->value("type")!=CUSTOMER) return;
    user->updateUser(User);
    showmainwindow();
}

void CustomerMainWindow::showmainwindow()
{
    ui->setupUi(mainwindow);
    //set welcome text
    QString welcome("Welcome,");
    welcome.append(user->getName());
    welcome.append("!");
    ui->label->setText(welcome);
   //add dish
    dishListLayout = new QVBoxLayout;
    ui->DishLists->setLayout(dishListLayout);
    int i = 0;
    for(vector<Dish*>::iterator iter = allDish.begin();iter!= allDish.end();iter++)
    {
        QHBoxLayout *m_hBox = new QHBoxLayout;
        dishListLayout->addLayout(m_hBox);
        HBox.push_back(m_hBox);

        Dish* now = *iter;
        QLabel *m_name = new QLabel(now->getName());
        QLabel *m_price = new QLabel(QString::number(now->getPrice()));
        QPushButton *m_viewComment = new QPushButton("Viee Comment");
        QPushButton *m_order = new QPushButton("Add in Shopping Box");
        m_hBox->addWidget(m_name);
        m_hBox->addWidget(m_price);
        m_hBox->addWidget(m_viewComment);
        m_hBox->addWidget(m_order);

        dishName.push_back(m_name);
        dishPrice.push_back(m_price);
        viewComment.push_back(m_viewComment);
        addShoppingBox.push_back(m_order);

        //connect
        disconnect(m_order,SIGNAL(clicked(bool)),dishAddMap,SLOT(map()));
        connect(m_order,SIGNAL(clicked(bool)),dishAddMap,SLOT(map()));
        dishAddMap->setMapping(m_order,i++);
    }
    //connect
    disconnect(dishAddMap,SIGNAL(mapped(int)),this,SLOT(AddInShoppingBox(int)));
    connect(dishAddMap,SIGNAL(mapped(int)),this,SLOT(AddInShoppingBox(int)));
    disconnect(ui->ShoppingBoxButton,SIGNAL(clicked(bool)),this,SLOT(showCustomerCacu()));
    connect(ui->ShoppingBoxButton,SIGNAL(clicked(bool)),this,SLOT(showCustomerCacu()));
    disconnect(ui->ProgressButton,SIGNAL(clicked(bool)),this,SLOT(showProgress()));
    connect(ui->ProgressButton,SIGNAL(clicked(bool)),this,SLOT(showProgress()));
    emit REconnect(CUSTOMERMAIN);
}

void CustomerMainWindow::AddInShoppingBox(int num)
{
    vector<Dish*>::iterator iter = allDish.begin();
    for(int i = 0;i < num ;i++,iter++);
    //add in list
    Dish* now = *iter;
    user->addDishesNotPaid(now->getName());
    user->addDishesPrice(now->getPrice());
    ShowMessage("success!");
    user->saveData();
}

Ui::CustomerMainWindow *CustomerMainWindow::getMainUi()
{
    return ui;
}

void CustomerMainWindow::showCustomerCacu()
{
    cacuUi->setupUi(mainwindow);
    for(int i = 0; i < 8; i++)
    {
        cacuUi->comboBox->addItem(QString::number(i),i);
    }
    if(user->getTable()>0&&user->getTable()<9)
        cacuUi->comboBox->setCurrentIndex(user->getTable());
    connect(cacuUi->comboBox,SIGNAL(activated(int)),user,SLOT(setTable(int)));
    //add dish
    notPayDishAddMap = new QSignalMapper;
    notPayDishLayout = new QVBoxLayout;
    cacuUi->scrollAreaWidgetContents->setLayout(notPayDishLayout);
    int i = 0;
    vector<QString>::iterator strIter = user->getDishesNotPaid().begin();
    vector<int>::iterator priIter = user->getDishesPrice().begin();
    for(;(strIter != user->getDishesNotPaid().end()) && (priIter != user->getDishesPrice().end());strIter++,priIter++)
    {
        QHBoxLayout *m_HBox = new QHBoxLayout;
        notPayHBox.push_back(m_HBox);
        notPayDishLayout->addLayout(m_HBox);

        QLabel *m_label = new QLabel(*strIter);
        QLabel *m_label2 = new QLabel(QString::number(*priIter));
        QPushButton *m_delete = new QPushButton("Delete");

        m_HBox->addWidget(m_label);
        m_HBox->addWidget(m_label2);
        m_HBox->addWidget(m_delete);

        notPayDishName.push_back(m_label);
        notPaydishPrice.push_back(m_label2);
        notPayDeleteButton.push_back(m_delete);

        //connect
        disconnect(m_delete,SIGNAL(clicked(bool)),notPayDishAddMap,SLOT(map()));
        connect(m_delete,SIGNAL(clicked(bool)),notPayDishAddMap,SLOT(map()));
        notPayDishAddMap->setMapping(m_delete,i++);
    }
    disconnect(notPayDishAddMap,SIGNAL(mapped(int)),this,SLOT(deleteShoppingBox(int)));
    connect(notPayDishAddMap,SIGNAL(mapped(int)),this,SLOT(deleteShoppingBox(int)));
    emit REconnect(CUSTOMERCACU);
}

Ui::CustomerCacu *CustomerMainWindow::getCacuUi()
{
    return cacuUi;
}

void CustomerMainWindow::deleteShoppingBox(int num)
{
    user->deleteDishesPrice(num);
    user->deleteDishesNotPaid(num);
    ShowMessage("success!");
    user->saveData();
    showCustomerCacu();
}

void CustomerMainWindow::showProgress()
{
    proUi->setupUi(mainwindow);
    proDishLayout = new QVBoxLayout;

    proUi->scrollAreaWidgetContents->setLayout(proDishLayout);

    for(vector<QString>::iterator iter = user->getDishesNotPaid().begin();iter != user->getDishesNotPaid().end();iter++)
    {
        QHBoxLayout *m_HBox = new QHBoxLayout;
        proDishLayout->addLayout(m_HBox);
        proHBox.push_back(m_HBox);

        QLabel *m_name = new QLabel(*iter);
        QLabel *progress = new QLabel("Not Paid!");

        proName.push_back(m_name);
        proStatus.push_back(progress);

        m_HBox->addWidget(m_name);
        m_HBox->addWidget(progress);
    }
    for(vector<QString>::iterator iter = user->getDishesNotDone().begin();iter != user->getDishesNotDone().end();iter++)
    {
        QHBoxLayout *m_HBox = new QHBoxLayout;
        proDishLayout->addLayout(m_HBox);
        proHBox.push_back(m_HBox);

        QLabel *m_name = new QLabel(*iter);
        QLabel *progress = new QLabel("Not Done!");

        proName.push_back(m_name);
        proStatus.push_back(progress);

        m_HBox->addWidget(m_name);
        m_HBox->addWidget(progress);
    }
    for(vector<QString>::iterator iter = user->getDishesDoing().begin();iter != user->getDishesDoing().end();iter++)
    {
        QHBoxLayout *m_HBox = new QHBoxLayout;
        proDishLayout->addLayout(m_HBox);
        proHBox.push_back(m_HBox);

        QLabel *m_name = new QLabel(*iter);
        QLabel *progress = new QLabel("Doing!");

        proName.push_back(m_name);
        proStatus.push_back(progress);

        m_HBox->addWidget(m_name);
        m_HBox->addWidget(progress);
    }
    for(vector<QString>::iterator iter = user->getDishesHaveDone().begin();iter != user->getDishesHaveDone().end();iter++)
    {
        QHBoxLayout *m_HBox = new QHBoxLayout;
        proDishLayout->addLayout(m_HBox);
        proHBox.push_back(m_HBox);

        QLabel *m_name = new QLabel(*iter);
        QLabel *progress = new QLabel("Have Done!");

        proName.push_back(m_name);
        proStatus.push_back(progress);

        m_HBox->addWidget(m_name);
        m_HBox->addWidget(progress);
    }
    for(vector<QString>::iterator iter = user->getDishesEating().begin();iter != user->getDishesEating().end();iter++)
    {
        QHBoxLayout *m_HBox = new QHBoxLayout;
        proDishLayout->addLayout(m_HBox);
        proHBox.push_back(m_HBox);

        QLabel *m_name = new QLabel(*iter);
        QLabel *progress = new QLabel("Eating!");

        proName.push_back(m_name);
        proStatus.push_back(progress);

        m_HBox->addWidget(m_name);
        m_HBox->addWidget(progress);
    }
    emit REconnect(CUSTOMERPRO);
}

Ui::CustomerProgress *CustomerMainWindow::getProUi()
{
    return proUi;
}

void CustomerMainWindow::isPay()
{
    QMessageBox *m_msgBox = new QMessageBox;
    m_msgBox->setInformativeText("Sure to pay?");
    m_msgBox->setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    disconnect((QObject *)m_msgBox->button(QMessageBox::No),SIGNAL(clicked(bool)),m_msgBox,SLOT(close()));
    disconnect((QObject *)m_msgBox->button(QMessageBox::Yes),SIGNAL(clicked(bool)),this,SLOT(Pay()));
    connect((QObject *)m_msgBox->button(QMessageBox::No),SIGNAL(clicked(bool)),m_msgBox,SLOT(close()));
    connect((QObject *)m_msgBox->button(QMessageBox::Yes),SIGNAL(clicked(bool)),this,SLOT(Pay()));

    m_msgBox->show();
}

void CustomerMainWindow::Pay()
{
    user->setTable(cacuUi->comboBox->currentIndex());
    //add
    for(vector<QString>::iterator iter = user->getDishesNotPaid().begin();iter!=user->getDishesNotPaid().end();iter++)
    {
        user->addDishesNotDone(*iter);
    }
    //clear
    user->clearDisherPrice();
    user->clearDishesNotPaid();
    user->saveData();
    showCustomerCacu();
}

void CustomerMainWindow::SendMsg()
{
    QString message = proUi->lineEdit->text();
    qDebug()<<message;
    if(message.isEmpty())
    {
        ShowMessage("You can't send blank message!");
        return;
    }
    for(vector<QString>::iterator iter = user->getWaiter().begin();iter != user->getWaiter().end(); iter++)
    {
        //load
        QString namestr;
        namestr.append(*iter);
        namestr.append(".json");
        QFile userFile(namestr);
        userFile.open(QIODevice::ReadOnly);
        QByteArray userByte = userFile.readAll();
        QJsonDocument userJson = QJsonDocument::fromJson(userByte);
        QJsonObject *userObj = new QJsonObject(userJson.object());
        Waiter waiter;
        waiter.updateUser(userObj);
        //change
        waiter.addMsg(message);
        waiter.addSender(user->getName());
        waiter.savedata();
    }
    proUi->lineEdit->clear();
    showProgress();
    ShowMessage("Send Success!");
}
