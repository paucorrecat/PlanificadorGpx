
#include "planificador.h"
#include "fitxergpx.h"
#include <QListWidget>

Planificador::Planificador(QWidget *parent)
    : QDockWidget{parent}
{

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
    dades = new FitxerGpx;

}
