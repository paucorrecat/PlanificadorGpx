#ifndef PLANIFICADOR_H
#define PLANIFICADOR_H

#include <QWidget>
#include <QSplitter>
#include <QDockWidget>
#include <QListWidget>
#include "fitxergpx.h"

class Planificador : public QDockWidget
{
    Q_OBJECT
public:
    explicit Planificador(QWidget *parent = nullptr);

private:
    QListWidget *zonaNW, *zonaNE, *zonaS;
    QSplitter *splV, *splH;

    FitxerGpx  *dades;

signals:

};

#endif // PLANIFICADOR_H
