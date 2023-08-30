#ifndef G_TRKSEG_H
#define G_TRKSEG_H
#include <QList>
#include "g_Trkpt.h"

class gTrkseg
{
public:
    gTrkseg();
    QList<gTrkpt> punts;
    double Distancia() const;
    double Puja() const ;
    double Baixa() const ;

};

#endif // G_TRKSEG_H
