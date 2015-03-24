#include "recorder.h"

#include <qrutils/outFile.h>

#include "mainWindow.h"

using namespace qReal;
using namespace gui;
using namespace utils;

Recorder::Recorder()
	: QObject()
	, mMainWindow(nullptr)
	, mRecordSign(nullptr)
{
}

void Recorder::init(MainWindow *mainWindow)
{
	mMainWindow = mainWindow;
}

void Recorder::start()
{
	mRecordSign = new RecordSign(mMainWindow);
	//mRecordSign->animate();

	mRootElement = mUserActioDomDocument.createElement("UserActions");
}

void Recorder::stop()
{
	mRecordSign->hide();
	//mRecordSign->stop();

	OutFile userActionXml("userAction.xml");
	mUserActioDomDocument.appendChild(mRootElement);
	userActionXml() << mUserActioDomDocument.toString();
}

void Recorder::lowLevelEvent(QObject *obj, QEvent *e)
{
	QDomElement eventTag;
	eventTag.setTagName("Event");
	if (e->type()== QEvent::MouseButtonPress || e->type() == QEvent::MouseButtonRelease)
	{
		QMouseEvent* event = dynamic_cast<QMouseEvent*>(e);

		eventTag.setAttribute("Type", "Mouse");

		QString button;
		switch(event->button()){
			case Qt::LeftButton:
				button = "Left";
				break;
			case Qt::RightButton:
				button = "Right";
				break;
			case Qt::MidButton:
				button = "Mid";
				break;
			default:
				return;
		}

		eventTag.setAttribute("Button", button);

		QString action;
		switch(e->type()){
			case QEvent::MouseButtonPress:
				action = "Press";
				break;
			case QEvent::MouseButtonRelease:
				button = "Release";
				break;
			default:
				return;
		}
		if (action == ""){
			return;
		}
		eventTag.setAttribute("Action", action);

		eventTag.setAttribute("RecieverType", obj->metaObject()->className());
		eventTag.setAttribute("RecieverName", obj->objectName());

		if (obj->objectName() == "" && dynamic_cast<QWidget *>(obj)) {
			addParentChain(*eventTag, dynamic_cast<QWidget *>(obj));
		} else {
			return;
		}

	} else if (e->type() == QEvent::KeyPress || e->type() == QEvent::KeyRelease){
		QKeyEvent* event = static_cast<QKeyEvent *>(e);

		eventTag.setAttribute("Type", "Key");

		QString action;
		switch(e->type())
		{
			case QEvent::KeyPress:
				action = "Press";
				break;
			case QEvent::KeyRelease:
				action = "Release";
				break;
			default:
				return;
		}

		eventTag.setAttribute("KeyName", event->text());
		eventTag.setAttribute("Action", action);
		if (event->text() == ""){
			return;
		}

	} else if (e->type() == QEvent::Wheel) {
		QWheelEvent* event = static_cast<QWheelEvent *>(e);

		eventTag.setAttribute("Type", "Wheel");
		eventTag.setAttribute("Delta", event->delta());
	} else {
		return;
	}

	mRootElement.appendChild(eventTag);
}

void Recorder::addParentChain(QDomElement &event, QWidget *widget)
{
	while (widget->parentWidget()) {
		QDomElement parent;
		parent.setTagName("Parent");
		parent.setAttribute("Type", widget->metaObject()->className());
		event.appendChild(parent);
	}
}
