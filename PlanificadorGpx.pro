QT       += core  xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    FitxerGPX.cpp \
    arbreestructura.cpp \
    g_Projecte.cpp \
    g_Rte.cpp \
    g_Trk.cpp \
    g_Trkpt.cpp \
    g_Trkseg.cpp \
    g_Wpt.cpp \
    main.cpp \
    mainwindow.cpp \
    planificador.cpp

HEADERS += \
    FitxerGPX.h \
    arbreestructura.h \
    config.h \
    g_Projecte.h \
    g_Rte.h \
    g_Trk.h \
    g_Trkpt.h \
    g_Trkseg.h \
    g_Wpt.h \
    g_general.h \
    mainwindow.h \
    planificador.h

TRANSLATIONS += \
    PlanificadorGpx_ca_ES.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
