#include "fitxergpx.h"
#include <QFileDialog>
#include <QString>
#include <QObject>
#include "g_Projecte.h"
#include "g_Wpt.h"
#include "QRegularExpression"

void FitxerGpx::readXml(const QDomNode& xml, const QString& tag, qint32& value) {
    if (xml.namedItem(tag).isElement()) {
        bool ok = false;
        qint32 tmp = xml.namedItem(tag).toElement().text().toInt(&ok);
        if (!ok) {
            tmp = qRound(xml.namedItem(tag).toElement().text().toDouble(&ok));
        }
        if (ok) {
            value = tmp;
        }
    }
}

void FitxerGpx::readXml(const QDomNode& xml, const QString& tag, double& value) {
    if (xml.namedItem(tag).isElement()) {
        bool ok = false;
        double tmp = xml.namedItem(tag).toElement().text().toDouble(&ok);
        if (!ok) {
            tmp = qRound(xml.namedItem(tag).toElement().text().toDouble(&ok));
        }
        if (ok) {
            value = tmp;
        }
    }
}

void FitxerGpx::readXml(const QDomNode& xml, const QString& tag, act10_e& value) {
    if (xml.namedItem(tag).isElement()) {
        bool ok = false;
        qint32 tmp = xml.namedItem(tag).toElement().text().toInt(&ok);
        if (!ok) {
            value = act10_e::eActNone;
        } else {
            value = act10_e(tmp);
        }
    }
}

template <typename T>
void FitxerGpx::readXml(const QDomNode& xml, const QString& tag, T& value) {
    if (xml.namedItem(tag).isElement()) {
        bool ok = false;
        T tmp;

        if (std::is_same<T, quint32>::value) {
            tmp = xml.namedItem(tag).toElement().text().toUInt(&ok);
        } else if (std::is_same<T, quint64>::value) {
            tmp = xml.namedItem(tag).toElement().text().toULongLong(&ok);
        } else if (std::is_same<T, qreal>::value) {
            tmp = xml.namedItem(tag).toElement().text().toDouble(&ok);
        } else if (std::is_same<T, bool>::value) {
            tmp = xml.namedItem(tag).toElement().text().toInt(&ok);
        }

        if (ok) {
            value = tmp;
        }
    }
}

void FitxerGpx::readXml(const QDomNode& xml, const QString& tag, QString& value) {
    if (xml.namedItem(tag).isElement()) {
        value = xml.namedItem(tag).toElement().text();
    }
}

void FitxerGpx::readXml(const QDomNode& xml, const QString& tag, QString& value, bool& isHtml) {
    if (xml.namedItem(tag).isElement()) {
        const QDomNamedNodeMap& attr = xml.namedItem(tag).toElement().attributes();
        isHtml = (attr.namedItem("html").nodeValue().toLocal8Bit().toLower() == "true");
        value = xml.namedItem(tag).toElement().text();
    }
}

void FitxerGpx::readXml(const QDomNode& xml, const QString& tag, QDateTime& value) {
    int tzoffset;
    if (xml.namedItem(tag).isElement()) {
        QString time = xml.namedItem(tag).toElement().text();
        value = parseTimestamp(time, tzoffset);
    }
}

void FitxerGpx::readXml(const QDomNode& xml, const QString& tag, QList<link_t>& l) {
    if (xml.namedItem(tag).isElement()) {
        const QDomNodeList& links = xml.toElement().elementsByTagName(tag);
        int N = links.count();
        for (int n = 0; n < N; ++n) {
            const QDomNode& link = links.item(n);

            if (xml != link.parentNode()) {
                continue;
            }

            link_t tmp;
            tmp.uri.setUrl(link.attributes().namedItem("href").nodeValue());
            readXml(link, "text", tmp.text);
            readXml(link, "type", tmp.type);

            l << tmp;
        }
    }
}

