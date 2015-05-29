TARGET = user-action-generator

include(../../../global.pri)

QT += widgets

TEMPLATE = lib
CONFIG += plugin

DESTDIR = $$DESTDIR/plugins/tools/userAction/

includes(plugins/robots/generators/generatorBase \
	qrtext \
)

links(qrkernel qslog qrutils qrrepo qscintilla2 robots-generator-base)

HEADERS += \
	$$PWD/simpleGenerators/hintMessageGenerator.h \
	$$PWD/generatorPlugin.h \
	$$PWD/masterGenerator.h \
	$$PWD/factory.h \
	$$PWD/customizer.h \
	$$PWD/simpleGenerators/arrowGenerator.h \
	$$PWD/simpleGenerators/dragPaletteElementGenerator.h \
	$$PWD/simpleGenerators/drawLinkGenerator.h \
	$$PWD/simpleGenerators/waitGenerator.h \
	$$PWD/simpleGenerators/changeWindowGenerator.h \
	$$PWD/simpleGenerators/pickComboboxGenerator.h \
	$$PWD/simpleGenerators/scrollGenerator.h \
	$$PWD/simpleGenerators/cursorMoveToGenerator.h \
	$$PWD/simpleGenerators/typeGenerator.h \
	$$PWD/simpleGenerators/getWidgetGenerator.h \
	$$PWD/simpleGenerators/getPropertyGenerator.h \
	$$PWD/simpleGenerators/getPropertyRectangleGenerator.h \
	$$PWD/simpleGenerators/recordGenerator.h \
	$$PWD/simpleGenerators/mouseButtonActionGenerator.h \
	$$PWD/simpleGenerators/getDraggableElementGenerator.h

SOURCES += \
	$$PWD/simpleGenerators/hintMessageGenerator.cpp \
	$$PWD/generatorPlugin.cpp \
	$$PWD/masterGenerator.cpp \
	$$PWD/factory.cpp \
	$$PWD/customizer.cpp \
	$$PWD/simpleGenerators/arrowGenerator.cpp \
	$$PWD/simpleGenerators/dragPaletteElementGenerator.cpp \
	$$PWD/simpleGenerators/drawLinkGenerator.cpp \
	$$PWD/simpleGenerators/waitGenerator.cpp \
	$$PWD/simpleGenerators/changeWindowGenerator.cpp \
	$$PWD/simpleGenerators/pickComboboxGenerator.cpp \
	$$PWD/simpleGenerators/scrollGenerator.cpp \
	$$PWD/simpleGenerators/cursorMoveToGenerator.cpp \
	$$PWD/simpleGenerators/typeGenerator.cpp \
	$$PWD/simpleGenerators/getWidgetGenerator.cpp \
	$$PWD/simpleGenerators/getPropertyGenerator.cpp \
	$$PWD/simpleGenerators/getPropertyRectangleGenerator.cpp \
	$$PWD/simpleGenerators/recordGenerator.cpp \
	$$PWD/simpleGenerators/mouseButtonActionGenerator.cpp \
	$$PWD/simpleGenerators/getDraggableElementGenerator.cpp

RESOURCES = \
	$$PWD/templates.qrc \
    images.qrc
