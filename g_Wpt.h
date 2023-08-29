#ifndef G_WPT_H
#define G_WPT_H

#include<QDateTime>
#include"g_general.h"


class gWpt
{
public:
    gWpt();

    const int no_ele= -10000;
    const int no_hr = -1;
    const QDateTime no_time = QDateTime(QDate(1800, 1, 1), QTime(0, 0, 0));

    double lat;
    double lon;
    double ele;
    QDateTime time;

    uint magvar;
    uint geoidheight;
    QString name;
    QString cmt;
    QString desc;
    QString src;
    QList<link_t> links;
    QString sym;
    QString type;
    QString fix;
    uint sat;
    uint hdop;
    uint vdop;
    uint pdop;
    uint ageofdgpsdata;
    uint dgpsid;

 };

#endif // G_WPT_H
