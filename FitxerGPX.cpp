#include "FitxerGPX.h"
#include <QFileDialog>
#include <QString>
#include "g_Projecte.h"
//#include "g_Wpt.h"


FitxerGpx::FitxerGpx() {
}

void FitxerGpx::setProjecte(gProjecte Proj) {
    Prjct = Proj;
}

gProjecte FitxerGpx::getProjecte() {
    return Prjct;
}


void FitxerGpx::Llegir(QString _NomFitxer)
{

    QFile file(_NomFitxer);
    QFileInfo info(_NomFitxer);

    gProjecte project;
    //gTrk *trk;

    QDomDocument xml;

    QString errorStr;
    int errorLine;
    int errorColumn;


    // Llegir el xml
    if (!file.open(QIODevice::ReadOnly)) {
        throw QObject::tr("Ha fallat obrint %1").arg(_NomFitxer);
    }

    if (!xml.setContent(&file, false, &errorStr, &errorLine, &errorColumn)) {
        file.close();
        throw QObject::tr("Ha fallat al llegir:: %1\nlinia %2, columna %3:\n %4").arg(_NomFitxer).arg(errorLine).arg(errorColumn).arg(errorStr);
    }
    file.close();

    // Info del fitxer
    NomFitxer = info.fileName();
    Carpeta = info.absolutePath();
    NomBaseFitxer = info.baseName();
    project.fitxer.NomFitxer = NomFitxer;
    project.fitxer.Carpeta=Carpeta;
    project.fitxer.NomBaseFitxer=NomBaseFitxer;


    QDomElement xmlGpx = xml.documentElement();
    if (xmlGpx.tagName() != "gpx") {
        throw QObject::tr("No és un fitxer GPX: %1").arg(_NomFitxer);
    }

    //Atributs
    project.gpx.xmlns =xmlGpx.attribute("xmlns");
    project.gpx.xmlns_xsi =xmlGpx.attribute("xmlns:xsi");
    project.gpx.xsi_schemaLocation =xmlGpx.attribute("xsi:schemaLocation");
    project.gpx.creator =xmlGpx.attribute("creator");
    project.gpx.version =xmlGpx.attribute("version");

    //Metadata
    const QDomNode& xmlMetadata = xmlGpx.namedItem("metadata");
    if (xmlMetadata.isElement()) {
        project.Nom = xmlMetadata.firstChildElement("name").text();
        QDomElement xmlAuth = xmlMetadata.firstChildElement("author");
        if (xmlAuth.isElement()) {
            project.metadata.author=xmlAuth.firstChildElement("name").text();
            QDomElement xmllnk = xmlMetadata.firstChildElement("link");
            if (xmllnk.isElement()) {
                project.metadata.linkauthor.uri = xmllnk.attribute("href");
                project.metadata.linkauthor.text=xmllnk.firstChildElement("text").text();
            }
        }
        int tz;
        project.metadata.time = parseTimestamp( xmlMetadata.firstChildElement("time").text(), tz );
        QDomElement xmlbnd = xmlMetadata.firstChildElement("bounds");
        if (xmlbnd.isElement()) {
            project.metadata.bounds.setLeft(xmlbnd.attribute("minlon").toDouble());
            project.metadata.bounds.setRight(xmlbnd.attribute("maxlon").toDouble());
            project.metadata.bounds.setBottom(xmlbnd.attribute("minlat").toDouble());
            project.metadata.bounds.setTop(xmlbnd.attribute("maxlat").toDouble());
        }

    }

    QDomElement child = xmlGpx.firstChildElement("trk");
    while (!child.isNull()) {
        project.LlTrk.append(ll_Trk(child));
        child = child.nextSiblingElement("trk");
    }

    setProjecte(project);

}


gTrk FitxerGpx::ll_Trk(const QDomElement& xml) {
    // TODO: Llegir en nom del track
    gTrk trk;
    trk.name = xml.firstChildElement("name").text();

    QDomElement child = xml.firstChildElement("trkseg");
    while (!child.isNull()) {
        trk.segs.append(ll_Trkseg(child));
        child = child.nextSiblingElement("trkseg");
    }
    return trk;
}

gTrkseg FitxerGpx::ll_Trkseg(const QDomElement& xml) {

    gTrkseg trkseg;
    QDomElement child = xml.firstChildElement("trkpt");
    while (!child.isNull()) {
        trkseg.punts.append(ll_Trkpt(child));
        child = child.nextSiblingElement("trkpt");
    }
    return trkseg;
}

gTrkpt FitxerGpx::ll_Trkpt(const QDomElement& xml) {
    // TODO: Llegir el time del trkpt
    int tz; // Per històries del us horari
    gTrkpt trkpt;
    trkpt.ele =xml.firstChildElement("ele").text().toInt();
    trkpt.lat =xml.attribute("lat").toDouble();
    trkpt.lon =xml.attribute("lon").toDouble();
    trkpt.time = parseTimestamp(xml.firstChildElement("time").text(),tz);
    return trkpt;
}

