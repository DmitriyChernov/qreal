#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtXml/QDomNodeList>

namespace userAction {

class FromXmlToScript : public QObject
{
	Q_OBJECT

public:
	FromXmlToScript();

public slots:
	void generateScript(QString const &xml);

private:
	QString generateMouseCommand(QString const &action, QString const &button, QString const &var) const;
	//QString const findPithyParent(QDomNodeList const &parents) const;
	int findPithyParent(QDomNodeList const &parents) const;

	//QMap draggableElements;

	QString mMousePressRecieverName;
	QString mActiveWindow;
	QString mDraggingElement;

	int mSceneElementVariables;
	bool mIsDragFromPalette;
};
}