void FitxerGpx::readXml(const QDomNode& xml, history_t& history) {
    if (xml.namedItem("ql:history").isElement()) {
        const QDomElement& xmlHistory = xml.namedItem("ql:history").toElement();

        const QDomNodeList& xmlEntries = xmlHistory.elementsByTagName("ql:event");
        for (int n = 0; n < xmlEntries.count(); ++n) {
            const QDomNode& xmlEntry = xmlEntries.item(n);
            history_event_t entry;
            readXml(xmlEntry, "ql:icon", entry.icon);
            readXml(xmlEntry, "ql:time", entry.time);
            readXml(xmlEntry, "ql:comment", entry.comment);

            history.events << entry;
        }

        history.histIdxInitial = history.events.size() - 1;
        history.histIdxCurrent = history.histIdxInitial;
    }
}

void FitxerGpx::readXml(const QDomNode& xml, const QString& tag, QPoint& offsetBubble, quint32& widthBubble) {
    if (xml.namedItem(tag).isElement()) {
        const QDomElement& xmlBubble = xml.namedItem(tag).toElement();
        int x = xmlBubble.attributes().namedItem("xoff").nodeValue().toInt();
        int y = xmlBubble.attributes().namedItem("yoff").nodeValue().toInt();
        offsetBubble = QPoint(x, y);
        widthBubble = xmlBubble.attributes().namedItem("width").nodeValue().toInt();
    }
}

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

            /* De moment sense extensions
            const QDomNode& ext = xmlTrkpt.namedItem("extensions");
            if (ext.isElement()) {
                readXml(ext, "ql:flags", trkpt.flags);
                readXml(ext, "ql:activity", trkpt.activity);
                trkpt.sanitizeFlags();
                readXml(ext, trkpt.extensions);
            }
            */
        }
    }
}

void FitxerGpx::readTrkpt(const QDomNode& xml,  gTrkpt &trkpt) {
    const QDomNamedNodeMap& attr = xml.attributes();
    trkpt.lat = attr.namedItem("lat").nodeValue().toDouble();
    trkpt.lon = attr.namedItem("lon").nodeValue().toDouble();

    readXml(xml, "ele", trkpt.ele);
    readXml(xml, "time", trkpt.time);
}




void FitxerGpx::readWpt(const QDomNode& xml, gWpt &wpt) {
    const QDomNamedNodeMap& attr = xml.attributes();
    wpt.lat = attr.namedItem("lat").nodeValue().toDouble();
    wpt.lon = attr.namedItem("lon").nodeValue().toDouble();

    readXml(xml, "ele", wpt.ele);
    readXml(xml, "time", wpt.time);
    readXml(xml, "magvar", wpt.magvar);
    readXml(xml, "geoidheight", wpt.geoidheight);
    readXml(xml, "name", wpt.name);
    readXml(xml, "cmt", wpt.cmt);
    readXml(xml, "desc", wpt.desc);
    readXml(xml, "src", wpt.src);
    readXml(xml, "link", wpt.links);
    readXml(xml, "sym", wpt.sym);
    readXml(xml, "type", wpt.type);
    readXml(xml, "fix", wpt.fix);
    readXml(xml, "sat", wpt.sat);
    readXml(xml, "hdop", wpt.hdop);
    readXml(xml, "vdop", wpt.vdop);
    readXml(xml, "pdop", wpt.pdop);
    readXml(xml, "ageofdgpsdata", wpt.ageofdgpsdata);
    readXml(xml, "dgpsid", wpt.dgpsid);

    // some GPX 1.0 backward compatibility
    QString url;
    readXml(xml, "url", url);
    if (!url.isEmpty()) {
        link_t link;
        link.uri.setUrl(url);
        readXml(xml, "urlname", link.text);

        wpt.links << link;
    }
}



void FitxerGpx::setProjecte(gProjecte Proj) {
    project = Proj;
}

gProjecte FitxerGpx::getProjecte() {
    return project;
}