QDateTime FitxerGpx::parseTimestamp(const QString& timetext, int& tzoffset) {
    const QRegularExpression tzRE("[-+]\\d\\d:\\d\\d$");
    int i;

    tzoffset = 0;
    bool applyTzOffset = false;

    QString format = "yyyy-MM-dd'T'hh:mm:ss";

    i = timetext.indexOf(".");
    if (i != -1) {
        if (timetext[i + 1] == '0') {
            format += ".zzz";
        } else {
            format += ".z";
        }
    }

    QRegularExpressionMatch match = tzRE.match(timetext);
    // trailing "Z" explicitly declares the timestamp to be UTC
    if (timetext.indexOf("Z") != -1) {
        format += "'Z'";
        applyTzOffset = true;
    }
    else if ((i = match.capturedStart(0)) != -1) {
        // trailing timezone offset [-+]HH:MM present
        // This does not match the original intentions of the GPX
        // file format but appears to be found occasionally in
        // the wild.  Try our best parsing it.

        // add the literal string to the format so fromString()
        // will succeed
        format += "'";
        format += timetext.right(6);
        format += "'";

        // calculate the offset
        int offsetHours(timetext.mid(i + 1, 2).toUInt());
        int offsetMinutes(timetext.mid(i + 4, 2).toUInt());
        if (timetext[i] == '-') {
            tzoffset = -(60 * offsetHours + offsetMinutes);
        } else {
            tzoffset = 60 * offsetHours + offsetMinutes;
        }
        tzoffset *= 60;  // seconds
        applyTzOffset = true;
    }

    QDateTime datetime = QDateTime::fromString(timetext, format);

    if (applyTzOffset) {
        datetime.setOffsetFromUtc(tzoffset);
    } else {  // if timetext has no 'Z' and no [-+]HH:MM then this is local time then simply switch to UTC without
        // applying any offset
        datetime = datetime.toUTC();
    }

    return datetime;
}
// DOC: Algorisme de QDateTime a QString, tret de QMapShack, que és d'on he tret el de parse
/*
QString FitxerGpx::datetime2string(const QDateTime& time, time_format_e format, const QPointF& pos) {
    QTimeZone tz;

    tz_mode_e tmpMode = (pos != NOPOINTF) ? timeZoneMode : eTZLocal;

    switch (tmpMode) {
    case eTZUtc:
        tz = QTimeZone("UTC");
        break;

    case eTZLocal:
        tz = QTimeZone(QTimeZone::systemTimeZoneId());
        break;

    case eTZAuto:
        tz = QTimeZone(pos2timezone(pos));
        break;

    case eTZSelected:
        tz = QTimeZone(timeZone);
        break;
    }

    QDateTime tmp = time.toTimeZone(tz);

    switch (format) {
    case eTimeFormatLong:
        return tmp.toString(QLocale().dateTimeFormat(useShortFormat ? QLocale::ShortFormat : QLocale::LongFormat));
    case eTimeFormatShort:
        return tmp.toString(QLocale().dateTimeFormat(QLocale::ShortFormat));
    case eTimeFormatIso:
        return tmp.toString(Qt::ISODate);
    }

    return tmp.toString(QLocale().dateTimeFormat(QLocale::LongFormat));
}
*/



// TODO: Llegir tots els atributs del track
/*
readXml(xml, "name", trk.name);
readXml(xml, "cmt", trk.cmt);
readXml(xml, "desc", trk.desc);
readXml(xml, "src", trk.src);
readXml(xml, "link", trk.links);
readXml(xml, "number", trk.number);
readXml(xml, "type", trk.type);
*/



/*
void FitxerGpx::readTrk(const QDomNode& xml, gTrk& trk) {
    gTrkseg *seg;
    gTrkpt *pnt;

    readXml(xml, "name", trk.name);
    readXml(xml, "cmt", trk.cmt);
    readXml(xml, "desc", trk.desc);
    readXml(xml, "src", trk.src);
    readXml(xml, "link", trk.links);
    readXml(xml, "number", trk.number);
    readXml(xml, "type", trk.type);

    const QDomNodeList& trksegs = xml.toElement().elementsByTagName("trkseg");
    int N = trksegs.count();
    //trk.segs.resize(N);
    for (int n = 0; n < N; ++n) {
        const QDomNode& trkseg = trksegs.item(n);
        seg = new gTrkseg;
        trk.segs.append(*seg);

        const QDomNodeList& xmlTrkpts = trkseg.toElement().elementsByTagName("trkpt");
        int M = xmlTrkpts.count();
        //seg.pts.resize(M);
        for (int m = 0; m < M; ++m) {
            pnt = new gTrkpt;
            seg->punts.append(*pnt);
            const QDomNode& xmlTrkpt = xmlTrkpts.item(m);
            readTrkpt(xmlTrkpt, *pnt);

            // De moment sense extensions
            const QDomNode& ext = xmlTrkpt.namedItem("extensions");
            if (ext.isElement()) {
                readXml(ext, "ql:flags", trkpt.flags);
                readXml(ext, "ql:activity", trkpt.activity);
                trkpt.sanitizeFlags();
                readXml(ext, trkpt.extensions);
            }

}
}
}
*/

