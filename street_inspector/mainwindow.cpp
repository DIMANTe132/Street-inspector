#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_registration_clicked()
{
    close();
    reg = new registration();
    reg->show();
}

void MainWindow::on_sign_in_clicked()
{
    createMarks();
}

void MainWindow::newreport(double latitude, double longitude)
{
    addreport *rep = new addreport(nullptr, latitude, longitude, name, lastname, id);
    map->rootContext()->setContextProperty("addreport", rep);
    rep->show();
}

void MainWindow::showreport(double latitude, double longitude)
{
    for (report *rep : reports)
    {
        if (rep->latitude == latitude && rep->longitude == longitude)
        {
            viewpost *post = new viewpost(nullptr, rep->name, rep->lastname, rep->description, rep->supp , rep->user_id, rep->id, id);
            map->rootContext()->setContextProperty("showpost", post);
            post->show();
        }
    }
}

void MainWindow::createMarks()
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(sockReady()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(sockDisconnect()));
    socket->connectToHost("192.168.0.6", 5555);
    QByteArray sign_in = "{\"type\":\"user\","
                        "\"action\":\"checkUser\","
                        "\"phone_number\":\""+ui->login->text().toUtf8()+"\","
                        "\"password\":\""+ui->password->text().toUtf8()+"\"}";
    socket->write(sign_in);
    socket->waitForBytesWritten(500);
    socket->waitForReadyRead(500);

    if (name.length() != 0 && lastname.length() != 0)
    {
        close();
        map = new QQuickView;
        map->setSource(QUrl("qrc:/map.qml"));
        map->setResizeMode(QQuickView::SizeRootObjectToView);

        Root = map->rootObject();
        map->rootContext()->setContextProperty("window", this);
        reports.clear();
        QByteArray returnReports = "{\"type\":\"report\","
                                    "\"action\":\"returnReports\"}";
        socket->write(returnReports);
        socket->waitForBytesWritten(500);
        socket->waitForReadyRead(5000);

        for (report* rep : reports)
        {
            emit addElement(rep->latitude, rep->longitude);
        }
    }
}

void MainWindow::sockReady()
{
    if (socket->waitForConnected(500))
    {
        Data = socket->readAll();
        doc = QJsonDocument::fromJson(Data, &docError);

        if (docError.errorString().toInt() == QJsonParseError::NoError)
        {
            if (doc.object().value("type").toString() == "user")
            {
                if (doc.object().value("name").toString() == "")
                    ui->error->setText("Ошибка телефона или пароля");

                else
                {
                    id = doc.object().value("id").toInt();
                    std::cout << "id: " << id << std::endl;
                    name = doc.object().value("name").toString().toUtf8();
                    lastname = doc.object().value("lastname").toString().toUtf8();
                }
            }
            else if (doc.object().value("type").toString() == "report")
            {
                QJsonArray arr = doc.object().value("result").toArray();
                qDebug() << arr;
                for (int i = 0; i < arr.count(); i++)
                {
                    QJsonObject obj = arr.at(i).toObject();

                    report *rep = new report();
                    rep->name = obj.value("name").toString().toUtf8();
                    rep->lastname = obj.value("lastname").toString().toUtf8();
                    rep->latitude = obj.value("latitude").toDouble();
                    rep->longitude = obj.value("longitude").toDouble();
                    rep->description = obj.value("message").toString().toStdString();
                    rep->supp = obj.value("supp").toInt();
                    rep->user_id = obj.value("user_id").toInt();
                    rep->id = obj.value("id").toInt();
                    reports.push_back(rep);
                }
            }
        }
        else
            ui->error->setText("Ошибка телефона или пароля");
    }
}

void MainWindow::sockDisconnect()
{
    socket->deleteLater();
}
