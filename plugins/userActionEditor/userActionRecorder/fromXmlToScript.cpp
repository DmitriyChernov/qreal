#include "fromXmlToScript.h"

#include <QtXml/QDomDocument>

#include <qrutils/outFile.h>

#include <QDebug>

using namespace userAction;
using namespace utils;

FromXmlToScript::FromXmlToScript()
	: QObject()
{
}

void FromXmlToScript::generateScript(QString const &xml)
{
	QDomDocument events;
	if (events.setContent(xml)) {
		QDomNodeList eventList = events.elementsByTagName("Event");

		utils::OutFile script("userActions.js");
		mActiveWindow = "mainWindow";
		script() << "var mainWindow = api.ui().mainWindow();";
		script() << "api.changeWindow(mainWindow);";

		for (int i = 1; i < eventList.size(); i+2) {
			QDomElement event = eventList.at(i).toElement();
			QString const recieverName = event.attributes().namedItem("RecieverName").nodeValue();
			QString const recieverType = event.attributes().namedItem("RecieverType").nodeValue();
			QString const eventType = event.attributes().namedItem("Type").nodeValue();
			QString const eventAction = event.attributes().namedItem("Action").nodeValue();

			if (eventType == "Hint") {
				script() << "api.hints().addHint(\""
							+ event.attributes().namedItem("Message").nodeValue()
							+ "\", 1500, " + mActiveWindow + ");";
				script() << "api.wait(1700)";
			}

			if (recieverName == "MainWindowUiWindow") {
				continue;
			} else if (recieverName != "" && recieverType != "") {
				script() << "var " + recieverName + " = api.ui().widget(\"" + recieverType + "\", \"" + recieverName + "\");";
				if (eventType == "Mouse") {
					if (eventAction == "Press") {
						mMousePressRecieverName = recieverName;
						script() << "api.cursor().moveTo(" + recieverName + ", 500)";
					} else if (eventAction == "Release" && recieverName != mMousePressRecieverName) {
						script() << "api.cursor().moveTo(" + recieverName + ", 500)";
					}
					script() << generateMouseCommand(eventAction
							, event.attributes().namedItem("Button").nodeValue()
							, recieverName);
				}
			} else {
				/// TODO : parse events without reciever name, but with parent chain.
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
	return "api.cursor()." + button + "Button" + action + "(" + var + ")";
}
