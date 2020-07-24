#ifndef VIEWPOST_H
#define VIEWPOST_H

#include <QMainWindow>
#include "registration.h"
#include "addreport.h"
#include <QTcpSocket>
#include <QDebug>
#include <QJsonArray>

namespace Ui {
class viewpost;
}

class viewpost : public QWidget
{
    Q_OBJECT

public:
    explicit viewpost(QWidget *parent = nullptr, QByteArray name = "", QByteArray lastname = "", std::string description = "", int supp = 0,int user_id = 0, int rep_id = 0, int id = 0);
    ~viewpost();

private slots:
    void on_back_clicked();

    void on_Delete_clicked();

    void on_supp_2_clicked();

public slots:
    void sockReady();
    void sockDisconnect();

private:
    Ui::viewpost *ui;
    int repID;
    int userID;
    QByteArray Data;
    QTcpSocket *socket;
    QJsonDocument doc;
    QJsonParseError docError;
};

#endif // VIEWPOST_H
