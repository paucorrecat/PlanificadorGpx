QT       += core gui gui-private xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GPXSee/address.cpp \
    GPXSee/common/coordinates.cpp \
    GPXSee/common/rectc.cpp \
    GPXSee/data.cpp \
    GPXSee/dem.cpp \
    GPXSee/gpxparser.cpp \
    GPXSee/path.cpp \
    GPXSee/route.cpp \
    GPXSee/track.cpp \
    GPXSee/waypoint.cpp \
    arbreestructura.cpp \
    fitxergpx.cpp \
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
    GPXSee/address.h \
    GPXSee/area.h \
    GPXSee/common/coordinates.h \
    GPXSee/common/hash.h \
    GPXSee/common/polygon.h \
    GPXSee/common/rectc.h \
    GPXSee/common/wgs84.h \
    GPXSee/data.h \
    GPXSee/dem.h \
    GPXSee/gpxparser.h \
    GPXSee/graph.h \
    GPXSee/link.h \
    GPXSee/parser.h \
    GPXSee/path.h \
    GPXSee/route.h \
    GPXSee/routedata.h \
    GPXSee/style.h \
    GPXSee/track.h \
    GPXSee/trackdata.h \
    GPXSee/trackpoint.h \
    GPXSee/waypoint.h \
    arbreestructura.h \
    config.h \
    fitxergpx.h \
    g_Projecte.h \
    g_Rte.h \
    g_Trk.h \
    g_Trkpt.h \
    g_Trkseg.h \
    g_Wpt.h \
    mainwindow.h \
    planificador.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += GPXSee

TRANSLATIONS += \
    PlanificadorGpx_ca_ES.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
