#include "publisher.h"
#include "ui_publisher.h"

Publisher::Publisher(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Publisher)
{
    ui->setupUi(this);
}

Publisher::~Publisher()
{
    delete ui;
}
