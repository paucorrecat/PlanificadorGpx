#ifndef FITXERGPX_H
#define FITXERGPX_H

// #include "data.h" Es per GPXSee
#include <QDomDocument>
#include <QString>
#include <QObject>
#include <QUrl>
#include <QRegularExpression>
#include "g_Projecte.h"
//#include "g_Wpt.h"


class FitxerGpx
{
public:
    FitxerGpx();

    gProjecte getProjecte();
    void setProjecte(gProjecte Proj);
    // Fitxer
    QString NomFitxer;
    QString Carpeta;
    QString NomBaseFitxer;

    //Atributs (Qui i com s'ha fet el fitxer)




    void Llegir(QString _NomFitxer);
    void Guardar(QString _NomFitxer);


private:


    gProjecte Prjct;
    gProjecte PrjtBuit;

    gTrk ll_Trk(const QDomElement& xml);
    gTrkseg ll_Trkseg(const QDomElement& xml);
    gTrkpt ll_Trkpt(const QDomElement& xml);
    QDateTime parseTimestamp(const QString& timetext, int& tzoffset);

    /*
    void readWpt(const QDomNode& xml, gWpt &wpt);

    void readMetadata(const QDomNode& xml, metadata_t& metadata);
    QDateTime parseTimestamp(const QString& timetext, int &tzoffset);
    */

};


#endif // FITXERGPX_H


/**********************************************/
/* Documentació extra per a futures millores  */
/**********************************************/

// DOC: links a especificacions de gpx diferents

/* Per si vull tenir en compte possibles versions de xml
const char* gpx_links_gpx_ns = "http://www.topografix.com/GPX/1/1";
const char* gpx_links_xsi_ns = "http://www.w3.org/2001/XMLSchema-instance";
const char* gpx_links_gpxx_ns = "http://www.garmin.com/xmlschemas/GpxExtensions/v3";
const char* gpx_links_gpxtpx_ns = "http://www.garmin.com/xmlschemas/TrackPointExtension/v1";
const char* gpx_links_wptx1_ns = "http://www.garmin.com/xmlschemas/WaypointExtension/v1";
const char* gpx_links_rmc_ns = "urn:net:trekbuddy:1.0:nmea:rmc";
const char* gpx_links_ql_ns = "http://www.qlandkarte.org/xmlschemas/v1.1";
const char* gpx_links_gs_ns = "http://www.groundspeak.com/cache/1/0";
const char* gpx_links_tp1_ns = "http://www.garmin.com/xmlschemas/TrackPointExtension/v1";
const char* gpx_links_gpxdata_ns = "http://www.cluetrust.com/XML/GPXDATA/1/0";
*/

// DOC: Per si vull classificar les activitats com QMapShack"
/*
enum act10_e {
    // activity flags
    eActNone = 0x00000000,
    eActFoot = 0x80000000,
    eActCycle = 0x40000000,
    eActBike = 0x20000000,
    eActCar = 0x10000000,
    eActCable = 0x08000000,
    eActSwim = 0x04000000,
    eActShip = 0x02000000,
    eActAero = 0x01000000,
    eActSki = 0x00800000,
    eActTrain = 0x00400000,
    eActMask = 0xFFC00000  ///< mask for activity flags
};
*/

// DOC: Per portar l'historial de canvis a l'estil de QMapShack
/*
struct history_event_t {
    QDateTime time;
    QString hash;
    QString who = "Pau";
    QString icon;
    QString comment;
    QByteArray data;
};

struct history_t {
    history_t() : histIdxInitial(NOIDX), histIdxCurrent(NOIDX) {}

    void reset() {
        histIdxInitial = NOIDX;
        histIdxCurrent = NOIDX;
        events.clear();
    }

    qint32 histIdxInitial;
    qint32 histIdxCurrent;
    QList<history_event_t> events;
};
*/



