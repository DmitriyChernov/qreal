TARGET = robots-trik-f-sharp-generator

include(../../../../../global.pri)

QT += widgets network

TEMPLATE = lib
CONFIG += plugin

copyToDestdir($$PWD/lib/Trik.Core.dll)

DESTDIR = $$DESTDIR/plugins/tools/kitPlugins/

includes(plugins/robots/generators/trik/trikGeneratorBase \
		plugins/robots/generators/generatorBase \
		plugins/robots/common/kitBase \
		plugins/robots/utils \
		qrtext \
)

links(qrkernel qslog qrutils qrrepo qscintilla2 robots-generator-base robots-trik-generator-base robots-utils \
		qrgui-preferences-dialog robots-kit-base \
)

TRANSLATIONS = $$PWD/../../../../../qrtranslations/ru/plugins/robots/trikFSharpGenerator_ru.ts

HEADERS += \
	$$PWD/trikFSharpGeneratorPlugin.h \
	$$PWD/trikFSharpMasterGenerator.h \
	$$PWD/trikFSharpAdditionalPreferences.h \
	$$PWD/trikFSharpControlFlowValidator.h \

SOURCES += \
	$$PWD/trikFSharpGeneratorPlugin.cpp \
	$$PWD/trikFSharpMasterGenerator.cpp \
	$$PWD/trikFSharpAdditionalPreferences.cpp \
	$$PWD/trikFSharpControlFlowValidator.cpp \

FORMS += \
	$$PWD/trikFSharpAdditionalPreferences.ui \

RESOURCES = \
	$$PWD/trikFSharpGenerator.qrc \
	$$PWD/templates.qrc \
