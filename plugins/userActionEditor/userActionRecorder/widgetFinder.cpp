#include "widgetFinder.h"

WidgetFinder::WidgetFinder(QObject *parent) :
	QObject(parent)
{
}

void fromWidget(QWidget *widget)
{
	Q_UNUSED(widget);
}

QWidget *findWidget()
{
	return nullptr;
}
