QREAL_XML = userActionEditor.xml
QREAL_XML_DEPENDS =  ../../commonMetamodels/kernelMetamodel.xml ../../commonMetamodels/basicBehaviorsMetamodel.xml ../../commonMetamodels/basicActionsMetamodel.xml
QREAL_EDITOR_PATH = userActionEditor/editor
ROOT = ../../..

include (../../editorsSdk/editorsCommon.pri)

win32 {
	win32:DESTDIR ~= s,/,\,g
	QMAKE_POST_LINK = "cmd /C "xcopy images $$DESTDIR\\images /s /e /q /y /i &&"\&&"
}
else {
	QMAKE_POST_LINK = "cp -r images $$DESTDIR/; "\
}
