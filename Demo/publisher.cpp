#include "publisher.h"
#include "ui_publisher.h"

#include <QStringListModel>
#include <QThread>

#include "qtsignalslotmanager.h"

static const char *signalName = SIGNAL(signal_publishMessage(QString));

Publisher::Publisher(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Publisher)
{
    setAttribute(Qt::WA_DeleteOnClose);

    ui->setupUi(this);

    m_model = new QStringListModel;
    ui->subjects->setModel(m_model);
}

Publisher::~Publisher()
{
    for (auto id : m_model->stringList())
    {
        QtSignalSlotManager::getInstance().removeSubject(id.toInt(), this, signalName);
    }
    m_model->deleteLater();
    delete ui;
}

void Publisher::on_regBtn_clicked()
{
    int id = ui->spinBox->value();
    QtSignalSlotManager::getInstance().addSubject(id, this, signalName);

    if(m_model->stringList().contains(QString::number(id)))
        return;

    m_model->insertRow(m_model->rowCount());
    auto index = m_model->index(m_model->rowCount()-1);
    m_model->setData(index, id);
}

void Publisher::on_publishBtn_clicked()
{
    QString cnt = ui->msgLine->text();
    int channel = ui->spinBox->value();

    auto thread = QThread::create([=]{
        auto msg = QString("%1 publish \"%2\" in channel %3").arg(objectName()).arg(cnt).arg(channel);
        emit signal_publishMessage(msg);
    });
    thread->start();
    thread->wait();
    thread->deleteLater();
}

void Publisher::on_unsubBtn_clicked()
{
    int id = ui->subjects->currentText().toInt();
    QtSignalSlotManager::getInstance().removeSubject(id, this, signalName);

    auto row = m_model->stringList().indexOf(QString::number(id));
    m_model->removeRow(row);
}
