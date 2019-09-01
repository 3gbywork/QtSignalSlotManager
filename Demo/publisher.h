#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <QWidget>

namespace Ui {
class Publisher;
}

class QStringListModel;
class Publisher : public QWidget
{
    Q_OBJECT

public:
    explicit Publisher(QWidget *parent = nullptr);
    ~Publisher();

signals:
    void signal_publishMessage(QString message);

private slots:
    void on_regBtn_clicked();

    void on_publishBtn_clicked();

    void on_unsubBtn_clicked();

private:
    Ui::Publisher *ui;
    QStringList m_listSubjects;
    QStringListModel *m_model;
};

#endif // PUBLISHER_H
