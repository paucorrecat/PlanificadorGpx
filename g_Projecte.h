#ifndef G_PROJECTE_H
#define G_PROJECTE_H

#include <QList>
#include <QDomDocument>
#include <QUrl>
#include <QDateTime>
#include <QRectF>
#include "g_Trk.h"

struct link_t {
    QUrl uri;
    QString text;
    QString type;
};

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



class gProjecte
{
public:
    gProjecte();
    QList<gTrk> LlTrk;
    QString Nom;
    QString NomFitxer;

    metadata_t metadata;

    void readMetadata(const QDomNode& xml, metadata_t& metadata);
};

#endif // G_PROJECTE_H
