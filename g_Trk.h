#ifndef G_TRK_H
#define G_TRK_H
#include <QString>
#include <QList>
#include "g_Trkseg.h"

class gTrk
{
public:
    gTrk();
    QString name;
    QString cmt;
    QString desc;
    QString src;
    QString links;
    QString number;
    QString type;
    QList<gTrkseg> segs;
    double NumPunts() const;
    double Distancia() const;
    double Puja() const;
    double Baixa() const;
};

#endif // G_TRK_H
