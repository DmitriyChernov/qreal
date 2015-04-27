#include "fromXmlToScript.h"

#include <QtXml/QDomDocument>

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

		OutFile script("userActions.js");
		mActiveWindow = "mainWindow";
		script() << "var mainWindow = api.ui().mainWindow();\n";
		script() << "api.changeWindow(mainWindow);\n";

		for (int i = 0; i < eventList.size(); i++	) {
			QDomElement event = eventList.at(i).toElement();
			QString const recieverName = event.attributes().namedItem("RecieverName").nodeValue();
			QString const recieverType = event.attributes().namedItem("RecieverType").nodeValue();
			QString const eventType = event.attributes().namedItem("Type").nodeValue();
			QString const eventAction = event.attributes().namedItem("Action").nodeValue();

			if (eventType == "Drop" && recieverType == "EditorViewScene") {
				QString const id = event.attributes().namedItem("Id").nodeValue();
				QString const xcoord = event.attributes().namedItem("Xcoord").nodeValue();
				QString const ycoord = event.attributes().namedItem("Ycoord").nodeValue();

				script()<<generateDragCommand(id, mDraggingElement, xcoord, ycoord);
			} else if (recieverName != "") {
				script() << "var "
						+ recieverName
						+ " = api.ui().widget(\""
						+ recieverType + "\", \""
						+ recieverName + "\");\n";
				if (eventType == "Mouse") {
					script() << generateMouseAction(eventAction
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
						continue;
					} else if (objectType == "qReal::EditorView") {
						QString const sceneViewport = "sceneViewport";
						QString const xcoord = parent.attributes().namedItem("Xcoord").nodeValue();
						QString const ycoord = parent.attributes().namedItem("Ycoord").nodeValue();
						script() << "var " + sceneViewport + " = api.ui().sceneViewport();\n";
						script() << "api.cursor().sceneMoveTo("
									+ sceneViewport
									+ ", 1000, "
									+ xcoord
									+ ", "
									+ ycoord
									+ ");\n";

						script() << generateMouseCommand(eventAction
								, event.attributes().namedItem("Button").nodeValue()
								, sceneViewport);
					} else {
						QString indexesArray = "var indexes = [";
						for (int j = 1; j <= parentList.size(); j++) {
							indexesArray += parentList.at(parentList.size() - j)
									.attributes()
									.namedItem("LayoutIndex")
									.nodeValue();
							indexesArray += ", ";
						}
						indexesArray += "];";
						script() << indexesArray;
						script() << "var widget = api.ui().widget(\""
								+ parentList.at(parentList.size() - 1).attributes().namedItem("Type").nodeValue()
								+ "\", \""
								+ parentList.at(parentList.size() - 1).attributes().namedItem("ObjectName").nodeValue()
								+ "\");";
						QString cycleCommand = "";
						cycleCommand += "for (var i = 0; i < ";
						cycleCommand += parentList.size();
						cycleCommand += "; i ++) \n{\n";
						script() << cycleCommand;
						script() << "widget = api.ui().widgetByLayoutIndex(indexes[i], widget);\n";
						script() << "}\n";

						if (eventType == "Mouse") {
							script() << generateMouseAction(eventAction
									, event.attributes().namedItem("Button").nodeValue()
									, "widget");
						}
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

QString FromXmlToScript::generateDragCommand(QString const &id
		, QString const &var
		, QString const &xcoord
		, QString const &ycoord) const
{
	return "var "
			+ var
			+ " = api.palette().dragPaletteElement(\""
			+ id
			+ "\", 500, "
			+ xcoord
			+ ", "
			+ ycoord
			+ ");\n";
}

int FromXmlToScript::findPithyParent(QDomNodeList const &parents) const
{
	for (int i = 0; i < parents.size(); i++) {
		QDomElement parent = parents.at(i).toElement();
		QString const objectName = parent.attributes().namedItem("ObjectName").nodeValue();
		QString const objectType = parent.attributes().namedItem("Type").nodeValue();

		if (objectType == "qReal::gui::DraggableElement"
				|| objectType == "qReal::EditorView") {
			return i;
		}
	}

	return -1;
}

QString FromXmlToScript::generateMouseAction(QString const &action, QString const &button, QString const &reciever)
{
	QString commands = "";
	if (action == "Press") {
		mMousePressRecieverName = reciever;
		commands += "api.cursor().moveTo(" + reciever + ", 500)\n";
	} else if (action == "Release" && reciever != mMousePressRecieverName) {
		commands += "api.cursor().moveTo(" + reciever + ", 500);\n";
	}
	commands += generateMouseCommand(action
			, button
			, reciever);

	return commands;
}
