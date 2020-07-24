#include "registration.h"
#include "ui_registration.h"
#include "mainwindow.h"

using namespace std;

registration::registration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registration)
{
    ui->setupUi(this);
}

registration::~registration()
{
    delete ui;
}

void registration::on_back_clicked()
{
    close();
    MainWindow *login = new MainWindow();
    login->show();
}

void registration::on_tryregistration_clicked()
{
    bool n = true , l = true , p = true , e = true , pass = true , ppass = true ;
    string name = ui->name->text().toStdString();
    string last_name = ui->last_name->text().toStdString();
    string phone_number = ui->phone_number->text().toStdString();
    string e_mail = ui->e_mail->text().toStdString();
    string password = ui->password->text().toStdString();
    string second_password = ui->second_password->text().toStdString();

    if (name.empty())
    {
        n = false;
        ui->name->clear();
        ui->name->setPlaceholderText("Имя не может быть пустым");
    }
    else if (name.length() < 2 || name.length() > 20)
    {
        n = false;
        ui->name->clear();
        ui->name->setPlaceholderText("Длина имени должна быть 2-20");
    }
    else
    {
        for (int i = 0; i < name.length(); i++)
        {
            if ((name[i] >= '0' && name[i] <= '9'))
            {
                n = false;
                ui->name->clear();
                ui->name->setPlaceholderText("Имя может включать только символы a-z A-Z");
                break;
            }
        }
    }

    if (last_name.empty())
    {
        l = false;
        ui->last_name->clear();
        ui->last_name->setPlaceholderText("Фамилия не может быть пустой");
    }
    else if (last_name.length() < 2 || last_name.length() > 20)
    {
        l = false;
        ui->last_name->clear();
        ui->last_name->setPlaceholderText("Длина фамилии должна быть 2-20");
    }
    else
    {
        for (int i = 0; i < last_name.length(); i++)
        {
            if ((last_name[i] >= '0' && last_name[i] <= '9'))
            {
                l = false;
                ui->last_name->clear();
                ui->last_name->setPlaceholderText("Фамилия может включать только символы a-z A-Z");
                break;
            }
        }
    }

    if (phone_number.empty())
    {
        p = false;
        ui->phone_number->clear();
        ui->phone_number->setPlaceholderText("Номер не может быть пустой");
    }
    else
    {
        for (int i = 0; i < phone_number.length(); i++)
        {
            if (phone_number[i] < '0' && phone_number[i] > '9' && phone_number[i] != '+')
            {
                p = false;
                ui->phone_number->clear();
                ui->phone_number->setPlaceholderText("Номер включает неразрешенные символы");
                break;
            }
        }
        if (phone_number[0] == '+' && phone_number[1] == '7')
        {
            phone_number.replace(0, 2, "8");
        }

        if (phone_number[0] != '8')
        {
            p = false;
            ui->phone_number->clear();
            ui->phone_number->setPlaceholderText("Номер должен быть вида 8**********");
        }
        if (phone_number.length() != 11)
        {
            p = false;
            ui->phone_number->clear();
            ui->phone_number->setPlaceholderText("Номер должен иметь 11 цифр");
        }
    }

    if (e_mail.empty())
    {
        e = false;
        ui->e_mail->clear();
        ui->e_mail->setPlaceholderText("e-mail не может быть пустой");
    }
    else
    {
        int all_presents = 0;
        std::string suitable_symbols = "-_.@";
        for(int i = 0; i < e_mail.length(); i++)
        {
            if( !isalpha(e_mail[i]) && !isdigit(e_mail[i]) && suitable_symbols.find(e_mail[i]) == std::string::npos)
            {
                e = false;
                ui->e_mail->clear();
                ui->e_mail->setPlaceholderText("e-mail записан не корректно");
                break;
            }
            if(i > 0 && e_mail[i] == '.' && e_mail[i - 1] == '.')
            {
                e = false;
                ui->e_mail->clear();
                ui->e_mail->setPlaceholderText("e-mail записан не корректно");
                break;
            }
            else if(i > 0 && e_mail[i] == '@' && !all_presents)
            {
                all_presents = 1;
            }
            else if(e_mail[i] == '@' && all_presents)
            {
                e = false;
                ui->e_mail->clear();
                ui->e_mail->setPlaceholderText("e-mail записан не корректно");
                break;
            }
            else if( ( isalpha(e_mail[i]) || isdigit(e_mail[i]) ) && all_presents == 1)
            {
                all_presents = 2;
            }
            else if(e_mail[i] == '.' && all_presents == 2)
            {
                all_presents = 3;
            }
            else if(isalpha(e_mail[i]) && all_presents == 3 && e_mail[i + 2] == '\0')
            {
                all_presents = 4;
            }
        }
    }

    if (password.empty())
    {
        pass = false;
        ui->password->clear();
        ui->password->setPlaceholderText("Пароль не может быть пустой");
    }
    else if (password.length() < 8)
    {
        pass = false;
        ui->password->clear();
        ui->password->setPlaceholderText("Минимальная длина пароля - 8");
    }

    if (second_password.empty() || second_password != password)
    {
        ppass = false;
        ui->second_password->clear();
        ui->second_password->setPlaceholderText("Пароли не совпадают");
    }

    if (!n)
        ui->name->setStyleSheet("QLineEdit { background: rgb(255, 117, 117)}");
    else
        ui->name->setStyleSheet("QLineEdit { background: rgb(158, 255, 255);}");
    if (!l)
        ui->last_name->setStyleSheet("QLineEdit { background: rgb(255, 117, 117)}");
    else
        ui->last_name->setStyleSheet("QLineEdit { background: rgb(158, 255, 255);}");
    if (!p)
        ui->phone_number->setStyleSheet("QLineEdit { background: rgb(255, 117, 117)}");
    else
        ui->phone_number->setStyleSheet("QLineEdit { background: rgb(158, 255, 255);}");
    if (!e)
        ui->e_mail->setStyleSheet("QLineEdit { background: rgb(255, 117, 117)}");
    else
        ui->e_mail->setStyleSheet("QLineEdit { background: rgb(158, 255, 255);}");
    if (!pass)
        ui->password->setStyleSheet("QLineEdit { background: rgb(255, 117, 117)}");
    else
        ui->password->setStyleSheet("QLineEdit { background: rgb(158, 255, 255);}");
    if (!ppass)
        ui->second_password->setStyleSheet("QLineEdit { background: rgb(255, 117, 117)}");
    else
        ui->second_password->setStyleSheet("QLineEdit { background: rgb(158, 255, 255);}");

    if (n && l && p && e && pass && ppass)
    {
        socket = new QTcpSocket(this);
        connect(socket, SIGNAL(disconnected()), this, SLOT(sockDisconnect()));
        socket->connectToHost("192.168.0.6", 5555);

        QByteArray result = "{\"type\":\"user\","
                            "\"action\":\"pushUser\","
                            "\"name\":\""+ui->name->text().toUtf8()+"\","
                            "\"lastname\":\""+ui->last_name->text().toUtf8()+"\","
                            "\"phone_number\":\""+ui->phone_number->text().toUtf8()+"\","
                            "\"email\":\""+ui->e_mail->text().toUtf8()+"\","
                            "\"password\":\""+ui->password->text().toUtf8()+"\"}";
        socket->write(result);
        socket->waitForBytesWritten(500);
        close();
        MainWindow *login = new MainWindow();
        login->show();
        sockDisconnect();
    }
}

void registration::sockDisconnect()
{
    socket->deleteLater();
}
