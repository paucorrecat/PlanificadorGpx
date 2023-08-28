#ifndef G_TRKSEG_H
#define G_TRKSEG_H
#include <QList>
#include "g_Trkpt.h"

class gTrkseg
{
public:
    gTrkseg();
    QList<gTrkpt> punts;
};

#endif // G_TRKSEG_H
