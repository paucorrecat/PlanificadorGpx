#ifndef G_TRKPT_H
#define G_TRKPT_H

#include<QDateTime>

static const int no_ele= -10000;
static const int no_hr = -1;
// WARNING: No tinc clara la gestió de memòria d'això
static const QDateTime no_time = QDateTime(QDate(1800, 1, 1), QTime(0, 0, 0));

class gTrkpt
{
public:

    gTrkpt();
    double lat;
    double lon;
    int ele = no_ele;
    QDateTime time = no_time;
    int hr= no_hr;  //Heart rate

};

#endif // G_TRKPT_H
