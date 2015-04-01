HEADERS += \
	$$PWD/outFile.h \
	$$PWD/utilsDeclSpec.h \
	$$PWD/xmlUtils.h \
	$$PWD/watchListWindow.h \
	$$PWD/metamodelGeneratorSupport.h \
	$$PWD/inFile.h \
	$$PWD/scalableItem.h \
	$$PWD/scalableCoordinate.h \
	$$PWD/nameNormalizer.h \
	$$PWD/fileSystemUtils.h \
	$$PWD/stringUtils.h \
	$$PWD/qRealDialog.h \
	$$PWD/qRealFileDialog.h \
	$$PWD/textElider.h\
	$$PWD/virtualKeyboard.h \
	$$PWD/parserErrorReporter.h \
	$$PWD/deleteLaterHelper.h \
	$$PWD/generator/abstractGenerator.h \
	$$PWD/widgetFinder.h

SOURCES += \
	$$PWD/outFile.cpp \
	$$PWD/xmlUtils.cpp \
	$$PWD/watchListWindow.cpp\
	$$PWD/metamodelGeneratorSupport.cpp \
	$$PWD/inFile.cpp \
	$$PWD/scalableItem.cpp \
	$$PWD/scalableCoordinate.cpp \
	$$PWD/nameNormalizer.cpp \
	$$PWD/fileSystemUtils.cpp \
	$$PWD/stringUtils.cpp \
	$$PWD/qRealDialog.cpp \
	$$PWD/qRealFileDialog.cpp \
	$$PWD/textElider.cpp \
	$$PWD/virtualKeyboard.cpp \
	$$PWD/parserErrorReporter.cpp \
	$$PWD/generator/abstractGenerator.cpp \
	$$PWD/widgetFinder.cpp

FORMS += \
	$$PWD/watchListWindow.ui

RESOURCES = $$PWD/qrutils.qrc

TRANSLATIONS = $$PWD/../qrtranslations/ru/qrutils_ru.ts

QT += xml widgets

includes(qrtext)

links(qrkernel qslog qrtext)

DEFINES += QRUTILS_LIBRARY

# Files for parsing of expressions on diagrams
include($$PWD/expressionsParser/expressionsParser.pri)

# Graphical scene framework used in qrgui and plugins
include($$PWD/graphicsUtils/graphicsUtils.pri)

# Stuff connected with graphs and trees
include($$PWD/graphUtils/graphUtils.pri)

# Stuff for running long operations in different modes
include($$PWD/invocationUtils/invocationUtils.pri)

# Math Utils
include($$PWD/mathUtils/mathUtils.pri)

# Real-time plot
include($$PWD/graphicsWatcher/sensorsGraph.pri)

#Plugin managers
include($$PWD/pluginManagers/pluginManagers.pri)

# Tools for interpreting behavioral diagrams
include($$PWD/interpreter/interpreter.pri)
