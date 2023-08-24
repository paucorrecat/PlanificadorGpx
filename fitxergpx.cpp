#include "fitxergpx.h"
#include <QFileDialog>
#include <QString>

FitxerGpx::FitxerGpx()
{

    QString fileName;
    bool tryUnknown = true;

   // fileName = QFileDialog::getOpenFileName(this,
   //                                         ("Obre GPX"), "/home/pau/Dropbox", ("Fitxers GPX (*.gpx)"));

    fileName =  "/home/pau/Dropbox/Projectes/GPS/PlanificadorGPX VS/Dades prova/2011-03-20-Congost v01.gpx";

    Data data( fileName, tryUnknown);

}
