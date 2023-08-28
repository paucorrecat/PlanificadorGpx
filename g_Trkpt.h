#ifndef G_TRKPT_H
#define G_TRKPT_H

#include<QDateTime>

class gTrkpt
{
public:

    const int no_ele= -10000;
    const int no_hr = -1;
    const QDateTime no_time = QDateTime(QDate(1800, 1, 1), QTime(0, 0, 0));

    gTrkpt();
    double lat;
    double lon;
    int ele = no_ele;
    QDateTime time = no_time;
    int hr= no_hr;  //Heart rate

};

#endif // G_TRKPT_H
