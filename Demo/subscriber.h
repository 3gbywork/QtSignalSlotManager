#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <QWidget>

namespace Ui {
class Subscriber;
}

class Subscriber : public QWidget
{
    Q_OBJECT

public:
    explicit Subscriber(QWidget *parent = nullptr);
    ~Subscriber();

private:
    Ui::Subscriber *ui;
};

#endif // SUBSCRIBER_H
