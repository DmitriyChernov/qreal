#include "fromXmlToScript.h"

#include <QtXml/QDomDocument>

#include <QDebug>

using namespace userAction;
using namespace utils;

FromXmlToScript::FromXmlToScript()
	: QObject()
	, mIsDragFromPalette(false)
	, mSceneElementVariables(0)
	, mVariables(new QStringList())
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
			QString const recieverObjectName = event.attributes().namedItem("RecieverName").nodeValue();
			QString const recieverName = event.attributes().namedItem("RecieverName").nodeValue().replace(" ", "");
			QString const recieverType = event.attributes().namedItem("RecieverType").nodeValue();
			QString const eventType = event.attributes().namedItem("Type").nodeValue();
			QString const eventAction = event.attributes().namedItem("Action").nodeValue();

			if (eventType == "Drop" && recieverType == "EditorViewScene") {
				QString const id = event.attributes().namedItem("Id").nodeValue();
				QString const xcoord = event.attributes().namedItem("Xcoord").nodeValue();
				QString const ycoord = event.attributes().namedItem("Ycoord").nodeValue();

				script()<<generateDragCommand(id, mDraggingElement, xcoord, ycoord);
			} else if (recieverType == "QScrollBar" && eventAction == "Press"
					|| recieverName == "QComboBoxPrivateContainerClassWindow") {
				continue;
			} else if (recieverName != "" && recieverName != "qt_scrollarea_viewport") {
				if (!mVariables->contains(recieverName)) {
					script() << "var "
							+ recieverName
							+ " = api.ui().widget(\""
							+ recieverType + "\", \""
							+ recieverObjectName + "\");\n";
					mVariables->append(recieverName);
				}

				if (eventType == "Mouse") {
					script() << generateMouseAction(eventAction
							, event.attributes().namedItem("Button").nodeValue()
							, recieverType
							, recieverName);
				}
			} else {
				QDomNodeList const parentList = event.elementsByTagName("Parent");

				int const pithyParent = findPithyParent(parentList);

				if (pithyParent != -1) {
					QDomElement const parent = parentList.at(pithyParent).toElement();
					QString const objectName = parent.attributes().namedItem("ObjectName").nodeValue();
					QString const objectType = parent.attributes().namedItem("Type").nodeValue();

					qDebug()<<objectName;
					qDebug()<<objectType;

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
					} else if (objectType == "QComboBox") {
						QString varName = objectName;
						script() << "api.wait(100);\n";
						script() << "api.pickComboBoxItem("
								+ varName.replace(" ", "")
								+ ", "
								+ parent.attributes().namedItem("ItemSelected").nodeValue()
								+ ", "
								+ "1000);\n";
						continue;
					}
				}


				script() << generateArrayInitialising(parentList
						, "Index"
						, event.attributes().namedItem("Index").nodeValue());
				script() << generateArrayInitialising(parentList, "Type", recieverType);
				script() << generateArrayInitialising(parentList, "ObjectName", recieverObjectName);

				script() << "var widget = api.ui().widget(\""
						+ parentList.at(parentList.size() - 1).attributes().namedItem("Type").nodeValue()
						+ "\", \""
						+ parentList.at(parentList.size() - 1).attributes().namedItem("ObjectName").nodeValue()
						+ "\");\n";
				QString cycleCommand = "";
				cycleCommand += "for (var i = 1; i <= ";
				cycleCommand += QString::number(parentList.size());
				cycleCommand += "; i ++) \n{\n";
				script() << cycleCommand;
				script() << "\tif (Index[i - 1] == -1) {\n";
				script() << "\t\twidget = api.ui().widget(Type[i], ObjectName[i], widget);\n";
				script() << "\t} else {\n";
				script() << "\t\twidget = api.ui().widgetByIndex(Index[i - 1], widget);\n";
				script() << "\t}\n}\n";

				if (eventType == "Mouse") {
					if (recieverType == "QScrollBar" && eventAction == "Release") {
						script() << "api.scroll(widget, "
								+ event.attributes().namedItem("Value").nodeValue()
								+ ", 500);\n";
					} else {
						script() << generateMouseAction(eventAction
								, event.attributes().namedItem("Button").nodeValue()
								, recieverType
								, "widget");
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
		QString const objectType = parent.attributes().namedItem("Type").nodeValue();

		if (objectType == "qReal::gui::DraggableElement" || objectType == "qReal::EditorView"
				|| objectType == "QScrollBar" || objectType == "QComboBox") {
			return i;
		}
	}

	return -1;
}

QString FromXmlToScript::generateMouseAction(QString const &action, QString const &button, QString const &recieverType
		, QString const &reciever)
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

QString FromXmlToScript::generateArrayInitialising(QDomNodeList const &parents, QString const &name
		, QString const &child) const
{
	QString array = "var " + name + " = [";
	for (int j = 1; j <= parents.size(); j++) {
		QString element = parents.at(parents.size() - j)
				.attributes()
				.namedItem(name)
				.nodeValue();
		if (name != "Index") {
			array += "\"" + element + "\"";
		} else {
			QString parentObjectName;
			if (j != parents.size()) {
				parentObjectName = parents.at(parents.size() - j - 1)
						.attributes()
						.namedItem("ObjectName")
						.nodeValue();
			} else {
				break;
			}

			if (parentObjectName != "" || element == "") {
				array += "-1";
			} else {
				array += element;
			}
		}

		if (j != parents.size() || name != "Index") {
			array += ", ";
		}
	}

	if (name != "Index") {
		array += "\"" + child + "\"";
	} else {
		array += child;
	}

	array += "];\n";

	return array;
}
