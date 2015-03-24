#pragma once

#include <QObject>

class WidgetFinder : public QObject
{
	Q_OBJECT

public:
	explicit WidgetFinder(QObject *parent = 0);

	QWidget *findWidget();
	void fromWidget(QWidget *widget);

};
