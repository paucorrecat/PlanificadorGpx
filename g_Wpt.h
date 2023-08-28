#ifndef G_WPT_H
#define G_WPT_H

#include<QDateTime>
#include"g_Projecte.h"

class gWpt
{
public:
    gWpt();

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
