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


    // Per si és un "llegir" sobre un que ja s'havia llegit
    // Ho posa tot a 0
    /* No cal
    NomFitxer = "";
    Carpeta = "";
    NomBaseFitxer = "";
    project=PrjtBuit;
    */

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
        // TODO: Acabar de llegir matadata
        /*
        QDomElement xmlAuth = xmlMetadata.firstChildElement("author");
        if (xmlAuth.isElement()) {
            project.metadata.author=xmlAuth.firstChildElement("name").text();
            QDomElement xmllnk = xmlMetadata.firstChildElement("link");
            if (xmllnk.isElement()) {
                project.metadata.author=xmlAuth.firstChildElement("name").text();
                project.metadata.linkauthor.uri = xmllnk.firstChildElement("href").text();

        }
        */

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
    gTrkpt trkpt;
    trkpt.ele =xml.firstChildElement("ele").text().toInt();
    trkpt.lat =xml.attribute("lat").toDouble();
    trkpt.lon =xml.attribute("lon").toDouble();
    return trkpt;
}

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

