#include "recorder.h"

#include <QtCore/QPropertyAnimation>
#include <QtWidgets/QGraphicsOpacityEffect>

#include "mainWindow.h"

#include <qrutils/graphicsUtils/animatedEffects.h>

using namespace qReal;
using namespace gui;
using namespace graphicsUtils;

Recorder::Recorder(QObject *parent)
	: QObject(parent)
	, mMainWindow(nullptr)
	, mRecordSign(new RecordSign)
{
}

void Recorder::init(MainWindow *mainWindow)
{
	mMainWindow = mainWindow;
}

void Recorder::start()
{
	// Show recording sign in new thread, cause animation.

	QThread *recordSignThread = new QThread(this);
	mRecordSign->moveToThread(recordSignThread);

	recordSignThread->start();
	mRecordSign->animate(this);
}
