
#include "planificador.h"
#include "fitxergpx.h"
#include <QListWidget>
#include <qfiledialog.h>
#include <QSettings>
#include "config.h"
#include "g_Projecte.h"

Planificador::Planificador(QWidget *parent)
    : QDockWidget{parent}
{
    QFileInfo fitxer;
    FitxerGpx fitxergpx;


    zonaNW = new QListWidget;
    zonaNE = new QListWidget;
    zonaS = new QListWidget;
    splV = new QSplitter;
    splH = new QSplitter;

    zonaNE->setBackgroundRole(QPalette::Text);

    splH->setOrientation(Qt::Horizontal);
    splH->addWidget(zonaNW);
    splH->addWidget(zonaNE);
    splV->setOrientation(Qt::Vertical);
    splV->addWidget(splH);
    splV->addWidget(zonaS);

    /* Per ajustar mesures, de moment no ho usaré

    widget1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    widget2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 1);
    */

    this->setWidget(splV);

    QSettings settings(Config::Org,Config::App);
    QString path = settings.value (Config::UltDir,QDir::currentPath()).toString();

    NomFitxer = QFileDialog::getOpenFileName(this,
                         tr("Obre track"), path, tr("Track (*.gpx)"));
    if (NomFitxer.isEmpty()) {
        this->close();
        return;
    }
    fitxer = QFileInfo(NomFitxer);
    if (QString::compare(path,fitxer.absoluteFilePath())!=0) {
        settings.setValue(Config::UltDir,fitxer.absoluteFilePath());
    }


    fitxergpx.Llegir(NomFitxer);

//    MostraDades();

}


void Planificador::MostraDades() {
    int NumTracks;
    int n, m;
    gProjecte  Proj;
    gTrk *Tr;
  // Track TrackAct;

/*
    NumTracks = fitxerGpx->dades->tracks().count();
    zonaNW->addItem("Número de tracks = " + QString::number(NumTracks));
    for (n=0;n<NumTracks;n++) {
        Tr = new gTrk;
        Tr->Nom = fitxerGpx->dades->tracks().at(n).name();
        Proj.LlTrk.append(*Tr);
        zonaNW->addItem("   - Track " + QString::number(n+1) + " " + Tr->Nom);
        for (m=0 ; m<fitxerGpx->dades-> )
//        TrackAct = fitxerGpx->dades->tracks();
    };

*/


}
