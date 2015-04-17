#include "recorder.h"

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLayout>

#include <qrutils/outFile.h>

using namespace qReal;
using namespace userAction;
using namespace utils;

Id const startingElementType = Id("userActionEditor", "userActionDiagram", "InitialNode");

UserActionRecorderPlugin::UserActionRecorderPlugin()
	: QObject()
	, mStartAction(new QAction(this))
	, mStopAction(new QAction(this))
	, mRecordShell(nullptr)
	, mScriptGenerator(nullptr)
	, mIsRecording(false)
{
	mStartAction->setShortcut(QKeySequence(Qt::SHIFT + Qt::Key_F9));
	mStopAction->setShortcut(QKeySequence(Qt::SHIFT + Qt::Key_F10));
}

void UserActionRecorderPlugin::init(PluginConfigurator const &configurator)
{
	connect(mStartAction, &QAction::triggered, this, &UserActionRecorderPlugin::start);
	connect(mStopAction, &QAction::triggered, this, &UserActionRecorderPlugin::stop);

	connect(mStartAction, &QAction::triggered
			, [configurator, this]() {
		connect(&configurator.systemEvents(), &SystemEvents::lowLevelEvent
				, this, &UserActionRecorderPlugin::lowLevelEvent);
		this->start();
	});

	connect(mStopAction, &QAction::triggered
			, [configurator, this]() {
		disconnect(&configurator.systemEvents(), &SystemEvents::lowLevelEvent
				, this, &UserActionRecorderPlugin::lowLevelEvent);
		if (mRecordElementId.toString() != "qrm:/") {
			configurator.logicalModelApi().setPropertyByRoleName(mRecordElementId, mUserActioDomDocument.toString(), "UserActions");
		}
	});

	connect(&configurator.systemEvents(), &qReal::SystemEvents::logicalElementAdded
			, [this](qReal::Id const &id) {
		if (id.diagram() == "UserActionDiagram"
				&& id.editor() == "UserActionEditor"
				&& id.element() == "Record") {
			mRecordElementId = id;
		}
	});

	mRecordShell = new RecordShell(configurator.mainWindowInterpretersInterface().windowWidget());
	connect(mRecordShell, &RecordShell::hintAdded, this, &UserActionRecorderPlugin::addHintEvent);

	mScriptGenerator = new FromXmlToScript();
}

void UserActionRecorderPlugin::start()
{
	mUserActioDomDocument.clear();
	mRecordShell->show();
	//mRecordSign->animate();
	mRootElement = mUserActioDomDocument.createElement("UserActions");
}

void UserActionRecorderPlugin::stop()
{
	mRecordShell->hide();
	//mRecordSign->stop();
	mUserActioDomDocument.appendChild(mRootElement);

	mScriptGenerator->generateScript(mUserActioDomDocument.toString());
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
				button = "left";
				break;
			case Qt::RightButton:
				button = "right";
				break;
			case Qt::MidButton:
				button = "mid";
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

void UserActionRecorderPlugin::addHintEvent(QString const &hint)
{
	QDomElement hintEvent = mUserActioDomDocument.createElement("Event");

	hintEvent.setAttribute("Type", "Hint");
	hintEvent.setAttribute("Message", hint);

	mRootElement.appendChild(hintEvent);
}

void UserActionRecorderPlugin::addParentChain(QDomElement *event, QWidget *widget)
{
	QWidget *parentWidget = widget->parentWidget();
	while (parentWidget) {
		QDomElement par = mUserActioDomDocument.createElement("Parent");
		par.setAttribute("Type", parentWidget->metaObject()->className());
		par.setAttribute("ObjectName", parentWidget->objectName());
		event->appendChild(par);
		parentWidget = parentWidget->parentWidget();
	}
}

UserActionRecorderPlugin::~UserActionRecorderPlugin()
{
	delete mRecordShell;
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
