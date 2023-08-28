#ifndef PLANIFICADOR_H
#define PLANIFICADOR_H

#include <QWidget>
#include <QSplitter>
#include <QDockWidget>
#include <QListWidget>
#include "FitxerGPX.h"

class Planificador : public QDockWidget
{
    Q_OBJECT
public:
    explicit Planificador(QWidget *parent = nullptr);

private:
    QListWidget *zonaNW, *zonaNE, *zonaS;
    QSplitter *splV, *splH;

    QString NomFitxer;

    FitxerGpx fitxerGpx();

    void MostraDades();

signals:

};

#endif // PLANIFICADOR_H
