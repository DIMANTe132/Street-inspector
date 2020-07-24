#ifndef ADDREPORT_H
#define ADDREPORT_H

#include <QWidget>
#include <QtQuick>
#include <QtLocation/QLocation>
#include "report.h"

namespace Ui {
class addreport;
}

class addreport : public QWidget
{
    Q_OBJECT

public:
    explicit addreport(QWidget *parent = nullptr, double latitude = 0, double longitude = 0, QByteArray name = "", QByteArray lastname= "", int id = 0);
    ~addreport();

private slots:
    void on_back_clicked();

    void on_pushreport_clicked();

public slots:
    void sockDisconnect();

private:
    Ui::addreport *ui;
    report *rep;
    QTcpSocket *socket;
};

#endif // ADDREPORT_H
