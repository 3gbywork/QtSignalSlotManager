#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <QWidget>

namespace Ui {
class Subscriber;
}

class QStringListModel;
class Subscriber : public QWidget
{
    Q_OBJECT

public:
    explicit Subscriber(QWidget *parent = nullptr);
    ~Subscriber();

private slots:
    void on_subBtn_clicked();

    void on_unsubBtn_clicked();

private slots:
    void slot_recvMessage(QString message);

private:
    Ui::Subscriber *ui;
    QStringList m_subjects;
    QStringListModel *m_model;
};

#endif // SUBSCRIBER_H
