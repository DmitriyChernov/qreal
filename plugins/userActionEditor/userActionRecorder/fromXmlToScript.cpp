#include "fromXmlToScript.h"

#include <QtXml/QDomDocument>

#include <qrutils/outFile.h>

#include <QDebug>

using namespace userAction;
using namespace utils;

FromXmlToScript::FromXmlToScript()
	: QObject()
	, mIsDragFromPalette(false)
	, mSceneElementVariables(0)
{
}

void FromXmlToScript::generateScript(QString const &xml)
{
	QDomDocument events;
	if (events.setContent(xml)) {
		QDomNodeList const eventList = events.elementsByTagName("Event");

		utils::OutFile script("userActions.js");
		mActiveWindow = "mainWindow";
		script() << "var mainWindow = api.ui().mainWindow();\n";
		script() << "api.changeWindow(mainWindow);\n";


		for (int i = 1; i < eventList.size(); i=i+2) {
			QDomElement event = eventList.at(i).toElement();
			QString const recieverName = event.attributes().namedItem("RecieverName").nodeValue();
			QString const recieverType = event.attributes().namedItem("RecieverType").nodeValue();
			QString const eventType = event.attributes().namedItem("Type").nodeValue();
			QString const eventAction = event.attributes().namedItem("Action").nodeValue();

			qDebug()<<recieverName;
			qDebug()<<eventList.at(i-1).toElement().attributes().namedItem("RecieverName").nodeValue();

			if (eventType == "Hint") {
				script() << "api.hints().addHint(\""
							+ event.attributes().namedItem("Message").nodeValue()
							+ "\", 1500, " + mActiveWindow + ");\n";
				script() << "api.wait(1700)\n";
			}

			if (recieverName == "MainWindowUiWindow") {
				if (eventAction == "Release") {
//					script() << "var block"
//								+ mSceneElementVariables
//								+ " = api.palette().dragPaletteElement(\""
//								+ event.attributes().namedItem("Message").nodeValue()
//								+ "\", 1500, " + mActiveWindow + ");\n";
					mIsDragFromPalette = false;
				}

				continue;
			} else if (recieverName != "" && recieverType != "") {
				script() << "var "
						+ recieverName
						+ " = api.ui().widget(\""
						+ recieverType + "\", \""
						+ recieverName + "\");\n";
				if (eventType == "Mouse") {
					if (eventAction == "Press") {
						mMousePressRecieverName = recieverName;
						script() << "api.cursor().moveTo(" + recieverName + ", 500)\n";
					} else if (eventAction == "Release" && recieverName != mMousePressRecieverName) {
						script() << "api.cursor().moveTo(" + recieverName + ", 500);\n";
					}
					script() << generateMouseCommand(eventAction
							, event.attributes().namedItem("Button").nodeValue()
							, recieverName);
				}
			} else {
				QDomNodeList const parentList = event.elementsByTagName("Parent");
				int const pithyParent = findPithyParent(parentList);

				if (pithyParent == -1) {
					continue;
				} else {
					QDomElement const parent = parentList.at(pithyParent).toElement();
					QString const objectName = parent.attributes().namedItem("ObjectName").nodeValue();
					QString const objectType = parent.attributes().namedItem("Type").nodeValue();

					if (objectType == "qReal::gui::DraggableElement") {
						mDraggingElement = objectName;
						mIsDragFromPalette = true;
					}
				}
			}

			QDomElement eventCatchedByWindow = eventList.at(i+1).toElement();
			if (eventCatchedByWindow.attributes().namedItem("RecieverName").nodeValue() != mActiveWindow) {
				/// TODO : change window, when window, which recieving events changed.
			}
		}
	}
}

QString FromXmlToScript::generateMouseCommand(QString const &action, QString const &button, QString const &var) const
{
	return "api.cursor()." + button + "Button" + action + "(" + var + ");\n";
}

int FromXmlToScript::findPithyParent(QDomNodeList const &parents) const
{
	for (int i = 0; i < parents.size(); i++) {
		QDomElement parent = parents.at(i).toElement();
		QString const objectName = parent.attributes().namedItem("ObjectName").nodeValue();
		QString const objectType = parent.attributes().namedItem("Type").nodeValue();

		if (objectType == "qReal::gui::DraggableElement") {
			return i;
		}
	}

	return -1;
}
