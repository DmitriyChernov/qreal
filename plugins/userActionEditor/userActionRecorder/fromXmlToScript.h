#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>

namespace userAction {

class FromXmlToScript : public QObject
{
	Q_OBJECT

public:
	FromXmlToScript();

public slots:
	void generateScript(QString const &xml);

};
}
