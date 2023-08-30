
#include "planificador.h"
#include "FitxerGPX.h"
#include "arbreestructura.h"
#include <QListWidget>
#include <qfiledialog.h>
#include <QSettings>
#include "config.h"
#include "g_Projecte.h"

Planificador::Planificador(QWidget *parent)
    : QDockWidget{parent}
{
    QFileInfo fitxer;
    //FitxerGpx fitxergpx;
    gProjecte project;


    zonaNW = new ArbreGpx;
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


    fitxerGpx.Llegir(NomFitxer);
    project = fitxerGpx.getProjecte();




    zonaNW->Representa(project);
    MostraDades();


}


void Planificador::MostraDades() {

    gProjecte project;
    project = fitxerGpx.getProjecte();
    zonaNE->addItem("GPX: " + project.Nom);
    zonaNE->addItem("  GPX:Creator " + project.gpx.creator);
    //zonaNE->addItem(projecte.)
}
