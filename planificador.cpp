
#include "planificador.h"
#include <QListWidget>

Planificador::Planificador(QWidget *parent)
    : QDockWidget{parent}
{

    QListWidget *zonaNW = new QListWidget;
    QListWidget *zonaNE = new QListWidget;
    QListWidget *zonaS = new QListWidget;
    QSplitter *splV = new QSplitter;
    QSplitter *splH = new QSplitter;

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

}
