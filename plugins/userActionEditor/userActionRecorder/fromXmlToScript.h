#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtXml/QDomNodeList>

#include <qrutils/outFile.h>

namespace userAction {

class FromXmlToScript : public QObject
{
	Q_OBJECT

public:
	FromXmlToScript();

public slots:
	void generateScript(QString const &xml);

private:
	QString generateMouseAction(QString const &action, QString const &button, QString const &reciever);
	QString generateMouseCommand(QString const &action, QString const &button, QString const &var) const;
	QString generateDragCommand(QString const &id, QString const &var, QString const &xcoord, QString const &ycoord) const;

	int findPithyParent(QDomNodeList const &parents) const;

	//QMap draggableElements;

	QString mMousePressRecieverName;
	QString mActiveWindow;
	QString mDraggingElement;

	int mSceneElementVariables;
	bool mIsDragFromPalette;
};
}
