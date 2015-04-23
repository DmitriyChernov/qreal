#include "recordShell.h"

#include <QDebug>

using namespace userAction;

RecordShell::RecordShell(QWidget *parent)
	: QWidget(parent)
	, mRecordSign(new RecordSign(this))
{
	setFixedSize(100, 100);
	setWindowFlags(Qt::WindowStaysOnTopHint);
	raise();
	move(QPoint(10,10));
}
