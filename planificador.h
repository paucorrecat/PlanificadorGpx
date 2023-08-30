#ifndef PLANIFICADOR_H
#define PLANIFICADOR_H

#include <QWidget>
#include <QSplitter>
#include <QDockWidget>
#include <QListWidget>
#include "FitxerGPX.h"
#include "arbreestructura.h"
#include "taulaTrams.h"


class Planificador : public QDockWidget
{
    Q_OBJECT
public:
    explicit Planificador(QWidget *parent = nullptr);

private:
    QListWidget *zonaNE;
    taulaTrams *zonaS;
    ArbreGpx *zonaNW;
    QSplitter *splV, *splH;

    QString NomFitxer;

    FitxerGpx fitxerGpx;

    void MostraDades();

signals:

};

#endif // PLANIFICADOR_H
