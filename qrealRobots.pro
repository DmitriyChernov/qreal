include (qreal.pri)

plugins.file += $$PWD/plugins/robots.pro \

SUBDIRS += \
	$$PWD/plugins/userActionEditor/userActionEditor.pro \

RESOURCES += \
	qrgui/mainwindow/qrgui.qrc
