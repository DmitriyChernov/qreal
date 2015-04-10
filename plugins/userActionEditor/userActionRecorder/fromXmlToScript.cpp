#include "fromXmlToScript.h"

#include <QtXml/QDomDocument>

using namespace userAction;

FromXmlToScript::FromXmlToScript()
{
}

void FromXmlToScript::generateScript(QString const &xml)
{
	QDomDocument events;
	events.setContent(xml);
	qDebug()<<events.toString();
}
