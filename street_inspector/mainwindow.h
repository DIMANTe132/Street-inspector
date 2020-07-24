#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "registration.h"
#include "addreport.h"
#include <QQuickView>
#include <QGraphicsObject>
#include <QtGui>
#include <QQmlContext>
#include <vector>
#include "viewpost.h"
#include <QTcpSocket>
#include <QDebug>
#include <QJsonArray>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Q_INVOKABLE void newreport(double latitude, double longitude);
    Q_INVOKABLE void showreport(double latitude, double longitude);
    Q_INVOKABLE void createMarks();

signals:
    void addElement(double latitude, double longitude);

public slots:
    void sockReady();
    void sockDisconnect();

private slots:
    void on_registration_clicked();

    void on_sign_in_clicked();

private:
    Ui::MainWindow *ui;

    int id;
    QByteArray name;
    QByteArray lastname;

    QQuickView *map;
    registration *reg;
    QQuickItem *Root;
    std::vector<report*> reports;
    QTcpSocket *socket;
    QByteArray Data;
    QJsonDocument doc;
    QJsonParseError docError;
};
#endif // MAINWINDOW_H
