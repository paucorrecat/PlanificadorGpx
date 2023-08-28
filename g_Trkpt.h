#ifndef G_TRKPT_H
#define G_TRKPT_H

#include<QDateTime>

class gTrkpt
{
public:
    gTrkpt();
    double lat;
    double lon;
    double ele;
    QDateTime time;
    uint hr;

};

#endif // G_TRKPT_H
