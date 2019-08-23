#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <QWidget>

namespace Ui {
class Publisher;
}

class Publisher : public QWidget
{
    Q_OBJECT

public:
    explicit Publisher(QWidget *parent = nullptr);
    ~Publisher();

private:
    Ui::Publisher *ui;
};

#endif // PUBLISHER_H
