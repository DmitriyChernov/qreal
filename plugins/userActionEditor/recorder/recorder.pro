include(../../../global.pri)

QT += xml widgets core

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
	$$PWD/fromXmlToScript.h\
	$$PWD/recordShell.h \

SOURCES += \
	$$PWD/recorder.cpp \
	$$PWD/recordSign.cpp \
	$$PWD/fromXmlToScript.cpp\
	$$PWD/recordShell.cpp \
