#include "widgetFinder.h"

#include <QDebug>

using namespace utils;

QWidget *WidgetFinder::widget(QWidget const *parent, QString const &type, QString const &name)
{
	QList<QWidget *> const widgetList = parent->findChildren<QWidget *>(name);

	for (QWidget * const widget : widgetList) {
		const char *typeName = type.toStdString().c_str();
		if (widget->inherits(typeName) && widget->isVisible()) {
			return widget;
		}
	}

	return nullptr;
}