void FitxerGpx::readMetadata(const QDomNode& xml, metadata_t& metadata) {
    readXml(xml, "name", metadata.name);
    readXml(xml, "desc", metadata.desc);

    const QDomNode& xmlAuthor = xml.namedItem("author");
    if (xmlAuthor.isElement()) {
        readXml(xml, "name", metadata.author.name);

        const QDomNode& xmlEmail = xmlAuthor.namedItem("email");
        if (xmlEmail.isElement()) {
            const QDomNamedNodeMap& attr = xmlEmail.attributes();
            metadata.author.id = attr.namedItem("id").nodeValue();
            metadata.author.domain = attr.namedItem("domain").nodeValue();
        }

        const QDomNode& xmlLink = xmlAuthor.namedItem("link");
        if (xmlLink.isElement()) {
            metadata.author.link.uri.setUrl(xmlLink.attributes().namedItem("href").nodeValue());
            readXml(xmlLink, "text", metadata.author.link.text);
            readXml(xmlLink, "type", metadata.author.link.type);
        }
    }

    const QDomNode& xmlCopyright = xml.namedItem("copyright");
    if (xmlCopyright.isElement()) {
        metadata.copyright.author = xmlCopyright.attributes().namedItem("author").nodeValue();
        readXml(xmlCopyright, "year", metadata.copyright.year);
        readXml(xmlCopyright, "license", metadata.copyright.license);
    }

    readXml(xml, "link", metadata.links);
    readXml(xml, "time", metadata.time);
    readXml(xml, "keywords", metadata.keywords);

    const QDomNode& xmlBounds = xml.namedItem("bounds");
    if (xmlBounds.isElement()) {
        const QDomNamedNodeMap& attr = xmlBounds.attributes();
        metadata.bounds.setLeft(attr.namedItem("minlon").nodeValue().toDouble());
        metadata.bounds.setTop(attr.namedItem("maxlat").nodeValue().toDouble());
        metadata.bounds.setRight(attr.namedItem("maxlon").nodeValue().toDouble());
        metadata.bounds.setBottom(attr.namedItem("minlat").nodeValue().toDouble());
    }
}


