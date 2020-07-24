#include "addreport.h"
#include "ui_addreport.h"
#include <iostream>

addreport::addreport(QWidget *parent, double latitude, double longitude, QByteArray name, QByteArray lastname, int id) :
    QWidget(parent),
    ui(new Ui::addreport)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(disconnected()), this, SLOT(sockDisconnect()));

    ui->FIO->setText(QString::fromUtf8(name) + " " + QString::fromUtf8(lastname));
    rep = new report();
    rep->name = name;
    rep->lastname = lastname;
    rep->latitude = latitude;
    rep->longitude = longitude;
    rep->supp = 0;
    rep->user_id = id;
}

addreport::~addreport()
{
    delete ui;
}

void addreport::on_back_clicked()
{
    close();
}

void addreport::on_pushreport_clicked()
{
    socket->connectToHost("192.168.0.6", 5555);

    QByteArray result = "{\"type\":\"report\","
                        "\"action\":\"pushReport\","
                        "\"latitude\":\""+QByteArray::number(rep->latitude, 'f', 10)+"\","
                        "\"longitude\":\""+QByteArray::number(rep->longitude, 'f', 10)+"\","
                        "\"supp\":\""+QByteArray::number(rep->supp, 'f', 0)+"\","
                        "\"user_id\":\""+QByteArray::number(rep->user_id, 'f', 0)+"\","
                        "\"user_name\":\""+rep->name+"\","
                        "\"user_lastname\":\""+rep->lastname+"\","
                        "\"message\":\""+ui->textEdit->toPlainText().toUtf8()+"\"}";
    socket->write(result);
    socket->waitForBytesWritten(500);
    close();
}

void addreport::sockDisconnect()
{
    socket->deleteLater();
}
