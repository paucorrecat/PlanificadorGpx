#include "g_Trk.h"

gTrk::gTrk()
{

}

double gTrk::Distancia() const {
    double Total = 0;
    for (int n = 0 ; n < segs.count() ;n++) {
        Total += segs.at(n).Distancia();
    }
    return Total;
}
