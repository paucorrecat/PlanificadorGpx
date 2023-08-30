#include "g_Trkseg.h"
#include "g_Trkpt.h"
#include "GeoMath.h"

gTrkseg::gTrkseg()
{

}

double gTrkseg::Distancia() const {
    double Total = 0;
    double lon1, lat1;
    lon1 = punts.at(0).lon;
    lat1 = punts.at(0).lat;
    for (int n = 1 ; n < punts.count();n++) {
        Total = Total + CalculaDistancia(lon1 *DEG_TO_RAD, lat1 * DEG_TO_RAD,
                                         punts.at(n).lon * DEG_TO_RAD, punts.at(n).lat * DEG_TO_RAD);
        lon1 = punts.at(n).lon;
        lat1 = punts.at(n).lat;
    }
    return Total;
}

double gTrkseg::Puja() const {
    double Total = 0;
    double ele1;
    int n=0;
    while ((punts.at(n).ele == no_ele)&&(n<punts.count())) {
        n++;
    }
    if (n==punts.count()) {
        return 0;// No hi ha cap punt amb dates d'elevació
    }
    ele1 = punts.at(n).ele;
    while (n<punts.count()) {
        if (punts.at(n).ele != no_ele) {
            if (punts.at(n).ele> ele1) {
                Total += punts.at(n).ele -ele1;
            }
            ele1 = punts.at(n).ele;
        }
        n++;
    }
    return Total;
}

double gTrkseg::Baixa() const {
    double Total = 0;
    double ele1;
    int n=0;
    while ((punts.at(n).ele == no_ele)&&(n<punts.count())) {
        n++;
    }
    if (n==punts.count()) {
        return 0;// No hi ha cap punt amb dates d'elevació
    }
    ele1 = punts.at(n).ele;
    while (n<punts.count()) {
        if (punts.at(n).ele != no_ele) {
            if (punts.at(n).ele < ele1) {
                Total += ele1 - punts.at(n).ele;
            }
            ele1 = punts.at(n).ele;
        }
        n++;
    }
    return Total;
}



