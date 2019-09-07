#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVBoxLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>

#include "publisher.h"
#include "subscriber.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    static int publisherCount = 1;
    static int subscriberCount = 1;

    auto widget = new QWidget();
    auto layout = new QVBoxLayout(widget);

    auto publisherGroup = new QGroupBox();
    publisherGroup->setTitle("Publisher");
    auto pubLayout = new QVBoxLayout(publisherGroup);
//    auto pubLine = new QLineEdit();
    auto newPubBtn = new QPushButton();
    newPubBtn->setText("New Publisher");
//    pubLayout->addWidget(pubLine);
    pubLayout->addWidget(newPubBtn);
    connect(newPubBtn, &QPushButton::clicked, [=]{
        auto publisher = new Publisher();
        publisher->setWindowTitle(QString("Publisher %1").arg(publisherCount++));
        publisher->show();
    });

    auto subscriberGroup = new QGroupBox();
    subscriberGroup->setTitle("Subscriber");
    auto subLayout = new QVBoxLayout(subscriberGroup);
    auto newSubBtn = new QPushButton();
    newSubBtn->setText("New Subscriber");
    subLayout->addWidget(newSubBtn);
    connect(newSubBtn, &QPushButton::clicked, [=]{
        auto subscriber = new Subscriber();
        subscriber->setWindowTitle(QString("Subscriber %1").arg(subscriberCount++));
        subscriber->show();
    });

    layout->addWidget(publisherGroup);
    layout->addWidget(subscriberGroup);

    setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
