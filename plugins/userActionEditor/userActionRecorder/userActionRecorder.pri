include(../../../global.pri)

QT += xml widgets

TEMPLATE = lib
CONFIG += plugin

DESTDIR = $$DESTDIR/plugins/tools/

INCLUDEPATH += \
	$$PWD/../../.. \
	$$PWD/../../../qrgui/ \
	$$PWD/../../../qrtext/include/ \

links(qrkernel qrutils qrgui-preferences-dialog qrgui-tool-plugin-interface qrtext)

HEADERS += \
	$$PWD/recorder.h \
	$$PWD/recordSign.h \
	$$PWD/widgetFinder.h \
    $$PWD/blocks/recordBlock.h

SOURCES += \
	$$PWD/recorder.cpp \
	$$PWD/recordSign.cpp \
	$$PWD/widgetFinder.cpp \
    $$PWD/blocks/recordBlock.cpp
