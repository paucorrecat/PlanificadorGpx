#include "GeoMath.h"



//Tret de QMapShack
// from http://www.movable-type.co.uk/scripts/LatLongVincenty.html
// qreal GPS_Math_Distance(const qreal u1, const qreal v1, const qreal u2, const qreal v2, qreal& a1, qreal& a2) {
double CalculaDistancia(double lonR1, double latR1, double lonR2, double latR2 ) {

    // lonR1 = longitud en radiants
    // latR1 = latitud en radiants
    double cosSigma = 0.0;
    double sigma = 0.0;
    double sinAlpha = 0.0;
    double cosSqAlpha = 0.0;
    double cos2SigmaM = 0.0;
    double sinSigma = 0.0;
    double sinLambda = 0.0;
    double cosLambda = 0.0;

    double a = 6378137.0, b = 6356752.3142, f = 1.0 / 298.257223563;  // WGS-84 ellipsiod
    // a, b : major & minor semi-axes of the ellipsoid
    // f : flattering = (a-b)/a

    double L = lonR2 - lonR1;  // Primera aproximació

    double U1 = qAtan((1 - f) * qTan(latR1));
    double U2 = qAtan((1 - f) * qTan(latR2));
    double sinU1 = qSin(U1), cosU1 = qCos(U1);
    double sinU2 = qSin(U2), cosU2 = qCos(U2);
    double lambda = L, lambdaP = 2 * PI;  //
    unsigned iterLimit = 20;

    while ((qAbs(lambda - lambdaP) > 1e-12) && (--iterLimit > 0)) {
        sinLambda = qSin(lambda);
        cosLambda = qCos(lambda);
        sinSigma = qSqrt((cosU2 * sinLambda) * (cosU2 * sinLambda) +
                         (cosU1 * sinU2 - sinU1 * cosU2 * cosLambda) * (cosU1 * sinU2 - sinU1 * cosU2 * cosLambda));

        if (sinSigma == 0) {
            return 0;  // co-incident points
        }

        cosSigma = sinU1 * sinU2 + cosU1 * cosU2 * cosLambda;
        sigma = qAtan2(sinSigma, cosSigma);
        sinAlpha = cosU1 * cosU2 * sinLambda / sinSigma;
        cosSqAlpha = 1 - sinAlpha * sinAlpha;
        cos2SigmaM = cosSigma - 2 * sinU1 * sinU2 / cosSqAlpha;

        if (qIsNaN(cos2SigmaM)) {
            cos2SigmaM = 0;  // equatorial line: cosSqAlpha=0 (§6)
        }

        double C = f / 16 * cosSqAlpha * (4 + f * (4 - 3 * cosSqAlpha));
        lambdaP = lambda;
        lambda = L + (1 - C) * f * sinAlpha *
                         (sigma + C * sinSigma * (cos2SigmaM + C * cosSigma * (-1 + 2 * cos2SigmaM * cos2SigmaM)));
    }
    if (iterLimit == 0) {
        return FP_NAN;  // formula failed to converge
    }
    double uSq = cosSqAlpha * (a * a - b * b) / (b * b);
    double A = 1 + uSq / 16384 * (4096 + uSq * (-768 + uSq * (320 - 175 * uSq)));
    double B = uSq / 1024 * (256 + uSq * (-128 + uSq * (74 - 47 * uSq)));
    double deltaSigma =
        B * sinSigma *
        (cos2SigmaM + B / 4 *
                          (cosSigma * (-1 + 2 * cos2SigmaM * cos2SigmaM) -
                           B / 6 * cos2SigmaM * (-3 + 4 * sinSigma * sinSigma) * (-3 + 4 * cos2SigmaM * cos2SigmaM)));
    double s = b * A * (sigma - deltaSigma);

    // No sé ben bé què són ni per a què serveixen
    //a1 = qAtan2(cosU2 * sinLambda, cosU1 * sinU2 - sinU1 * cosU2 * cosLambda) * 360 / (2* PI); //a1 is the initial bearing, or forward azimuth ¿?
    //a2 = qAtan2(cosU1 * sinLambda, -sinU1 * cosU2 + cosU1 * sinU2 * cosLambda) * 360 / (2* PI); // a2 is the final bearing (in direction p1→p2)
    return s;


}