QDateTime FitxerGpx::parseTimestamp(const QString& timetext, int& tzoffset) {
    const QRegularExpression tzRE("[-+]\\d\\d:\\d\\d$");
//    QRegularExpression tzRE;
//    tzRe.set = "[-+]\\d\\d:\\d\\d$";
    int i;

    tzoffset = 0;
    bool applyTzOffset = false;

    QString format = "yyyy-MM-dd'T'hh:mm:ss";

    i = timetext.indexOf(".");
    if (i != NOIDX) {
        if (timetext[i + 1] == '0') {
            format += ".zzz";
        } else {
            format += ".z";
        }
    }

    QRegularExpressionMatch match = tzRE.match(timetext);
    // trailing "Z" explicitly declares the timestamp to be UTC
    if (timetext.indexOf("Z") != NOIDX) {
        format += "'Z'";
        applyTzOffset = true;
    }

    else if ( match.hasMatch() ) {
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


FitxerGpx::FitxerGpx() {
}

void FitxerGpx::Llegir(QString _NomFitxer)
{

  //  bool tryUnknown = true;
    NomFitxer=_NomFitxer;

   // dades = new Data(_NomFitxer, tryUnknown);


    QFile file(_NomFitxer);
    gProjecte project;
    gTrk *trk;

    QDomDocument xml;
    QString msg;
    int line;
    int column;

    if (!file.open(QIODevice::ReadOnly)) {
        throw QObject::tr("Failed to open %1").arg(_NomFitxer);
    }

    if (!xml.setContent(&file, false, &msg, &line, &column)) {
        file.close();
        throw QObject::tr("Failed to read: %1\nline %2, column %3:\n %4").arg(_NomFitxer).arg(line).arg(column).arg(msg);
    }
    file.close();

    int N;
    QDomElement xmlGpx = xml.documentElement();
    if (xmlGpx.tagName() != "gpx") {
        throw QObject::tr("Not a GPX file: %1").arg(_NomFitxer);
    }

    /* De moment passo

    // Read all attributes and find any registrations for actually known extensions.
    // This is used to properly detect valid .gpx files using uncommon namespaces.
    QDomNamedNodeMap attributes = xmlGpx.attributes();
    for (int i = 0; i < attributes.size(); ++i) {
        const QString xmlns("xmlns");
        QDomAttr att = attributes.item(i).toAttr();

        if (att.name().startsWith(xmlns + ":")) {
            QString ns = att.name().mid(xmlns.length() + 1);

            if (att.value() == gpxtpx_ns) {
                CKnownExtension::initGarminTPXv1(IUnit::self(), ns);
            } else if (att.value() == gpxdata_ns) {
                CKnownExtension::initClueTrustTPXv1(IUnit::self(), ns);
            }
        }
    }
    */

    /*Extensions que no connec

    const QDomElement& xmlExtension = xmlGpx.namedItem("extensions").toElement();
    if (xmlExtension.namedItem("ql:key").isElement()) {
        project->key = xmlExtension.namedItem("ql:key").toElement().text();
    }

    if (xmlExtension.namedItem("ql:sortingRoadbook").isElement()) {
        project->sortingRoadbook =
            sorting_roadbook_e(xmlExtension.namedItem("ql:sortingRoadbook").toElement().text().toInt());
    }

    if (xmlExtension.namedItem("ql:sortingFolder").isElement()) {
        project->sortingFolder = sorting_folder_e(xmlExtension.namedItem("ql:sortingFolder").toElement().text().toInt());
    }

    if (xmlExtension.namedItem("ql:correlation").isElement()) {
        project->noCorrelation = bool(xmlExtension.namedItem("ql:correlation").toElement().text().toInt() == 0);
    }

    if (xmlExtension.namedItem("ql:invalidDataOk").isElement()) {
        project->invalidDataOk = bool(xmlExtension.namedItem("ql:invalidDataOk").toElement().text().toInt() != 0);
    }

    */

    const QDomNode& xmlMetadata = xmlGpx.namedItem("metadata");
    if (xmlMetadata.isElement()) {
        readMetadata(xmlMetadata, project.metadata);
    }

    /** @note   If you change the order of the item types read you have to
              take care of the order enforced in IGisItem().
   */
    const QDomNodeList& xmlTrks = xmlGpx.elementsByTagName("trk");
    N = xmlTrks.count();
    for (int n = 0; n < N; ++n) {
        trk = new gTrk;
        project.LlTrk.append(*trk);
        const QDomNode& xmlTrk = xmlTrks.item(n);
        readTrk(xmlTrk, *trk);
    }

    /* TODO de moment que no llegeixi més que tracks
     *
    const QDomNodeList& xmlRtes = xmlGpx.elementsByTagName("rte");
    N = xmlRtes.count();
    for (int n = 0; n < N; ++n) {
        const QDomNode& xmlRte = xmlRtes.item(n);
        new CGisItemRte(xmlRte, project);
    }

    const QDomNodeList& xmlWpts = xmlGpx.elementsByTagName("wpt");
    N = xmlWpts.count();
    for (int n = 0; n < N; ++n) {
        const QDomNode& xmlWpt = xmlWpts.item(n);
        CGisItemWpt* wpt = new CGisItemWpt(xmlWpt, project);

        /*
        Special care for waypoints stored on Garmin devices. Images attached
        to the waypoint are stored in the file system of the device and written
        as links to the waypoint. Let the device object take care of this.

        IDevice* device = dynamic_cast<IDevice*>(project->parent());
        if (device) {
            device->loadImages(*wpt);
        }

    }
    */
    /* TODO de moment res
    const QDomNodeList& xmlAreas = xmlExtension.elementsByTagName("ql:area");
    N = xmlAreas.count();
    for (int n = 0; n < N; ++n) {
        const QDomNode& xmlArea = xmlAreas.item(n);
        new CGisItemOvlArea(xmlArea, project);
    }

    project->sortItems();
    project->setupName(QFileInfo(filename).completeBaseName().replace("_", " "));
    project->setToolTip(CGisListWks::eColumnName, project->getInfo());
    project->valid = true;

    */




}
