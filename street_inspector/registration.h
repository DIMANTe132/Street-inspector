#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QWidget>
#include <QTcpSocket>
#include <string>

namespace Ui {
class registration;
}

class registration : public QWidget
{
    Q_OBJECT

public:
    explicit registration(QWidget *parent = nullptr);
    ~registration();

public slots:
    void sockDisconnect();

private slots:
    void on_back_clicked();

    void on_tryregistration_clicked();

private:
    Ui::registration *ui;
    QTcpSocket *socket;
};

#endif // REGISTRATION_H
