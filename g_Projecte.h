#ifndef G_PROJECTE_H
#define G_PROJECTE_H

#include <QList>
#include <QDomDocument>
#include <QDateTime>
#include <QRectF>
#include "g_general.h"
#include "g_Trk.h"
#include "g_Wpt.h"
#include "g_Rte.h"

struct person_t {
    QString name;
    QString id;
    QString domain;
    link_t link;
};

struct copyright_t {
    QString author;
    QString year;
    QString license;
};


class gProjecte
{
public:
    gProjecte();
    // Característiques GPX
    struct gpx_t  {
        QString xmlns; //XML namespace
        QString xmlns_xsi; //XML namespace prefix (Xml Schema Instance)
        QString xsi_schemaLocation; //XML namespace
        QString creator; // El que ha fet el fitxer gpx, no l'autor del track
        QString version; //Suposo que la versió de XML
    } gpx;
    // Fitxer
    struct fitxer_t {
        QString NomFitxer;
        QString Carpeta;
        QString NomBaseFitxer;
    } fitxer;


    QString Nom;
    struct metadata_t {
        QString author;
        link_t linkauthor;
        link_t link;
        QDateTime time;
        QRectF bounds;
    } metadata;

    QList<gTrk> LlTrk;
    QList<gWpt> LlWpt;
    QList<gRte> LlRte;
};

#endif // G_PROJECTE_H

// DOC: Dades complertes metadata
/* Versió complerta que de moment no usaré
struct metadata_t {
    metadata_t() : time(QDateTime::currentDateTimeUtc()) {}
    QString name;
    QString desc;
    person_t author;
    copyright_t copyright;
    QList<link_t> links;
    QDateTime time;
    QString keywords;
    QRectF bounds;
    // -- all gpx tags - stop
    QMap<QString, QVariant> extensions;
};
*/
