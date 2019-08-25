#include "subscriber.h"
#include "ui_subscriber.h"

Subscriber::Subscriber(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Subscriber)
{
    ui->setupUi(this);
}

Subscriber::~Subscriber()
{
    delete ui;
}
