#ifndef FITXERGPX_H
#define FITXERGPX_H

#include "data.h"

class FitxerGpx
{
public:
    explicit  FitxerGpx();

private:
    char *NomFitxer;

    Data data(const QString &fileName, bool tryUnknown = true);

};

#endif // FITXERGPX_H
