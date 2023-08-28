#ifndef FITXERGPX_H
#define FITXERGPX_H

// #include "data.h" Es per GPXSee
#include <QDomDocument>
#include <QString>
#include <QObject>
#include <QUrl>
#include "g_Projecte.h"
#include "g_Wpt.h"

#define NOIDX -1

/*
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



class FitxerGpx
{
public:
    //FitxerGpx(QString _NomFitxer);
    FitxerGpx();

  //  Data *dades; Això és de GPXSee
    QString NomFitxer;
    metadata_t metadata;

    void Llegir(QString _NomFitxer);
    void Guardar(QString _NomFitxer);

    // Polimorfisme de readXML
    void readXml(const QDomNode& xml, const QString& tag, qint32& value);
    void readXml(const QDomNode& xml, const QString& tag, double& value);
    void readXml(const QDomNode& xml, const QString& tag, act10_e& value);
    template <typename T>
    void readXml(const QDomNode& xml, const QString& tag, T& value);
    void readXml(const QDomNode& xml, const QString& tag, QString& value);
    void readXml(const QDomNode& xml, const QString& tag, QString& value, bool& isHtml);
    void readXml(const QDomNode& xml, const QString& tag, QDateTime& value);
    void readXml(const QDomNode& xml, const QString& tag, QList<link_t>& l);
    void readXml(const QDomNode& xml, history_t& history);
    void readXml(const QDomNode& xml, const QString& tag, QPoint& offsetBubble, quint32& widthBubble) ;

    void readTrk(const QDomNode& xml, gTrk& trk);
    void readTrkpt(const QDomNode& xml,  gTrkpt &trkpt);
    void readWpt(const QDomNode& xml, gWpt &wpt);

    void readMetadata(const QDomNode& xml, metadata_t& metadata);
    QDateTime parseTimestamp(const QString& timetext, int &tzoffset);

    gProjecte getProjecte();
    void setProjecte(gProjecte Proj);

private:
    gProjecte project;

};




#endif // FITXERGPX_H
