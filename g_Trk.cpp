#include "g_Trk.h"

gTrk::gTrk()
{

}

double gTrk::NumPunts() const {
    int Total = 0;
    for (int n = 0 ; n < segs.count() ;n++) {
        Total += segs.at(n).punts.count();
    }
    return Total;
}

double gTrk::Distancia() const {
    double Total = 0;
    for (int n = 0 ; n < segs.count() ;n++) {
        Total += segs.at(n).Distancia();
    }
    return Total;
}
double gTrk::Puja() const {
    double Total = 0;
    for (int n = 0 ; n < segs.count() ;n++) {
        Total += segs.at(n).Puja();
    }
    return Total;
}
double gTrk::Baixa() const {
    double Total = 0;
    for (int n = 0 ; n < segs.count() ;n++) {
        Total += segs.at(n).Baixa();
    }
    return Total;
}
