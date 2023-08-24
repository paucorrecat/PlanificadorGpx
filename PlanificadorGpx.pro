QT       += core gui gui-private

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    address.cpp \
    common/coordinates.cpp \
    common/rectc.cpp \
    data.cpp \
    dem.cpp \
    fitxergpx.cpp \
    gpxparser.cpp \
    main.cpp \
    mainwindow.cpp \
    path.cpp \
    planificador.cpp \
    route.cpp \
    track.cpp \
    waypoint.cpp

HEADERS += \
    address.h \
    area.h \
    common/coordinates.h \
    common/hash.h \
    common/polygon.h \
    common/rectc.h \
    common/wgs84.h \
    data.h \
    dem.h \
    fitxergpx.h \
    gpxparser.h \
    graph.h \
    link.h \
    mainwindow.h \
    parser.h \
    path.h \
    planificador.h \
    route.h \
    routedata.h \
    style.h \
    track.h \
    trackdata.h \
    trackpoint.h \
    waypoint.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    PlanificadorGpx_ca_ES.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
