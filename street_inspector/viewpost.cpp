#include "viewpost.h"
#include "ui_viewpost.h"

#include <iostream>

viewpost::viewpost(QWidget *parent, QByteArray name, QByteArray lastname, std::string description, int supp, int user_id, int rep_id, int id) :
    QWidget(parent),
    ui(new Ui::viewpost)
{
    ui->setupUi(this);

    std::cout << "user_id = " << user_id << std::endl;
    std::cout << "rep_id = " << rep_id << std::endl;
    std::cout << "id = " << id << std::endl;

    ui->FIO->setText(QString::fromUtf8(name) + " " + QString::fromUtf8(lastname));
    ui->message->setText(QString::fromStdString(description));
    ui->supp->setText(QString::number(supp));
    repID = rep_id;
    userID = id;
    if (user_id == id)
    {
        ui->Delete->setEnabled(true);
        ui->supp_2->setEnabled(false);
    }
}

viewpost::~viewpost()
{
    delete ui;
}

void viewpost::on_back_clicked()
{
    close();
}

void viewpost::on_Delete_clicked()
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(disconnected()), this, SLOT(sockDisconnect()));

    socket->connectToHost("192.168.0.6", 5555);

    QByteArray result = "{\"type\":\"report\","
                        "\"action\":\"deleteReport\","
                        "\"id\":"+QByteArray::number(repID, 'f', 0)+"}";
    socket->write(result);
    socket->waitForBytesWritten(500);
    close();
}

void viewpost::on_supp_2_clicked()
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(sockReady()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(sockDisconnect()));

    socket->connectToHost("192.168.0.6", 5555);

    QByteArray result = "{\"type\":\"report\","
                        "\"action\":\"likeReport\","
                        "\"rep_id\":"+QByteArray::number(repID, 'f', 0)+","
                        "\"user_id\":"+QByteArray::number(userID, 'f', 0)+"}";
    socket->write(result);
    socket->waitForBytesWritten(500);
    socket->waitForReadyRead(1000);
}

void viewpost::sockReady()
{
    if (socket->waitForConnected(500))
    {
        Data = socket->readAll();
        qDebug() << Data;
        doc = QJsonDocument::fromJson(Data, &docError);

        if (docError.errorString().toInt() == QJsonParseError::NoError)
        {
            if (doc.object().value("result").toString() == "true")
            {
                qDebug() << "Нашел!";
            }
            else if (doc.object().value("result").toString() == "false")
            {
                qDebug() << "Не нашел!";
            }
        }
    }
}

void viewpost::sockDisconnect()
{
    socket->deleteLater();
}
