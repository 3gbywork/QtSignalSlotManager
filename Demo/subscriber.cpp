#include "subscriber.h"
#include "ui_subscriber.h"

#include <QStringListModel>

#include "qtsignalslotmanager.h"

static const char *slotName = SLOT(slot_recvMessage(QString));

Subscriber::Subscriber(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Subscriber)
{
    setAttribute(Qt::WA_DeleteOnClose);

    ui->setupUi(this);

    m_model = new QStringListModel;
    ui->subjects->setModel(m_model);
}

Subscriber::~Subscriber()
{
    for (auto id : m_model->stringList())
    {
        QtSignalSlotManager::getInstance().unsubscribe(id.toInt(), this, slotName);
    }
    m_model->deleteLater();
    delete ui;
}

void Subscriber::on_subBtn_clicked()
{
    int id = ui->spinBox->value();
    QtSignalSlotManager::getInstance().subscribe(id, this, slotName);

    if(m_model->stringList().contains(QString::number(id)))
        return;

    m_model->insertRow(m_model->rowCount());
    auto index = m_model->index(m_model->rowCount()-1);
    m_model->setData(index, id);
}

void Subscriber::on_unsubBtn_clicked()
{
    int id = ui->subjects->currentText().toInt();
    QtSignalSlotManager::getInstance().unsubscribe(id, this, slotName);

    auto row = m_model->stringList().indexOf(QString::number(id));
    m_model->removeRow(row);
}

void Subscriber::slot_recvMessage(QString message)
{
    ui->msgList->addItem(message);
}
