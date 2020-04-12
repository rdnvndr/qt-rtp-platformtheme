TARGET = rtptheme
CONFIG += plugin
TEMPLATE = lib

PLUGIN_TYPE = platformthemes
PLUGIN_EXTENDS = -
PLUGIN_CLASS_NAME = RTPThemePlugin

QT += gui-private

HEADERS += \
    rtptheme.h

SOURCES += \
        main.cpp \
        rtptheme.cpp
