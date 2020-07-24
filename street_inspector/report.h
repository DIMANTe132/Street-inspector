#ifndef REPORT_H
#define REPORT_H

#include <string>
#include <QByteArray>

struct report
{
    int id;
    int user_id;
    QByteArray name;
    QByteArray lastname;
    double latitude;
    double longitude;
    std::string description;
    int supp;
};

#endif // REPORT_H
