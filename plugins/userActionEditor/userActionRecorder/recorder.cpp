#include "recorder.h"

#include <QtWidgets/QMainWindow>

#include <qrutils/outFile.h>

using namespace qReal;
using namespace userAction;
using namespace utils;

Id const startingElementType = Id("userActionEditor", "userActionDiagram", "InitialNode");

UserActionRecorderPlugin::UserActionRecorderPlugin()
	: QObject()
	, mMainWindow(nullptr)
	, mRecordSign(nullptr)
	, mStartAction(new QAction(this))
	, mStopAction(new QAction(this))
	, mIsRecording(false)
{
	mStartAction->setShortcut(QKeySequence(Qt::SHIFT + Qt::Key_F11));
	mStopAction->setShortcut(QKeySequence(Qt::SHIFT + Qt::Key_F12));
}

void UserActionRecorderPlugin::init(PluginConfigurator const &configurator)
{
	connect(mStartAction, &QAction::triggered, this, &UserActionRecorderPlugin::start);
	connect(mStopAction, &QAction::triggered, this, &UserActionRecorderPlugin::stop);\

	connect(mStartAction, &QAction::triggered
			, [configurator, this]() {
				connect(&configurator.systemEvents(), &SystemEvents::lowLevelEvent
						, this, &UserActionRecorderPlugin::lowLevelEvent);

				qDebug()<<configurator.logicalModelApi().
				IdList ids = configurator.logicalModelApi().children(configurator.logicalModelApi().rootId());

				int size = ids.size();
				for (int i = 0; i < size; i++) {
					qDebug()<<ids.at(i);
				}
				this->start();
			});

	connect(mStopAction, &QAction::triggered
			, [configurator, this]() {
				disconnect(&configurator.systemEvents(), &SystemEvents::lowLevelEvent
						, this, &UserActionRecorderPlugin::lowLevelEvent);
				this->stop();
			});

	//Id recordBlock = configurator.logicalModelApi().createElement(configurator.logicalModelApi().rootId(), );

	//Id const newId = Id(newEditor, changeToId.diagram(), changeToId.element(), QUuid::createUuid().toString());
	//Id const newElementId = mGraphicalModelApi.createElement(parentId, newId,

	mRecordSign = new RecordSign(configurator.mainWindowInterpretersInterface().windowWidget());
	mRecordSign->hide();
}

void UserActionRecorderPlugin::start()
{
	mRecordSign->show();
	//mRecordSign->animate();
	mRootElement = mUserActioDomDocument.createElement("UserActions");
}

void UserActionRecorderPlugin::stop()
{
	mRecordSign->hide();
	//mRecordSign->stop();

	OutFile userActionXml("userAction.xml");
	mUserActioDomDocument.appendChild(mRootElement);
	userActionXml() << mUserActioDomDocument.toString();
}

void UserActionRecorderPlugin::lowLevelEvent(QObject *obj, QEvent *e)
{
	QDomElement eventTag = mUserActioDomDocument.createElement("Event");

	if (e->type() == QEvent::MouseButtonPress || e->type() == QEvent::MouseButtonRelease)
	{
		QMouseEvent* event = dynamic_cast<QMouseEvent*>(e);

		eventTag.setAttribute("Type", "Mouse");
		eventTag.setAttribute("RecieverType", obj->metaObject()->className());
		eventTag.setAttribute("RecieverName", obj->objectName());

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
				action = "Release";
				break;
			default:
				return;
		}
		if (action == ""){
			return;
		}
		eventTag.setAttribute("Action", action);

		if (obj->objectName() == "" && dynamic_cast<QWidget *>(obj)) {
			addParentChain(&eventTag, dynamic_cast<QWidget *>(obj));
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

		eventTag.setAttribute("KeyName", e->ActionAdded);
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

void UserActionRecorderPlugin::addParentChain(QDomElement *event, QWidget *widget)
{
	QWidget *parentWidget = widget->parentWidget();
	while (parentWidget) {
		QDomElement par = mUserActioDomDocument.createElement("Parent");
		par.setAttribute("Type", parentWidget->metaObject()->className());
		par.setAttribute("Object_name", parentWidget->objectName());
		event->appendChild(par);
		parentWidget = parentWidget->parentWidget();
	}
}

UserActionRecorderPlugin::~UserActionRecorderPlugin()
{
	delete mRecordSign;
}


QList<ActionInfo> UserActionRecorderPlugin::actions()
{
	return { qReal::ActionInfo(mStartAction, "interpreters", "tools")
			, qReal::ActionInfo(mStopAction, "interpreters", "tools")
	};
}

QList<HotKeyActionInfo> UserActionRecorderPlugin::hotKeyActions()
{
	return { qReal::HotKeyActionInfo("UserActionRecorder.Start", QObject::tr("Start recording"), mStartAction)
		, qReal::HotKeyActionInfo("UserActionRecorder.Stop", QObject::tr("Stop deployment"), mStopAction)
	};
}
