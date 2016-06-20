TEMPLATE = app
CONFIG += console c++11
QT += qml quick widgets

SOURCES += main.cpp \
    imageprovider.cpp \
    pixelmetricone.cpp \
    pixelmetrictwo.cpp \
    pixelmetricthree.cpp \
    pixelmetricfour.cpp \
    shortestpathsalgorithm.cpp \
    pathsholder.cpp \
    dijkstraalgorithm.cpp \
    legendholder.cpp \
    palette.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    imageprovider.h \
    pixelmetric.h \
    pixelmetricone.h \
    pixelmetrictwo.h \
    pixelmetricthree.h \
    pixelmetricfour.h \
    shortestpathsalgorithm.h \
    pathsholder.h \
    dijkstraalgorithm.h \
    legendholder.h \
    palette.h

